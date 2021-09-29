@echo off
echo :> look.out
for /l %%i in (20,1,100) do echo case %%i >> look.out&&echo %%i >  pyramids.in&&bc.exe&&pyramids.exe&&fc bc.out pyramids.out >> look.out