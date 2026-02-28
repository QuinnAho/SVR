---
name: repo-standards
description: Enforce and audit repository-wide standards for documentation naming, documentation formatting, code comment conventions, and basic file hygiene. Use when asked to standardize docs/code style, check convention drift, or apply consistent naming/formatting rules across the project.
---

# Repo Standards

Keep repository standards consistent and auditable.

## Convention Set

- Use `kebab-case` for documentation filenames (`lowercase-with-hyphens`).
- Keep fixed convention names unchanged: `README.md`, `AGENTS.md`, `CLAUDE.md`, `SKILL.md`.
- Keep markdown clean: one H1 (`#` heading) per file and no trailing whitespace.
- Keep JSON files parseable.
- Add Doxygen block comments (`/** ... */`) before `UCLASS`, `USTRUCT`, `UENUM`, and `UFUNCTION` in C++ headers.
- Add XML doc comments (`/// <summary>`) before public C# declarations (excluding Unreal `*.Build.cs` and `*.Target.cs`).

## Tools in This Skill

- `scripts/standards_guard.py`
  - `check`: audit standards and report issues.
  - `enforce-doc-names --apply`: rename docs to kebab-case and update markdown links.

## Workflow

1. Run standards audit:
   - `python Skills/repo-standards/scripts/standards_guard.py check`
2. If doc naming violations exist, enforce and rewrite links:
   - `python Skills/repo-standards/scripts/standards_guard.py enforce-doc-names --apply`
3. Re-run audit:
   - `python Skills/repo-standards/scripts/standards_guard.py check`
4. Fix remaining findings (comments/format issues) in code.
5. Report:
   - what changed
   - files changed
   - remaining risks or intentional exceptions

## Guardrails

- Do not change binary assets as part of standards cleanup.
- Prefer deterministic script-driven edits over manual bulk renames.
- Keep exceptions explicit; do not silently ignore violations.
