param(
    [string]$RepoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\\..")).Path
)

$ErrorActionPreference = "Stop"
$issues = [System.Collections.Generic.List[string]]::new()

function Add-Issue {
    param([string]$Message)
    $issues.Add($Message)
}

$docsRoot = Join-Path $RepoRoot "Docs"
if (Test-Path $docsRoot) {
    Get-ChildItem -Path $docsRoot -Recurse -File -Filter "*.md" | ForEach-Object {
        if ($_.Name -notmatch "^[a-z0-9][a-z0-9-]*\.md$") {
            Add-Issue "Docs markdown file should be lowercase kebab-case: $($_.FullName)"
        }
    }
}

$sourceRoot = Join-Path $RepoRoot "Source\\SVR"
$allowedModuleRootFiles = @(
    "SVR.Build.cs",
    "SVR.cpp",
    "SVR.h",
    "SVRBootstrap.cpp",
    "SVRBootstrap.h"
)

if (Test-Path $sourceRoot) {
    Get-ChildItem -Path $sourceRoot -File | ForEach-Object {
        if ($allowedModuleRootFiles -notcontains $_.Name) {
            Add-Issue "Source/SVR root should only contain module files. Move this file into a feature folder: $($_.FullName)"
        }
    }

    $cppFiles = Get-ChildItem -Path $sourceRoot -Recurse -File | Where-Object {
        $_.Extension -in @(".h", ".cpp")
    }

    foreach ($file in $cppFiles) {
        $baseName = [System.IO.Path]::GetFileNameWithoutExtension($file.Name)
        if ($baseName -notmatch "^SVR([A-Z][A-Za-z0-9]*)?$") {
            Add-Issue "C++ file should start with SVR and use PascalCase: $($file.FullName)"
        }
    }

    $byBase = @{}
    foreach ($file in $cppFiles) {
        $baseName = [System.IO.Path]::GetFileNameWithoutExtension($file.Name)
        if (-not $byBase.ContainsKey($baseName)) {
            $byBase[$baseName] = @()
        }
        $byBase[$baseName] += $file.Extension
    }

    foreach ($entry in $byBase.GetEnumerator()) {
        if (($entry.Value -contains ".h") -and -not ($entry.Value -contains ".cpp")) {
            Add-Issue "Missing .cpp pair for $($entry.Key).h"
        }
        if (($entry.Value -contains ".cpp") -and -not ($entry.Value -contains ".h")) {
            Add-Issue "Missing .h pair for $($entry.Key).cpp"
        }
    }
}

if ($issues.Count -gt 0) {
    Write-Host "Standards check failed:"
    foreach ($issue in $issues) {
        Write-Host " - $issue"
    }
    exit 1
}

Write-Host "Standards check passed."
exit 0
