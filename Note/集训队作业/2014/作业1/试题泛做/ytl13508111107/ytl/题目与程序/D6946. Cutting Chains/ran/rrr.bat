@echo off
for /l %%i in (1,1,20) do copy cutting%%i.in cutting.in&&cutting.exe&&copy cutting.out cutting%%i.out
pause
exit
for /l %%i in (1,1,20) do ran.exe&&cutting.exe&&copy cutting.in cutting%%i.in&&copy cutting.out cutting%%i.out