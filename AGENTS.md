# AGENTS.md

> Quick brief for AI coding agents working in this repo.
> Keep changes verifiable, scoped, and deterministic.
<!-- Encoding guardrail: keep text files UTF-8 with ASCII-safe punctuation (straight quotes, "->", "-") to avoid mojibake in terminals. -->

## Project (SVR) in one sentence
SVR (Stress-Validated Readiness) is an **audit-first readiness simulator**: run a short scenario, log behavior, compute an explainable score, deliver an after-action report, run targeted follow-up, then re-audit to verify improvement.

## What we are building first (MVP)
A desktop-first (XR later) **Office Fire** audit with:
- 15-minute session flow: Audit -> Score/Report -> Targeted micro-drill -> Re-audit
- Deterministic scoring + exportable logs (JSON + CSV)
- No biometrics required; offline-friendly; anonymous participant IDs

## Skills (preferred playbooks for recurring tasks)
For repeatable work (build/run, scenario data, telemetry/export, scoring, report UI, XR porting), prefer the repo's `/Skills/*/SKILL.md` playbooks. Use them as the default workflow to reduce mistakes and keep changes verifiable.

## Quick start (human steps; agent should not assume local tools exist)
- Open the Unreal project (`SVR.uproject`) in the correct UE version.
- Run Play-In-Editor (PIE) to smoke test scenario flow.
- Package builds only when explicitly requested (takes time + environment-specific).

## Verification (required)
When you change code or scenario logic, include one of:
- A reproducible manual test checklist (PIE steps + expected outcomes)
- Automated test command(s) if present
- Expected output snippets (e.g., example JSON/CSV export fields)

## Hard boundaries (do NOT do these)
- Do not add or modify secrets, API keys, credentials, or `.env` files.
- Do not introduce network/cloud dependencies in the MVP without explicit request.
- Do not make scoring depend on generative AI output.
- Do not modify binary assets (`.uasset`, `.umap`) unless explicitly asked.
  - Prefer text-based scenario data in `Data/*.json` or `*.csv`.

## Repo map (high-level)
- `Plugins/SVRCore/Source/` - C++ modules for core logic (preferred)
- `Plugins/SVRCore/Content/` - UE assets used by the plugin (minimal binary editing)
- `Content/` - project-level pilot/demo assets (if not using plugin-only content)
- `Data/` - text scenario definitions, rubrics, example exports
- `Docs/` - design docs, pilot one-pagers, internal notes

## Agent roles (pick one "hat" per task)
### @core-agent
Owns session lifecycle, scenario state machine, platform-agnostic abstractions.

### @telemetry-agent
Owns event schema, logging, export pipeline (JSON/CSV), replay/debug tooling.

### @scoring-agent
Owns rubric definitions, deterministic scoring rules, explainability ("why" strings).

### @ui-agent
Owns report UI, facilitator UI, clean product shell (UMG/Slate/CommonUI).

### @scenario-agent
Owns Office Fire scenario scripting/data, triggers, cues, micro-drills.

### @build-agent
Owns packaging scripts, build configs, performance budgets, device targets.

## Output expectations for any change
- Summarize what changed and why.
- List files changed.
- Provide a verification checklist (PIE steps) and what "good" looks like.
- Call out any open risks/assumptions.
