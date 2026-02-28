#!/usr/bin/env python3
"""
Repository standards checker/enforcer.

Commands:
  - check
  - enforce-doc-names [--apply]
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Iterable, List, Tuple
from urllib.parse import unquote


DEFAULT_EXCEPTIONS = {"README.md", "AGENTS.md", "CLAUDE.md", "SKILL.md"}
DOC_NAME_RE = re.compile(r"^[a-z0-9]+(?:-[a-z0-9]+)*\.md$")
MD_LINK_RE = re.compile(r"\[([^\]]+)\]\(([^)]+)\)")
PUBLIC_CS_TYPE_RE = re.compile(
    r"^\s*public\s+(?:class|interface|enum|struct|record)\s+\w+"
)
PUBLIC_CS_MEMBER_RE = re.compile(
    r"^\s*public\s+(?!class\b|interface\b|enum\b|struct\b|record\b).*\("
)
UMACRO_RE = re.compile(r"^\s*(UCLASS|USTRUCT|UENUM|UFUNCTION)\b")


@dataclass
class Finding:
    category: str
    path: Path
    message: str


def repo_root_from_script(script_path: Path) -> Path:
    # .../Skills/repo-standards/scripts/standards_guard.py -> repo root
    return script_path.resolve().parents[3]


def iter_files(root: Path, suffixes: Iterable[str]) -> Iterable[Path]:
    suffixes_l = {s.lower() for s in suffixes}
    skip_dirs = {
        ".git",
        ".vs",
        "Binaries",
        "DerivedDataCache",
        "Intermediate",
        "Saved",
    }
    for p in root.rglob("*"):
        if not p.is_file():
            continue
        if any(part in skip_dirs for part in p.parts):
            continue
        if p.suffix.lower() in suffixes_l:
            yield p


def relative(path: Path, root: Path) -> Path:
    return path.resolve().relative_to(root.resolve())


def slugify_doc_stem(stem: str) -> str:
    s = stem.strip()
    s = re.sub(r"([a-z0-9])([A-Z])", r"\1-\2", s)
    s = s.replace("_", "-")
    s = re.sub(r"[^A-Za-z0-9-]+", "-", s)
    s = re.sub(r"-{2,}", "-", s)
    s = s.strip("-").lower()
    return s or "doc"


def check_doc_names(root: Path, findings: List[Finding], exceptions: set[str]) -> None:
    for md in iter_files(root, [".md"]):
        name = md.name
        if name in exceptions:
            continue
        if not DOC_NAME_RE.match(name):
            target = f"{slugify_doc_stem(md.stem)}.md"
            findings.append(
                Finding(
                    "doc-name",
                    relative(md, root),
                    f"Use kebab-case filename. Suggested: {target}",
                )
            )


def check_markdown_format(root: Path, findings: List[Finding]) -> None:
    for md in iter_files(root, [".md"]):
        rel = relative(md, root)
        try:
            text = md.read_text(encoding="utf-8-sig")
        except UnicodeDecodeError:
            findings.append(Finding("markdown", rel, "File is not valid UTF-8"))
            continue
        lines = text.splitlines()
        h1_count = sum(1 for line in lines if line.lstrip("\ufeff").startswith("# "))
        if h1_count != 1:
            findings.append(Finding("markdown", rel, f"Expected 1 H1 heading, found {h1_count}"))
        for i, line in enumerate(lines, start=1):
            if line.rstrip("\t ") != line:
                findings.append(Finding("markdown", rel, f"Trailing whitespace on line {i}"))
                break


def check_json_parseable(root: Path, findings: List[Finding]) -> None:
    for js in iter_files(root, [".json"]):
        rel = relative(js, root)
        try:
            json.loads(js.read_text(encoding="utf-8-sig"))
        except Exception as exc:  # noqa: BLE001
            findings.append(Finding("json", rel, f"Invalid JSON: {exc}"))


def has_doxygen_above(lines: List[str], idx: int, max_lookback: int = 10) -> bool:
    j = idx - 1
    looked = 0
    seen_non_empty = False
    while j >= 0 and looked < max_lookback:
        looked += 1
        s = lines[j].strip()
        if not s:
            if seen_non_empty:
                break
            j -= 1
            continue
        seen_non_empty = True
        if s.startswith("/**"):
            return True
        if s.startswith("*") or s.startswith("*/"):
            j -= 1
            continue
        return False
    return False


def check_cpp_comment_conventions(root: Path, findings: List[Finding]) -> None:
    for header in iter_files(root, [".h"]):
        rel = relative(header, root)
        rel_s = str(rel).replace("\\", "/")
        if "/Source/" not in rel_s:
            continue
        text = header.read_text(encoding="utf-8", errors="replace")
        lines = text.splitlines()
        for i, line in enumerate(lines):
            if UMACRO_RE.match(line) and not has_doxygen_above(lines, i):
                macro = UMACRO_RE.match(line).group(1)  # type: ignore[union-attr]
                findings.append(
                    Finding(
                        "cpp-comments",
                        rel,
                        f"Add Doxygen block comment above {macro} (line {i + 1})",
                    )
                )


def has_xml_summary_above(lines: List[str], idx: int, max_lookback: int = 8) -> bool:
    j = idx - 1
    looked = 0
    saw_comment = False
    while j >= 0 and looked < max_lookback:
        looked += 1
        s = lines[j].strip()
        if not s:
            if saw_comment:
                break
            j -= 1
            continue
        if s.startswith("///"):
            saw_comment = True
            if "<summary>" in s:
                return True
            j -= 1
            continue
        break
    return False


def check_csharp_xml_comments(root: Path, findings: List[Finding]) -> None:
    for cs in iter_files(root, [".cs"]):
        rel = relative(cs, root)
        name = cs.name
        if name.endswith(".Build.cs") or name.endswith(".Target.cs"):
            continue
        lines = cs.read_text(encoding="utf-8", errors="replace").splitlines()
        for i, line in enumerate(lines):
            if PUBLIC_CS_TYPE_RE.match(line) or PUBLIC_CS_MEMBER_RE.match(line):
                if not has_xml_summary_above(lines, i):
                    findings.append(
                        Finding(
                            "cs-comments",
                            rel,
                            f"Add /// <summary> XML comment above public declaration (line {i + 1})",
                        )
                    )


def run_check(root: Path, exceptions: set[str]) -> int:
    findings: List[Finding] = []
    check_doc_names(root, findings, exceptions)
    check_markdown_format(root, findings)
    check_json_parseable(root, findings)
    check_cpp_comment_conventions(root, findings)
    check_csharp_xml_comments(root, findings)

    if not findings:
        print("PASS: no standards violations found")
        return 0

    findings.sort(key=lambda f: (f.category, str(f.path), f.message))
    for f in findings:
        print(f"[{f.category}] {f.path}: {f.message}")
    print(f"\nFAIL: {len(findings)} violation(s) found")
    return 1


def split_link_target(raw_target: str) -> Tuple[str, str, str]:
    # Returns: path_part, query_part (with '?'), anchor_part (with '#')
    path_part = raw_target
    query_part = ""
    anchor_part = ""

    if "#" in path_part:
        path_part, anchor = path_part.split("#", 1)
        anchor_part = f"#{anchor}"
    if "?" in path_part:
        path_part, query = path_part.split("?", 1)
        query_part = f"?{query}"
    return path_part, query_part, anchor_part


def is_external_link(target_path: str) -> bool:
    t = target_path.lower().strip()
    return (
        t.startswith("http://")
        or t.startswith("https://")
        or t.startswith("mailto:")
        or t.startswith("#")
        or t.startswith("file://")
    )


def build_doc_rename_plan(root: Path, exceptions: set[str]) -> List[Tuple[Path, Path]]:
    plan: List[Tuple[Path, Path]] = []
    seen_targets: Dict[Path, Path] = {}
    for md in iter_files(root, [".md"]):
        if md.name in exceptions:
            continue
        target_name = f"{slugify_doc_stem(md.stem)}.md"
        if target_name == md.name:
            continue
        target = md.with_name(target_name)
        if target in seen_targets and seen_targets[target] != md:
            raise RuntimeError(
                f"Naming collision: {relative(md, root)} and {relative(seen_targets[target], root)}"
                f" both map to {relative(target, root)}"
            )
        seen_targets[target] = md
        plan.append((md, target))
    return sorted(plan, key=lambda t: str(relative(t[0], root)))


def apply_rename(src: Path, dst: Path) -> None:
    src_resolved = src.resolve()
    dst_resolved = dst.resolve()
    if src_resolved == dst_resolved:
        return
    if src.parent != dst.parent:
        dst.parent.mkdir(parents=True, exist_ok=True)
    if dst.exists():
        raise RuntimeError(f"Cannot rename {src} -> {dst}: destination exists")
    # Handle case-only renames on case-insensitive filesystems.
    if str(src).lower() == str(dst).lower():
        tmp = src.with_name(src.name + ".tmp-rename")
        if tmp.exists():
            raise RuntimeError(f"Temporary path exists: {tmp}")
        src.rename(tmp)
        tmp.rename(dst)
    else:
        src.rename(dst)


def update_markdown_links(root: Path, rename_map_abs: Dict[Path, Path], apply: bool) -> int:
    changed = 0
    md_files = list(iter_files(root, [".md"]))
    for md in md_files:
        text = md.read_text(encoding="utf-8", errors="replace")
        original = text

        def repl(match: re.Match[str]) -> str:
            label = match.group(1)
            target = match.group(2)
            path_part, query_part, anchor_part = split_link_target(target)
            if is_external_link(path_part):
                return match.group(0)

            decoded = unquote(path_part)
            candidate = (md.parent / decoded).resolve()
            if candidate not in rename_map_abs:
                return match.group(0)

            new_abs = rename_map_abs[candidate]
            new_rel = Path(
                re.sub(
                    r"\\",
                    "/",
                    str(new_abs.relative_to(md.parent.resolve()))
                    if new_abs.is_relative_to(md.parent.resolve())
                    else str(Path("..") / new_abs.name),
                )
            )
            new_target = f"{new_rel.as_posix()}{query_part}{anchor_part}"
            return f"[{label}]({new_target})"

        text = MD_LINK_RE.sub(repl, text)
        if text != original:
            changed += 1
            if apply:
                md.write_text(text, encoding="utf-8", newline="\n")
    return changed


def run_enforce_doc_names(root: Path, exceptions: set[str], apply: bool) -> int:
    plan = build_doc_rename_plan(root, exceptions)
    if not plan:
        print("No doc filename changes required")
        return 0

    print("Doc rename plan:")
    for src, dst in plan:
        print(f"- {relative(src, root)} -> {relative(dst, root)}")

    if not apply:
        print("\nDry run only. Re-run with --apply to execute.")
        return 0

    rename_map_abs: Dict[Path, Path] = {}
    for src, dst in plan:
        rename_map_abs[src.resolve()] = dst.resolve()
    for src, dst in plan:
        apply_rename(src, dst)

    updated = update_markdown_links(root, rename_map_abs, apply=True)
    print(f"\nApplied {len(plan)} rename(s); updated links in {updated} markdown file(s).")
    return 0


def parse_args(argv: List[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Check/enforce repository standards")
    parser.add_argument(
        "--root",
        type=Path,
        default=None,
        help="Repository root (defaults to auto-detect from script path)",
    )
    parser.add_argument(
        "--extra-doc-name-exception",
        action="append",
        default=[],
        help="Extra markdown filename exception (repeatable)",
    )
    sub = parser.add_subparsers(dest="command", required=True)

    sub.add_parser("check", help="Audit standards")
    enforce = sub.add_parser("enforce-doc-names", help="Rename doc files to kebab-case")
    enforce.add_argument(
        "--apply",
        action="store_true",
        help="Apply renames and link updates (default is dry run)",
    )
    return parser.parse_args(argv)


def main(argv: List[str]) -> int:
    args = parse_args(argv)
    root = args.root.resolve() if args.root else repo_root_from_script(Path(__file__))
    exceptions = set(DEFAULT_EXCEPTIONS)
    exceptions.update(args.extra_doc_name_exception)

    if args.command == "check":
        return run_check(root, exceptions)
    if args.command == "enforce-doc-names":
        return run_enforce_doc_names(root, exceptions, apply=bool(args.apply))
    raise RuntimeError(f"Unknown command: {args.command}")


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
