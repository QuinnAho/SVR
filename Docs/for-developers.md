# FOR DEVELOPERS

Quick guide for new developers on this project.

## What SVR is

SVR (Stress-Validated Readiness) is a training check tool.

MVP loop:
Audit -> Score/Report -> Targeted Micro-Drill -> Re-audit -> Improvement delta

Current focus:
- One scenario: Office Fire
- Desktop first, XR later
- Clear, consistent scoring
- Offline JSON/CSV exports
- Anonymous participant IDs

## Current project status

This repo is still early.

Implemented:
- Unreal project setup (`SVR.uproject`)
- Basic game and plugin folders
- Data files in `Data/` (scenario, scoring rules, drills, schemas, examples)

Still mostly placeholder:
- Most runtime logic
- Many docs in `Docs/Tech`, `Docs/Pilot`, `Docs/Compliance`
- Scripts in `Scripts/`
- Tests in `Tests/`

## Repo map

- `Source/`: base game code
  - `Source/SVR/Characters/`: player character classes (current: `ASVRFirstPersonCharacter`)
  - `Source/SVR/Interaction/`: interaction interface + component
- `Plugins/SVRCore/Source/`: core systems (telemetry, scoring, UI, training, platform)
- `Content/`: Unreal assets
- `Data/`: main data files and examples
- `Docs/`: project docs
- `Skills/`: how-to playbooks
- `Scripts/`: setup and validation helpers
- `Tests/`: test files

## Setup (minimum)

- Unreal Engine 5.7
- Git + Git LFS
- Visual Studio 2022 (C++)

First steps:
1. `git lfs install`
2. `git lfs pull`
3. Open `SVR.uproject` in UE 5.7
4. Run a quick PIE test of the Office Fire flow

## How to work in this repo

- Put behavior in `Data/*.json` when possible.
- Keep scoring consistent and based on telemetry events.
- Keep UI as display only; do not hide scoring logic in UI.
- Use `Skills/*/SKILL.md` for repeat tasks.

## Hard constraints

- No secrets or credentials.
- No new cloud/network dependencies for MVP without explicit approval.
- No generative AI in scoring logic.
- Do not edit `.uasset`/`.umap` unless explicitly requested.

## Verification expectation for changes

Every meaningful change should include one of:
- A repeatable PIE checklist with expected behavior
- Automated checks (if available)
- Expected JSON/CSV output fields

Quick standards check:

`./Scripts/standards/check-standards.ps1`

## Where to start as a new engineer

1. Read `Docs/Vision/product-vision.md` and `Docs/Vision/mvp-scope.md`.
2. Review `Data/Scenarios/OfficeFire/{scenario,rubric,microdrills}.json`.
3. Run one end-to-end manual flow in PIE.
4. Make one small improvement and write down how you tested it.
