@echo off
:l
ran.exe
bc.exe
pirate.exe
fc bc.out pirate.out
if not errorlevel 1 goto l
pause 