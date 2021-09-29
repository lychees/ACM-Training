@echo off
:l
ran.exe
bc.exe
bus.exe
fc bc.out bus.out
if not errorlevel 1 goto l
pause