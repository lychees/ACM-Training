@echo off
for /l %%i in (11,1,20) do ran2.exe&&trash.exe&&copy trash.in trash%%i.in&&copy trash.out trash%%i.out