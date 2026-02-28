---
name: telemetry-export
description: Implement and validate offline telemetry logging and deterministic JSON/CSV export for SVR sessions. Use when defining event schema, export shape, or replay/debug data requirements.
---

# Telemetry Export
Purpose: enforce stable event schema and reliable local export artifacts for auditing and replay.

## When to use this skill
- Add or modify telemetry event fields.
- Update JSON/CSV export logic.
- Verify that scoring/report generation has complete event evidence.

## Inputs
- `Data/Schemas/telemetry_event.schema.json`.
- `Data/Examples/example_export.json`.
- `Data/Examples/example_export.csv`.
- Runtime events emitted by Office Fire flow.

## Outputs
- Event records that validate against schema.
- Session export JSON and CSV with consistent field naming.
- Clear event lineage from audit to re-audit.

## Step-by-step procedure
- Define event types and required fields in schema first.
- Emit events at each objective interaction and phase transition.
- Include deterministic identifiers: `session_id`, `participant_id`, `event_id`.
- Export complete session bundle to JSON.
- Flatten event timeline to CSV with one row per event.
- Ensure local-only file write path for offline operation.

## Verification checklist
- Schema validation passes for exported events.
- JSON includes `events`, `score`, and `report` sections.
- CSV row count matches JSON `events` count.
- Required fields present in all rows: `timestamp`, `event_type`, `phase`, `outcome`.

## Common pitfalls / guardrails
- Never drop failed interactions; failures are required for scoring explainability.
- Avoid locale-dependent timestamp formats; use ISO 8601 UTC.
- Do not add cloud upload or online authentication dependencies.
- Keep exported field names stable for pilot analysis scripts.

## Definition of Done
- Telemetry exports are deterministic and complete for identical inputs.
- JSON and CSV artifacts are generated locally with matching event counts.
- Event evidence is sufficient to recompute score and report offline.


