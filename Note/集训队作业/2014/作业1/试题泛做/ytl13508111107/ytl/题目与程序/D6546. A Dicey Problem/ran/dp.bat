@echo off
:l
ran.exe
bc.exe
dicey.exe
fc bc.out dicey.out
if not errorlevel 1 goto l
echo Wrong!
pause