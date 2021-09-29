@echo off
:l
ran.exe
structure.exe
copy structure.in temp.out
copy structure.out structure.in
structure.exe
fc structure.out temp.out
if not errorlevel 1 goto l
pause