@echo off
:l
ran.exe
bc.exe
bee.exe
fc bc.out bee.out
if not errorlevel 1 goto l
echo Wrong!
pause