# PIE Smoke Test Checklist (Office Fire MVP)

Use this checklist after a successful editor build. Record pass/fail for each item.

## Setup
- [ ] Open `SVR.uproject` in the intended UE version.
- [ ] Confirm Office Fire scenario data exists at `Data/Scenarios/OfficeFire/`.
- [ ] Clear previous exported files or note their timestamps.

## Run
- [ ] Start Play-In-Editor (PIE).
- [ ] Begin Audit phase and perform a known input path (example: identify alarm, choose exit path, optional extinguisher attempt).
- [ ] End Audit and advance to Score/Report.
- [ ] Confirm report shows numeric score and at least one explainable `why` reason.
- [ ] Start assigned micro-drill.
- [ ] Complete micro-drill and launch Re-audit.
- [ ] Complete Re-audit with improved behavior on targeted action.

## Validate exports
- [ ] JSON export exists and includes: `session_id`, `participant_id`, `events`, `score`, `report`.
- [ ] CSV export exists with columns: `timestamp,event_type,phase,actor_id,outcome,score_delta`.
- [ ] At least one critical-error event is represented when intentionally triggered.

## Expected outcome
- [ ] Flow remains deterministic for repeated identical inputs.
- [ ] No network/login prompts appear.
- [ ] No `.uasset` edits were required to validate data-driven behavior.


