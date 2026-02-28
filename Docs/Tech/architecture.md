# Architecture

High-level architecture for the current MVP codebase.

## Design goals

- Keep scenario logic deterministic.
- Keep reusable systems in C++.
- Keep scenario-specific behavior data-driven or in focused Blueprints.
- Keep desktop and XR paths sharing the same core logic.

## Source folder architecture

`Source/SVR/` is organized by feature:

```text
Source/SVR/
  Characters/
    SVRFirstPersonCharacter.h/.cpp
  Interaction/
    SVRInteractable.h/.cpp
    SVRInteractionComponent.h/.cpp
  SVR.h/.cpp
  SVRBootstrap.h/.cpp
  SVR.Build.cs
```

- `Characters/` holds player-facing character classes.
- `Interaction/` holds interaction contracts and runtime systems.
- Root files hold module bootstrap and entry code.

## Gameplay flow (desktop interaction)

1. Player presses `InteractAction` (`E`).
2. `ASVRFirstPersonCharacter` calls `USVRInteractionComponent::TryInteract()`.
3. Interaction component line traces from player view.
4. If focused actor implements `ISVRInteractable`, call `Interact`.
5. Actor-specific Blueprint logic handles the actual response (door, button, etc.).

## Asset-side expectations

- Game mode should use a pawn based on `ASVRFirstPersonCharacter`.
- Interactable actors should implement `SVRInteractable` in Blueprint.
- Prompt text should come from `GetInteractPromptText` when provided.

## Backward compatibility

- `DefaultEngine.ini` includes a class redirect from `SVRHeadCameraCharacter` to `SVRFirstPersonCharacter`.
- This prevents older Blueprint references from breaking after the rename.
