@echo off
:l
ran.exe
routing.exe
bc.exe
fc bc.out routing.out
if not errorlevel 1 goto l
pause