del *.o
del *.sym
del *.map
del *.tap
del *.err

@echo ===================================
@echo Text Compression
@echo ===================================

@echo Extrae Texto Parser
F:\devel\python27\python.exe textool.py -x t -i juego.c -o juego.txt -c // -l 2
REM textool.py -x t -i parser.c -o parser.txt -c // -l 2
@echo Comprime Texto y genera el diccionario
F:\devel\python27\python.exe tc.py -i juego.txt -o juegoc.txt -l 0 

@echo Inserta Texto Parser
copy juego.c juego_compressed.c
F:\devel\python27\python.exe textool.py -r t -i juegoc.txt -o juego_compressed.c -l 2 -c // 

@echo ===================================
@echo Compila Parser (Pass 1)
@echo ===================================


zcc --no-crt crt0_base.asm .\libgfx\libgfx.c parser.c juego_compressed.c zx_saddrpdown.asm -o parser.bin -vn -O3 -lfzx -lfzxfonts_utz -lzx7 -m -cleanup 
copy parser.def parser_def.asm

appmake +zx -b parser.bin -o parser.tap --noloader --org 24200

dir *.bin


