---
name: scenario-contract
description: Define and maintain text-first scenario contracts for SVR Office Fire flow. Use when adding or updating scenario phases, triggers, objectives, and micro-drill mappings under Data.
---

# Scenario Contract
Purpose: keep Office Fire scenario behavior data-driven, deterministic, and reviewable via JSON contracts.

## When to use this skill
- Add or modify scenario phases, timing, prompts, or failure conditions.
- Review scenario JSON for deterministic sequencing.
- Keep gameplay scripting aligned with telemetry and scoring contracts.

## Inputs
- `Data/Scenarios/OfficeFire/scenario.json`.
- `Data/Scenarios/OfficeFire/microdrills.json`.
- `Data/Scenarios/OfficeFire/rubric.json`.
- Constraints from MVP session flow and pilot runtime limits.

## Outputs
- Updated scenario JSON contracts with stable IDs.
- Deterministic trigger definitions with explicit phase transitions.
- Mapping from observed misses to targeted micro-drills.

## Step-by-step procedure
- Define phases in strict order: `audit`, `score_report`, `micro_drill`, `re_audit`.
- Assign stable IDs for objectives, triggers, and decision points.
- Declare timebox and failure/success conditions per phase.
- Map each objective to telemetry event types.
- Map objective misses and critical errors to micro-drill IDs.
- Validate references between scenario, rubric, and microdrills files.

## Verification checklist
- All phase IDs are unique and appear in expected sequence.
- Each objective has measurable completion criteria and event evidence.
- Missing objective IDs referenced in `microdrills.json` resolve correctly.
- Example run can produce both pass and fail outcomes without data edits.

## Common pitfalls / guardrails
- Avoid implicit logic hidden in Blueprints when it can live in JSON.
- Do not depend on randomness unless seed and behavior are fixed.
- Do not introduce networked content fetch for scenario definitions.
- Keep identifiers immutable once pilot data collection starts.

## Definition of Done
- Scenario contract is complete, cross-file consistent, and deterministic.
- Required phase transitions and trigger evidence are testable in PIE.
- Micro-drill mapping covers known objective misses and critical errors.


