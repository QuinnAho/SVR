# Coding Standards

Practical standards for this codebase. Keep this strict enough to scale, but simple enough to follow daily.

## C++ naming

- Classes start with `SVR` and use Unreal prefixes (`A`, `U`, `F`, `E`, `I`).
- File names match class names (for example `SVRFirstPersonCharacter.h/.cpp`).
- Function and variable names use PascalCase.
- `bool` fields start with `b` (for example `bDrawDebugTrace`).

## C++ structure

- Put one feature per folder under `Source/SVR/` (for example `Characters`, `Interaction`).
- Keep module bootstrap files only at `Source/SVR/` root.
- Put shared systems in C++; keep per-object behavior in Blueprint.
- Prefer composition (`UActorComponent`) over large monolithic character classes.

## Blueprint rules

- Keep heavy logic out of Level Blueprints.
- Use interfaces for cross-actor behavior (`SVRInteractable` pattern).
- Keep Blueprint names explicit: `BP_<Feature><Type>`.
- Implement interaction logic in interface graphs, not input nodes on each actor.

## Documentation naming

- Use lowercase kebab-case for markdown files in `Docs/`.
- Keep docs short, high-level, and task-oriented.
- Update docs when changing architecture or conventions.

## Verification

- Build after C++ changes.
- For gameplay changes, include a short PIE checklist with expected behavior.
- For scenario/scoring changes, include expected JSON/CSV outputs when applicable.

## Automated standards check

Run:

```powershell
./Scripts/standards/check-standards.ps1
```

This script validates:

- docs markdown naming convention
- C++ filename conventions in `Source/SVR/`
