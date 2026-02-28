# MVP Scope

## MVP goal
Ship a **pilotable** SVR experience that proves the full loop end-to-end:
**Audit → Score/Report → Targeted Follow-up → Re-audit → Improvement**

The MVP must be credible as a readiness tool (not a tech demo), and minimal enough to build quickly and iterate.

## Target form factor (MVP)
- **Desktop-first** (keyboard/mouse) for rapid development and demos
- **XR-ready architecture** (Quest later) with platform abstraction (no core rewrite)

## MVP scenario (single scenario)
### Office Fire Readiness Audit
- Environment: believable office slice (private office + hallway + exit path)
- Flow: normal activity → cue(s) → escalation → outcome
- Session length: ~10–15 minutes total

## Core features (must-have)
### 1) Session shell
- Start audit from a clean menu
- Participant ID entry (anonymous ID, no names)
- Single scenario selection (Office Fire)

### 2) Scenario runtime (deterministic)
- State machine:
  - Baseline → Cue → Escalation → End → Debrief → Follow-up → Re-audit → Final Report
- Scenario always terminates with a result (success/fail/end state)

### 3) Instrumentation (telemetry)
Log timestamped events such as:
- Session start
- Cue start (alarm/smoke onset)
- First reaction time
- Key decisions (movement direction, interactions)
- Protocol events (exit reached, etc.)
- Critical errors (e.g., delayed evacuation past threshold, moving toward hazard, re-entry)
- Session end state

### 4) Scoring (explainable)
- Deterministic Readiness Score (0–100)
- Score breakdown categories (minimum):
  - Reaction time
  - Decision quality
  - Protocol adherence
  - Critical errors
- “Why” strings for strengths/breakdowns tied to telemetry

### 5) After-action report
- On-screen report after each run:
  - Score
  - Strengths
  - Breakdowns
  - Critical errors
  - Assigned follow-up module(s)
- Exportable summary (see exports)

### 6) Targeted corrective follow-up (SVR differentiator)
- Identify top 1–2 failure modes from rubric
- Run a short micro-drill (30–90s) targeting only those gaps
- Minimal, failure-specific guidance (no long training paths)

### 7) Re-audit + improvement delta
- Run a shortened re-audit (or relevant sub-section)
- Display improvement delta:
  - score_before vs score_after
  - gap_resolved flag(s)

### 8) Offline export (pilot-friendly)
- Export per session:
  - JSON (full structured record)
  - CSV (summary row)
- Optional “export all + purge” for pilots

## Non-goals (explicitly out of scope for MVP)
- Cloud dashboard / accounts / logins / multi-tenant SaaS
- Biometrics (heart rate, eye tracking) required
- Open-ended generative AI driving scoring or pass/fail
- Multi-scenario libraries
- Multiplayer / multi-user sessions
- Facility scanning / custom per-building models
- Full compliance/legal policy packs (beyond a minimal dialogue prototype)

## MVP acceptance criteria (definition of done)
- A user can complete the Office Fire audit end-to-end without crashes.
- A report is generated every run.
- Exports are created and include required schema fields.
- Follow-up micro-drill runs when a failure is triggered.
- Re-audit runs and improvement delta is shown.
- The experience looks credible (office visuals + alarm/smoke/audio cues) and feels like software.