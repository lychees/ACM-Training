set name=G
:a
	mkd
	std
	%name%
	fc %name%.out std.out
	if errorlevel==1 pause
goto a