@echo off
:l
ran.exe
bc.exe
calculate.exe
fc bc.out calculate.out
if not errorlevel 1 goto l
pause