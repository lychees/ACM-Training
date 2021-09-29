@echo off
:l
ran.exe
bc.exe
always.exe
fc bc.out always.out
if not errorlevel 1 goto l 
pause 