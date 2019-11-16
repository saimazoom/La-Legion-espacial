del *.o
del *.sym
del *.map
zcc +zx main.c -o main.o -create-app -vn -zorg=25425 -cleanup -m -s -lndos -lfzx -lfzxfonts_utz
dir main.o 


