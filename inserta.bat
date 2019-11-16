@echo off
copy juego.c juego_compressed.c
textool.py -r t -i juegoc.txt -o juego_compressed.c -l 2 -c // 
