param(
    [string]$EngineRoot = "C:\\Program Files\\Epic Games\\UE_5.x",
    [string]$ProjectPath = "D:\\Unreal_Repositories\\SVR\\SVR.uproject",
    [string]$Target = "SVREditor",
    [string]$Platform = "Win64",
    [string]$Configuration = "Development"
)

$BuildBat = Join-Path $EngineRoot "Engine\\Build\\BatchFiles\\Build.bat"
if (-not (Test-Path $BuildBat)) {
    Write-Error "Build script not found at $BuildBat. Set -EngineRoot to your Unreal installation."
    exit 1
}

if (-not (Test-Path $ProjectPath)) {
    Write-Error "Project not found at $ProjectPath. Set -ProjectPath to SVR.uproject."
    exit 1
}

Write-Host "Building $Target ($Platform $Configuration) for project $ProjectPath"
& $BuildBat $Target $Platform $Configuration "-Project=$ProjectPath" -WaitMutex -NoHotReloadFromIDE
$exitCode = $LASTEXITCODE

if ($exitCode -ne 0) {
    Write-Error "Unreal build failed with exit code $exitCode"
    exit $exitCode
}

Write-Host "Build completed successfully."
