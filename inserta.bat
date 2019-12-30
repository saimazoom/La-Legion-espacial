@echo off
copy juego.c juego_compressed.c
textool.py -r t -i juego.txt -o juego.c -l 2 -c // 
