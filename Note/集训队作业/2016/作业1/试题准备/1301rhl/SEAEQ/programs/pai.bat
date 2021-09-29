:1
gen 1000 70 2000 3
SEAEQ3
SEAEQ4
fc SEAEQ.out SEAEQ.ans
if %errorlevel% equ 0 goto 1
pause