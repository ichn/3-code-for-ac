@echo off
:loop
gen.exe
std.exe
5798.exe
fc std.out 5798.out
if not errorlevel 1 goto loop
pause
end
