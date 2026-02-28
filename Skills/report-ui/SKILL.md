---
name: report-ui
description: Build facilitator-facing score/report UI for SVR that reads deterministic scoring outputs and explainability strings. Use when implementing report layout, evidence drilldown, or micro-drill assignment views.
---

# Report UI
Purpose: render a clear after-action report from deterministic score and telemetry artifacts without introducing hidden logic.

## When to use this skill
- Create or adjust report screen layout/sections.
- Wire UI bindings to score breakdown and explainability fields.
- Validate facilitator readability in short pilot sessions.

## Inputs
- Report payload schema `Data/Schemas/report.schema.json`.
- Scoring output (total, breakdown, why strings).
- Micro-drill recommendations linked to misses/errors.

## Outputs
- Report UI contract mapping data fields to visible sections.
- Deterministic rendering behavior for same payload.
- Facilitator-ready summary with next-drill recommendations.

## Step-by-step procedure
- Bind UI fields directly to report payload keys.
- Display total score, objective breakdown, and critical errors prominently.
- Show explainability list (`why`) with objective IDs.
- Present recommended micro-drill IDs and rationale.
- Ensure re-audit comparison block highlights delta by objective.
- Verify all text has fallback for missing optional fields.

## Verification checklist
- Report renders from `example_export.json` data without manual edits.
- Visible sections: `score_total`, `objective_breakdown`, `critical_errors`, `recommended_microdrills`.
- Re-audit comparison values align with exported score delta.
- No score recomputation occurs in UI layer.

## Common pitfalls / guardrails
- Keep UI pure presentation; scoring must remain in scoring subsystem.
- Avoid embedding hardcoded scenario text that belongs in data files.
- Do not block report rendering on network availability.
- Use stable field names from schema to prevent binding drift.

## Definition of Done
- Report screen consistently renders deterministic outputs for pilot sessions.
- Facilitator can identify misses, reasons, and next drill in under 60 seconds.
- UI behavior is reproducible across repeated runs with same payload.


