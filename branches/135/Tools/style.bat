@echo off
rem Cheap hack to detach actual used formatter and options from daily usage
setlocal
set STYLECMD=astyle
set STYLEOPTIONS=-T4 -caNLpDU

set STYLE="%~d0%~p0%STYLECMD%" %STYLEOPTIONS%

%STYLE%  %*

endlocal
