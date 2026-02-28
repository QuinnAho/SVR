---
name: ue-build-run
description: Build and run conservative Unreal Editor smoke tests for SVR without assuming machine-specific configuration. Use when validating compile health, opening the project, and executing deterministic Office Fire PIE checks.
---

# UE Build + Run
Purpose: provide a repeatable, low-risk workflow to build the project and run a manual PIE smoke test for MVP flow validation.

## When to use this skill
- Validate that source changes still compile.
- Run pre-merge smoke checks for Office Fire session flow.
- Verify deterministic behavior before touching telemetry/scoring/report layers.

## Inputs
- `SVR.uproject` path.
- Unreal Engine root path (placeholder, machine-specific).
- Target config (`Development Editor` by default).
- Optional map/startup settings already configured in project.

## Outputs
- Local editor build attempt result (success/failure logs on machine running script).
- Completed manual smoke checklist results from `scripts/run-pie-smoketest.md`.
- Pass/fail note for Audit -> Score/Report -> Micro-drill -> Re-audit loop.

## Step-by-step procedure
- Confirm engine path and project path placeholders in scripts.
- Run `scripts/build_editor.ps1` (Windows) or `scripts/build_editor.sh` (Unix-like) with local paths.
- If build fails, fix compile errors before any PIE validation.
- Open `SVR.uproject` in the correct engine version.
- Follow `scripts/run-pie-smoketest.md` exactly.
- Record any nondeterministic behavior as a blocker.

## Verification checklist
- Build script exits with status `0`.
- Project opens in Unreal Editor with no missing module prompt loops.
- PIE run demonstrates this sequence:
- Audit phase starts and captures player actions.
- Session transitions to score/report.
- At least one targeted micro-drill is assigned from observed misses.
- Re-audit launches and records a second attempt.
- Expected telemetry/report fields exist in exports after run: `session_id`, `participant_id`, `phase`, `score_total`, `why`.

## Common pitfalls / guardrails
- Do not hardcode engine paths in tracked files; keep placeholders.
- Do not rely on packaged build for quick validation unless explicitly requested.
- Do not edit `.uasset`/`.umap` for logic that belongs in `Data` JSON.
- Keep smoke tests deterministic: same input sequence should yield same score.

## Definition of Done
- Editor target builds locally with configured path placeholders replaced.
- PIE smoke checklist is executed and all expected outcomes pass.
- Any failures are documented with exact failing phase and reproducible steps.


