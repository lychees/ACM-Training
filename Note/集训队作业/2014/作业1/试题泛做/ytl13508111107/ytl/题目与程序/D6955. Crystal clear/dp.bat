@echo off
:l
ran.exe
bc.exe
clear.exe
fc bc.out clear.out
if not errorlevel 1 goto l
pause