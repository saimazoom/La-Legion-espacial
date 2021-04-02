
@echo Compile the tape and dsk files 
bas2tap loader.bas -a10 -sZHL
bin2tap .\res\zhl.scr -o screen.tap
REM copy /b loader.tap+screen.tap+parser.tap+p1.tap+p4.tap+p6.tap+p0.tap juego.tap
copy /b loader.tap+screen.tap+parser.tap juego.tap
..\spectrum\Spectaculator.exe juego.tap
REM cd ..\ZEsarUX_windows-9.1
REM .\zesarux.exe ..\ZHL\juego.tap
REM cd ..\ZHL