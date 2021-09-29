@echo off
:l
ran.exe
number.exe
bc.exe
fc number.out bc.out
if not errorlevel 1 goto l
pause
