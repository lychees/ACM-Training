@echo off
:l
ran.exe
bc2.exe
box.exe
fc box.out bc2.out
if not errorlevel 1 goto l
pause