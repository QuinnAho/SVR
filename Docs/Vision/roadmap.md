# Roadmap

This roadmap keeps the MVP small while ensuring the architecture scales into the full product.

Detailed milestone plan: [MVP Roadmap](mvp-roadmap.md)

## Phase 1 — MVP (Pilotable audit loop)
**Objective:** Prove the SVR loop works end-to-end with one scenario.

Deliverables:
- Desktop-first Office Fire audit
- Telemetry schema + JSON/CSV exports
- Deterministic scoring + explainable breakdowns
- After-action report UI
- Targeted micro-drills + re-audit improvement delta
- Pilot runbook + one-page overview

Success criteria:
- Can run 10–20 participants in a controlled pilot
- Outputs are useful and defensible to a risk/compliance stakeholder
- Clear failure modes are detected and corrected

## Phase 2 — Scenario expansion + “low-risk dialogue” track
**Objective:** Add breadth while staying deterministic and pilot-friendly.

Deliverables:
- Additional emergency scenarios (e.g., evacuation variants, medical event, severe weather)
- Dialogue-based compliance scenarios (policy/reporting decision paths)
  - Deterministic checkpoints + rubric scoring
  - Repeatable practice loops
- More robust facilitator view (local, no cloud required)

Success criteria:
- Multiple scenarios share the same telemetry/scoring/report pipeline
- Stakeholders see relevance beyond a single scenario

## Phase 3 — XR deployment (Quest) + optional mixed reality verification
**Objective:** Move from desktop demos to real deployment hardware.

Deliverables:
- XR pawn + comfort locomotion + input mapping
- Performance pass for standalone headsets
- Optional casting / facilitator console support
- Optional passthrough / mixed reality “real-space verification” prototype (if needed)

Success criteria:
- Same core audit engine runs on Quest with minimal changes
- Pilot logistics are “bring headset + run sessions”

## Phase 4 — Full product platform (dashboard + scalability)
**Objective:** Build the long-term product layer buyers will pay for at scale.

Deliverables:
- Dashboard (local or cloud depending on client needs):
  - site/team trends over time
  - top breakdown modes
  - improvement tracking
  - audit trail exports
- Data retention and privacy controls
- Role-based access + deployment options (cloud vs private tenant)
- Scenario authoring tools and content pipeline

Success criteria:
- Repeatable sales motion supported by measurable outcomes + case studies
- Multi-site deployments manageable with standardized tooling

