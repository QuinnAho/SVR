# MVP Roadmap

This is the milestone-level plan for the MVP build.

## Milestone 0 - Repo + baseline project

Achievement: Project boots reliably and is structured for growth.

- Create Unreal project + source control.
- Add clean folder/module structure (`SVRCore`, `SVRScenario`, `SVRUI`, `SVRTelemetry`).
- Add main menu placeholder with `Start Audit` button.

Done when: You can open, play, and exit without errors.

## Milestone 1 - Desktop walkaround demo

Achievement: It feels like a real office sim, not a blank map.

- Import office environment pack.
- Add basic lighting (consistent office neutral).
- Add basic movement (WASD + mouse look).
- Add interaction raycast + `Interact (E)` prompt.

Done when: You can record a 30s video walking around and it looks legit.

## Milestone 2 - Scenario state machine (the audit spine)

Achievement: The scenario progresses deterministically.

Implement a simple finite state machine:
Baseline -> Cue -> Escalation -> End -> Debrief

- Baseline: calm idle timer (e.g., 20-40s).
- Cue: alarm starts + first smoke cue appears.
- Escalation: smoke increases / visibility decreases / urgency rises.
- End: ends when user reaches exit zone OR time limit OR critical fail.

Done when: You can run it 5 times and it always completes.

## Milestone 3 - Instrumentation v1 (event logging)

Achievement: The sim produces objective records.

- Define event schema (`timestamp`, `event_type`, `metadata`).
- Log:
- Session start
- Cue start
- First reaction
- First movement
- Exit reached
- Critical error triggers
- Session end

Done when: Each run produces a structured log file.

## Milestone 4 - Scoring v1 (deterministic rubric)

Achievement: Readiness Score exists and is explainable.

Implement rubric:
- Reaction time (0-X points)
- Decision quality (toward exit vs toward hazard)
- Protocol adherence (exit reached, no re-entry, etc.)
- Critical errors (hard penalties)

Generate:
- Total score
- Breakdown list (why)

Done when: Score matches what you would expect from the run behavior.

## Milestone 5 - After-action report UI (product moment)

Achievement: Stakeholder-facing output looks professional.

- Build report screen (consistent branding).
- Display:
- Score
- 2-4 bullet strengths
- 2-4 bullet breakdowns
- Critical errors section
- Assigned follow-up: X

Done when: The report feels like something a risk manager would forward.

## Milestone 6 - Targeted follow-up micro-drill (SVR differentiator)

Achievement: Personalized correction exists.

- Map top failure -> micro-drill module.
- Examples:
- Delayed evacuation -> timed Find exit immediately mini-run
- Moved toward hazard -> cue recognition + immediate evacuation prompt
- After micro-drill, store follow-up completed and new score for that drill.

Done when: You can show Here is what you did wrong -> here is the fix.

## Milestone 7 - Re-audit loop (proof of improvement)

Achievement: SVR loop is complete end-to-end.

- Run shortened re-audit of core scenario.
- Compute improvement delta:
- Score before vs after
- Resolved? flag

Done when: One session demonstrates improvement, not just assessment.

## Milestone 8 - Export + pilot bundle (operational readiness)

Achievement: You can actually run a small pilot.

Export per session:
- JSON full record
- CSV summary

- Add Session list screen (last N runs).
- Add Export all + purge button (pilot-friendly).

Done when: You can run 10 people back-to-back and hand over results.

## Milestone 9 - Visual + audio polish pass (credibility)

Achievement: It does not feel like a game jam project.

- Alarm audio + muffled PA
- Smoke VFX tuned for readability
- Exit signage placed intentionally
- UI typography/spacing polished

Done when: A new viewer gets it in 30 seconds.

## XR-Readiness Track (start only after Milestone 5-8)

Do this as a parallel upgrade path, not a rewrite.

### XR Milestone A - Input abstraction

Achievement: Desktop and XR can share scenario logic.

- Create `IInteractable` interface + interaction service.
- Desktop pawn calls same service XR pawn will use.

Done when: You can swap pawn classes without touching scoring/telemetry.

### XR Milestone B - Basic XR pawn + locomotion

Achievement: Scenario runs in headset later with minimal changes.

- Add XR pawn (OpenXR/Meta XR).
- Teleport locomotion + snap turn.
- Simple grab/interact mapping.

Done when: Same scenario runs with XR controls.
