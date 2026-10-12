$ErrorActionPreference = "Stop"
$fail = 0

function Normalize([string]$text) {
    return ($text -replace "`r`n", "`n")
}

foreach ($input in Get-ChildItem -LiteralPath "hw02_starter/data" -Filter "*.txt") {
    $expectedPath = Join-Path "hw02_starter/expected" $input.Name
    $actual = ((Get-Content -Raw -LiteralPath $input.FullName | & .\readings) -join "`n") + "`n"
    $expected = Get-Content -Raw -LiteralPath $expectedPath
    if ((Normalize $actual) -eq (Normalize $expected)) {
        Write-Output "PASS  regression $($input.Name)"
    } else {
        Write-Output "FAIL  regression $($input.Name)"
        $fail = 1
    }
}

$inputPath = (Resolve-Path "hw02_starter/data/edge.txt").Path
$expectedPath = "hw02_starter/expected/edge_25.txt"
$actual = ((Get-Content -Raw -LiteralPath $inputPath | & .\readings 25) -join "`n") + "`n"
$expected = Get-Content -Raw -LiteralPath $expectedPath
if ((Normalize $actual) -eq (Normalize $expected)) {
    Write-Output "PASS  regression edge.txt, threshold 25"
} else {
    Write-Output "FAIL  regression edge.txt, threshold 25"
    $fail = 1
}

exit $fail
