---
name: scoring-rubric
description: Build deterministic, explainable scoring rules for SVR using telemetry-derived evidence only. Use when editing weights, critical errors, pass thresholds, and why-string generation.
---

# Scoring Rubric
Purpose: provide deterministic score computation from telemetry with transparent, auditable rationale.

## When to use this skill
- Add or tune objective weights and penalties.
- Define critical errors and fail logic.
- Update explainability strings shown in reports.

## Inputs
- `Data/Scenarios/OfficeFire/rubric.json`.
- Telemetry exports conforming to schema.
- Scenario objective IDs and expected evidence events.

## Outputs
- Stable scoring rule set with explicit formulas.
- Computed `score_total` and per-objective breakdown.
- Human-readable `why` explanations tied to specific events.

## Step-by-step procedure
- Declare objective weights and scoring basis (`binary`, `timed`, or `penalty`).
- Map each objective to required telemetry event evidence.
- Define critical errors with deterministic score impact and fail semantics.
- Compute audit score from first run, then re-audit delta.
- Generate `why` strings referencing objective IDs and outcomes.
- Persist final score payload for report rendering and export.

## Verification checklist
- Same event stream always yields same score.
- Every non-zero score delta has matching evidence event IDs.
- Critical error triggers expected hard penalty/fail state.
- Report includes at least one positive and one corrective `why` string when applicable.

## Common pitfalls / guardrails
- Do not use generative AI or probabilistic heuristics in scoring.
- Do not compute score from UI state; use telemetry only.
- Avoid hidden magic constants; keep all weights in rubric JSON.
- Keep formulas explainable enough for facilitator review.

## Definition of Done
- Scoring can be recomputed offline from export artifacts alone.
- Rule definitions are text-based, versionable, and linked to objective IDs.
- Output includes transparent per-objective reasoning and total score.


