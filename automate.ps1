# 1. Build folder mein jana
if (!(Test-Path build)) { mkdir build }
cd build

# 2. Compile karna (agar kuch change hua ho)
Write-Host "Compiling projects..." -ForegroundColor Cyan
cmake .. -G "MinGW Makefiles"
cmake --build .

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed! Fix errors first." -ForegroundColor Red
    exit
}

# 3. Nayi window mein Daemon start karna
Write-Host "Starting Daemon in a new window..." -ForegroundColor Green
Start-Process powershell -ArgumentList "-NoExit", "-Command", ".\daemon_app.exe"

# 4. Isi window mein CLI start karna
Write-Host "Starting CLI..." -ForegroundColor Yellow
.\cli_app.exe