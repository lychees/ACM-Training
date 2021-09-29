@echo off
for /l %%i in (1,1,20) do copy degree%%i.in degree.in&&degree.exe&&copy degree.out degree%%i.out
exit
for /l %%i in (7,1,20) do ran.exe&&degree.exe&&copy degree.in degree%%i.in&&copy degree.out degree%%i.out