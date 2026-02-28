#!/usr/bin/env bash
set -euo pipefail

ENGINE_ROOT="${ENGINE_ROOT:-/path/to/UnrealEngine-5.x}"
PROJECT_PATH="${PROJECT_PATH:-/path/to/SVR/SVR.uproject}"
TARGET="${TARGET:-SVREditor}"
PLATFORM="${PLATFORM:-Linux}"
CONFIGURATION="${CONFIGURATION:-Development}"

BUILD_SH="$ENGINE_ROOT/Engine/Build/BatchFiles/Linux/Build.sh"
if [[ ! -f "$BUILD_SH" ]]; then
  echo "Build script not found at $BUILD_SH. Set ENGINE_ROOT." >&2
  exit 1
fi

if [[ ! -f "$PROJECT_PATH" ]]; then
  echo "Project not found at $PROJECT_PATH. Set PROJECT_PATH." >&2
  exit 1
fi

echo "Building $TARGET ($PLATFORM $CONFIGURATION) for project $PROJECT_PATH"
"$BUILD_SH" "$TARGET" "$PLATFORM" "$CONFIGURATION" "-Project=$PROJECT_PATH" -WaitMutex -NoHotReloadFromIDE

echo "Build completed successfully."
