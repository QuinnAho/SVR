---
name: xr-porting
description: Plan and stage future XR adaptation of SVR after desktop MVP is stable. Use only for Phase 3 planning and implementation prep, while preserving deterministic scoring and telemetry contracts.
---

# XR Porting (Phase 3 / Future)
Purpose: guide deferred XR migration planning without destabilizing current desktop MVP workflows.

## When to use this skill
- Phase 3 planning after desktop pilot criteria are met.
- Mapping desktop interactions to XR input abstractions.
- Estimating performance and UX constraints for target XR hardware.

## Inputs
- Stable desktop scenario, telemetry, scoring, and report contracts.
- Target XR device profile(s) and frame budget constraints.
- Current interaction/action map from Office Fire desktop flow.

## Outputs
- XR porting plan with risk-ranked milestones.
- Input abstraction mapping (desktop -> XR controllers/hands).
- Validation matrix ensuring parity of telemetry and scoring outputs.

## Step-by-step procedure
- Confirm desktop MVP readiness and frozen data contracts.
- Define platform abstraction layer for inputs and locomotion.
- Re-map Office Fire interactions to XR equivalents.
- Preserve event emission points and scoring evidence paths.
- Add XR-specific comfort/performance checks.
- Run parity tests comparing desktop and XR exports.

## Verification checklist
- Desktop and XR runs emit the same required event types.
- Scoring parity: same scripted outcomes produce equivalent score totals.
- Report payload shape remains unchanged.
- Performance targets meet chosen device budgets.

## Common pitfalls / guardrails
- Phase 3 only: do not block desktop MVP on XR work.
- Avoid XR-only branching in scoring logic.
- Do not fork schema contracts per platform unless unavoidable.
- Keep offline-first behavior; no cloud dependency for XR mode.

## Definition of Done
- XR implementation plan exists with clear phase gates and parity checks.
- Core telemetry/scoring/report contracts remain desktop-compatible.
- Any XR-specific deviations are documented with explicit rationale.
