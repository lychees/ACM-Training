@echo off
:l 
ran.exe
bc.exe
game.exe
fc bc.out game.out
if not errorlevel 1 goto l 
pause