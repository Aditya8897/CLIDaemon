
if (!(Test-Path build)) { mkdir build }
cd build

Write-Host "Compiling projects..." -ForegroundColor Cyan
cmake .. -G "MinGW Makefiles"
cmake --build .

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed! Fix errors first." -ForegroundColor Red
    exit
}

Write-Host "Starting Daemon in a new window..." -ForegroundColor Green
Start-Process powershell -ArgumentList "-NoExit", "-Command", ".\daemon_app.exe"

Write-Host "Starting CLI..." -ForegroundColor Yellow
.\cli_app.exe
