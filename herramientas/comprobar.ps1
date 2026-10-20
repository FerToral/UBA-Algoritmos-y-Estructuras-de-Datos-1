param(
    [string]$CMake = 'cmake',
    [string]$Generador = '',
    [string[]]$Bloques = @(),
    [string]$DirectorioCompilacion = ''
)
$ErrorActionPreference = 'Stop'
$raiz = Split-Path -Parent $PSScriptRoot
if (!$DirectorioCompilacion) { $DirectorioCompilacion = Join-Path $raiz 'build' }
$cmakeEjecutable = (Get-Command $CMake -ErrorAction Stop).Source
$ctest = Join-Path (Split-Path $cmakeEjecutable) $(if ($IsWindows -or $env:OS -eq 'Windows_NT') { 'ctest.exe' } else { 'ctest' })
$directorios = @(
    Get-ChildItem (Join-Path $raiz 'Laboratorios') -Directory
    Get-ChildItem (Join-Path $raiz 'Entregables') -Directory
    Get-ChildItem (Join-Path $raiz 'Trabajos-Practicos') -Directory
) | Where-Object { Test-Path (Join-Path $_.FullName 'CMakeLists.txt') }
$resultados = @()
foreach ($directorio in $directorios) {
    if ($Bloques.Count -gt 0 -and $directorio.Name -notin $Bloques) { continue }
    $categoria = Split-Path (Split-Path $directorio.FullName -Parent) -Leaf
    $destino = Join-Path (Join-Path $DirectorioCompilacion $categoria) $directorio.Name
    $argumentos = @('-S', $directorio.FullName, '-B', $destino, '-DCMAKE_BUILD_TYPE=Release')
    if ($Generador) { $argumentos += @('-G', $Generador) }
    & $cmakeEjecutable @argumentos
    if ($LASTEXITCODE -ne 0) { throw ('No configura: ' + $directorio.Name) }
    & $cmakeEjecutable --build $destino --config Release -j 2
    if ($LASTEXITCODE -ne 0) { throw ('No compila: ' + $directorio.Name) }
    & $ctest --test-dir $destino -C Release --output-on-failure
    if ($LASTEXITCODE -ne 0) { throw ('Pruebas fallidas: ' + $directorio.Name) }
    $resultados += [PSCustomObject]@{ bloque = $directorio.Name; resultado = 'correcto' }
}
if (!$resultados.Count) { throw 'No se seleccionó ningún proyecto CMake' }
$resultados | ConvertTo-Json -Depth 4
