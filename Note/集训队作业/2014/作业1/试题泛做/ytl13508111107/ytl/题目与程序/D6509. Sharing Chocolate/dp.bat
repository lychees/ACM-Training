@echo off
:l
ran.exe
chocolate.exe
bc.exe
fc chocolate.out bc.out
if not errorlevel 1 goto l
pause