@echo off
:l
ran.exe
bc.exe
hey.exe
fc bc.out hey.out
if not errorlevel 1 goto l
pause 