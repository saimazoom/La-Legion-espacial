;* * * * *  Small-C/Plus z88dk * * * * *
;  Version: 20170415-
;
;	Reconstructed for z80 Module Assembler
;
;	Module compile time: Mon May 08 22:11:30 2017


;# 1 "..\libgfx\libgfx.c"

	MODULE	X___libgfx_libgfx


	INCLUDE "z80_crt0.hdr"


;# 25 "..\libgfx\libgfx.h"
;extern void __CALLEE__ putPixel (unsigned char x, unsigned char y);
;extern void __CALLEE__ scrollArriba (unsigned char fila_inicial, unsigned char columna_inicial);
;extern void __CALLEE__scrollArriba2 (unsigned char linea_inicial, unsigned char num, unsigned char step);
;extern void __CALLEE__drawRectangle (unsigned char xorig, unsigned char yorig, unsigned char width, unsigned char height);
;extern void __CALLEE__ clsScreen (unsigned char effect);
;extern void __CALLEE__drawGFX (unsigned char gfxnum, unsigned char xorig, unsigned char yorig);
;extern void __CALLEE__ waitForAnyKey();
;extern void __CALLEE__drawVline (unsigned char x0, unsigned char y0, unsigned char len);
;extern void __CALLEE__drawHline (unsigned char x0, unsigned char y0, unsigned char len);
;extern void __CALLEE__clearchar (unsigned char x, unsigned char y, unsigned char color);
;extern void __CALLEE__ clear_screen (unsigned char color);
;extern void __CALLEE__ waitForNoKey();
;extern void setRAMPage (unsigned char banco);
;# 17 "D:\devel\Cafax\z88dk-win32-latest\z88dk/Lib/Config/\..\..\/include/sys/types.h"
;typedef double float_t;
;# 26
;typedef double double_t;
;# 32
;typedef unsigned int size_t;
;typedef signed int ssize_t;
;typedef unsigned long clock_t;
;typedef signed int pid_t;
;typedef unsigned char bool_t;
;typedef long time_t;
;typedef short wild_t;
;typedef unsigned long fpos_t;
;typedef unsigned char u8_t;
;typedef unsigned short u16_t;
;typedef unsigned long u32_t;
;typedef char i8_t;
;typedef short i16_t;
;typedef long i32_t;
;# 83
;typedef unsigned char uchar;
;typedef unsigned int uint;
;# 9 "D:\devel\Cafax\z88dk-win32-latest\z88dk/Lib/Config/\..\..\/include/string.h"
;extern int __LIB__ strlen(const char *s) __z88dk_fastcall;
;extern char __LIB__ *strcat(char *dst, const char *src) __smallc;
;extern int __LIB__ strcmp(const char *s1, const char *s2) __smallc;
;extern char __LIB__ *strcpy(char *dst, const char *src) __smallc;
;extern char __LIB__ *strncat(char *dst, const char src, size_t n) __smallc;
;extern int __LIB__ strncmp(char *dst, char *src, size_t n) __smallc;
;extern char __LIB__ *strncpy(char *dst, char *src, size_t n) __smallc;
;extern char __LIB__ *strrev(char *s) __z88dk_fastcall;
;extern char __LIB__ *strchr(const char *haystack, int needle) __smallc;
;extern char __LIB__ *strchrnul(const char *haystack, int needle) __smallc;
;extern char __LIB__ *strrchr(const char *haystack, int needle) __smallc;
;extern char __LIB__ *strrstrip(char *, char) __smallc;
;extern char __LIB__ *strstrip(char *, uint) __smallc;
;extern char __LIB__ *strstr(const char *haystack, const char *needle) __smallc;
;extern char __LIB__ *strrstr(const char *haystack, const char *needle) __smallc;
;extern char __LIB__ *strtok(char *s, const char *delim) __smallc;
;extern char __LIB__ *strtok_r(char *s, const char *delim, char **saveptr) __smallc;
;extern char __LIB__ *strtok_s(char *s, const char *delim, char **saveptr) __smallc;
;extern char __LIB__ *strsep(char **dp, const char *delim) __smallc;
;extern char __LIB__ *strpbrk(const char *s, const char *accept) __smallc;
;extern int __LIB__ strpos(const char *haystack, uint needle) __smallc;
;extern int __LIB__ strcspn(const char *s, const char *reject) __smallc;
;extern int __LIB__ strspn(const char *s, const char *accept) __smallc;
;extern int __LIB__ stricmp(const char *s1, const char *s2) __smallc;
;extern int __LIB__ strcasecmp(const char *s1, const char *s2) __smallc;
;extern int __LIB__ strnicmp(const char *s1, const char *s2, size_t n) __smallc;
;extern int __LIB__ strncasecmp(const char *s1, const char *s2, size_t n) __smallc;
;extern char __LIB__ *strlwr(char *s) __z88dk_fastcall;
;extern char __LIB__ *strupr(char *s) __z88dk_fastcall;
;extern uint __LIB__ strlcat(char *dest, const char *src, size_t n) __smallc;
;extern uint __LIB__ strlcpy(char *dest, const char *src, size_t n) __smallc;
;extern void __LIB__ *memset(void *m, int c, size_t n) __smallc;
;extern void __LIB__ *memcpy(void *dst, const void src,size_t n) __smallc;
;extern void __LIB__ *memmove(void *dst, const void *src, size_t n) __smallc;
;extern void __LIB__ *memchr(const void *, int c, size_t n) __smallc;
;extern void __LIB__ *memrchr(const void *, int c, size_t n) __smallc;
;extern int __LIB__ memcmp(const void *, const void *, size_t n) __smallc;
;extern void __LIB__ *memswap(void *, void *, size_t n) __smallc;
;extern void __LIB__ *memopi(void *, void *, uint, uint) __smallc;
;extern void __LIB__ *memopd(void *, void *, uint, uint) __smallc;
;extern char __LIB__ *strdup(const char *) __z88dk_fastcall;
;extern char __LIB__ *strcat_callee(char *dst, const char *src) __smallc __z88dk_callee;
;extern int __LIB__ strcmp_callee(const char *s1, const char *s2) __smallc __z88dk_callee;
;extern char __LIB__ *strcpy_callee(char *dst, const char *src) __smallc __z88dk_callee;
;extern char __LIB__ *strncat_callee(char *dst, const char *src, size_t n) __smallc __z88dk_callee;
;extern int __LIB__ strncmp_callee(const char *s1, const char *s2, size_t n) __smallc __z88dk_callee;
;extern char __LIB__ *strncpy_callee(char *dst, const char *src, size_t n) __smallc __z88dk_callee;
;extern char __LIB__ *strchr_callee(const char *s, int c) __smallc __z88dk_callee;
;extern char __LIB__ *strchrnul_callee(const char *s, int c) __smallc __z88dk_callee;
;extern char __LIB__ *strrchr_callee(const char *, int c) __smallc __z88dk_callee;
;extern char __LIB__ *strrstrip_callee(char *s, int c) __smallc __z88dk_callee;
;extern char __LIB__ *strstrip_callee(char *s, int c) __smallc __z88dk_callee;
;extern char __LIB__ *strstr_callee(const char *haystack, const char *needle) __smallc __z88dk_callee;
;extern char __LIB__ *strrstr_callee(const char *haystack, const char *needle) __smallc __z88dk_callee;
;extern char __LIB__ *strtok_callee(char *s, const char *delim) __smallc __z88dk_callee;
;extern char __LIB__ *strtok_r_callee(char *s, const char *delim, char **saveptr) __smallc __z88dk_callee;
;extern char __LIB__ *strsep_callee(char **dp, const char *delim) __smallc __z88dk_callee;
;extern char __LIB__ *strpbrk_callee(const char *s, const char *accept) __smallc __z88dk_callee;
;extern int __LIB__ strpos_callee(const char *s, int c) __smallc __z88dk_callee;
;extern int __LIB__ strcspn_callee(const char *s, const char *reject) __smallc __z88dk_callee;
;extern int __LIB__ strspn_callee(const char *s, const char *accept) __smallc __z88dk_callee;
;extern int __LIB__ stricmp_callee(const char *s1, const char *s2) __smallc __z88dk_callee;
;extern int __LIB__ strnicmp_callee(const char *s1, const char *s2, size_t n) __smallc __z88dk_callee;
;extern uint __LIB__ strlcat_callee(char *dst, const char *src, size_t n) __smallc __z88dk_callee;
;extern uint __LIB__ strlcpy_callee(char *dst, const char *src, size_t n) __smallc __z88dk_callee;
;extern void __LIB__ *memset_callee(void *dst, int c, size_t n) __smallc __z88dk_callee;
;extern void __LIB__ *memcpy_callee(void *dst, void *src,size_t n) __smallc __z88dk_callee;
;extern void __LIB__ *memmove_callee(void *dst, void *src, size_t n) __smallc __z88dk_callee;
;extern void __LIB__ *memchr_callee(const void *m, int c, size_t n) __smallc __z88dk_callee;
;extern void __LIB__ *memrchr_callee(const void *m, int c, size_t n) __smallc __z88dk_callee;
;extern int __LIB__ memcmp_callee(const void *m1, const void *m2, size_t n) __smallc __z88dk_callee;
;extern void __LIB__ *memswap_callee(void *, void *, size_t n) __smallc __z88dk_callee;
;extern void __LIB__ *memopi_callee(void *, void *, uint, uint) __smallc __z88dk_callee;
;extern void __LIB__ *memopd_callee(void *, void *, uint, uint) __smallc __z88dk_callee;
;# 181
;extern void __LIB__ *bzero(void *, size_t n) __smallc;
;extern int __LIB__ bcmp(const void *m1, const void *m2, size_t n) __smallc;
;extern void __LIB__ *bcopy(void *, void *,size_t n) __smallc;
;extern char __LIB__ *index(const char *s, int c) __smallc;
;extern char __LIB__ *rindex(const char *s, int c) __smallc;
;# 198
;extern void __LIB__ *strset(unsigned char *, unsigned char) __smallc;
;extern void __LIB__ *strnset(unsigned char *, unsigned char, uint) __smallc;
;extern int __LIB__ strcmpi(const char *s1, const char *s2) __smallc;
;extern int __LIB__ strncmpi(const char *s1, const char *s2, size_t n) __smallc;
;extern void __LIB__ *rawmemchr(const void *, uint c) __smallc;
;# 6 "..\libgfx\libgfx.c"
;void setRAMPage (unsigned char banco)
;{
	SECTION	code_compiler


._setRAMPage
	LINE	7
;#asm
	LINE	8
	;-----------------------------------------------------------------------
	; SetRAMBank: Establece un banco de memoria sobre $c000
	; Entrada: B = banco (0-7) a paginar entre $c000-$ffff
	;-----------------------------------------------------------------------
	; Extraído del Manual de Usuario de Spectrum, Página 221
	;
	DI
	ld hl, $0002
	add hl, sp
	ld a, (hl) ; A= Banco
	ld b, a
	ld A, ($5B5C)
	and $F8
	or B
	ld BC, $7FFD
	ld ($5B5C), A
	out (C), A
	ret
;}
	ret


;unsigned char getRAMPage ()
;{

._getRAMPage
	LINE	33
;#asm
	LINE	34
	;
;}
	ret


;void drawVline (unsigned char x0, unsigned char y0, unsigned char len)
;{

._drawVline
	LINE	44
;}
	ret


;void drawHline (unsigned char x0, unsigned char y0, unsigned char len)
;{

._drawHline
	LINE	49
;}
	ret


;void drawline (unsigned char x0, unsigned char y0, unsigned char len)
;{

._drawline
	LINE	54
;}
	ret


;# 66
;void scrollArriba (unsigned char fila_inicial, unsigned char columna_inicial)
;{

._scrollArriba
	LINE	67
;#asm
	LINE	68
	ld hl,$0002
	add hl,sp ; skip over return address on stack
	ld b,(hl) ; Columna inicial
	inc hl ; La pila usa 16bit de ancho, Little Endian. Termina Word1
	inc hl ; Comienza Word2
	ld c,(hl) ; Fila inicial
	ld ixh,8 ; Contador de Scanlines
	inc hl
	SA1start:
	push bc ; B=Columa inicial, C=Fila actual
	ld hl, 16384 ; Origen de pantalla Y=0, HL = 0x4000
	ld a,c ; A = fila inicial
	and $18 ; Estos dos bit indican el tercio
	or h
	ld h,a ; H Apunta al tercio correcto, Scanline =0
	ld a,c
	and $07 ; Fila 0-7
	rlca
	rlca
	rlca
	rlca
	rlca
	or b ;Bits 0-4 Columna inicial
	ld l,a ; Ahora HL apunta a la dirección de la fila de destino
	ld de, 16384 ; DE debe apuntar a la fila de origen (1 fila por debajo de HL)
	ld a,c
	inc a
	and $18 ; Estos dos bit indican el tercio
	or d
	ld d,a ; H Apunta al tercio correcto, Scanline =0
	ld a,c
	inc a ; Fila A = Fila HL+1
	and $07 ; Fila 0-7
	rlca
	rlca
	rlca
	rlca
	rlca
	or b ; Bits 0-5 Columna inicial
	ld e,a ; Ahora DE apunta a la dirección de la fila de origen
	push de
	push hl
	ld a,32
	sub b
	ld b,a
	ld ixl,b ; Número de columnas acopiar por scanline
	SA1loops: ; Bucle por scanline...
	ld b,ixl
	SA1loop: ; Bucle por columna
	ld a,(de)
	ld (hl),a ; Escribe el contenido de la dirección DE en la dirección apuntada por HL
	ld a,c
	cp 23 ; Si estamos en la última linea de origen rellena con 0
	jp nz, notfillzero
	ld (hl),0
	notfillzero:
	inc de
	inc hl
	djnz SA1loop
	; Termina de copiar todas las columnas
	pop hl
	pop de
	ld b,ixh
	djnz nextscan
	jp nextrow
	nextscan:
	ld ixh,b
	inc h
	inc d ; Incrementa DE=DE+256, siguiente scanline
	push de
	push hl
	jp SA1loops
	nextrow:
	pop bc ; B=Columa inicial, C=Fila
	ld ixh,8
	ld a,c
	inc a ;
	ld c,a ; Almacena Siguiente fila de origen
	cp 24 ; La última fila de origen es la 23
	jp nz,SA1start
	; Limpia la última fila
;}
	pop	de
	pop	bc
	pop	bc
	push	de
	ret


;void drawRectangle (unsigned char xorig, unsigned char yorig, unsigned char width, unsigned char height)
;{

._drawRectangle
	LINE	164
;}
	ret


;# 172
;void clsScreen (unsigned char effect)
;{

._clsScreen
	LINE	173
;switch (effect)
	LINE	174
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
.i_4
	ld	a,l
	cp	#(0% 256)
	jp	z,i_5
	cp	#(1% 256)
	jp	z,i_6
	jp	i_3
;{
	LINE	175
;case 0:
	LINE	176
.i_5
;#asm
	LINE	177
	ld hl, $4000 ; Inicio de la memoria de video
	ld b, 32 ; 32bytes por línea
	ld c, $00 ; Contador de fila de caracteres
	ld d, 4 ; 4 líneas por caracter (alternas)
	ld e, 0 ; Contador de tercios..
	inicio: ld (hl), $FF ; Pone el Caracter actual a todo 1
	inc l ; Avanza 1 caracter a la derecha...
	dec b ; Decrementa el contador
	jr nz, inicio ; 32 veces...
	inc h
	inc h ; Salta 2 scanlines
	ld l, 0 ; Vuelve el contador de columnas a 0
	ld a, l
	add a, c ; Añade la fila
	ld l, a
	ld b, 32 ; 32 caracteres para la siguiente fila...
	dec d ; Contador de líneas del caracter...
	halt
	jr nz, inicio ; Se termina la fila de caracteres actual...
	ld a, e
	ld h, $40
	add a, h
	ld h, a
	ld d, 4
	ld a, $20 ; Para sumar 1 al contador de filas...
	add a, c ; Suma 1 al contador de filas...
	ld c, a
	ld l, a ; La parte baja de HL contiene ZZZ00000
	jr nc, inicio ; Fin de Tercio
	ld c, $00
	ld l, 0
	ld b, 32
	ld a, e
	add a, 8 ; Incrementa el contador de tercios
	ld e, a
	ld h, $40 ; Reinicia el contador de scanlines...
	add a, h ; H+E
	ld h, a
	cp $58
	jr nz, inicio
;break;
	LINE	224
	jp	i_3
;case 1:
	LINE	225
.i_6
;#asm
	LINE	226
	ld hl, 22496 ; Inicio de la penúltima línea de la memoria de video
	ld b, 32 ; 32bytes por línea
	ld c, $E0 ; Contador de fila de caracteres
	ld d, 4 ; 4 líneas por caracter (alternas)
	ld e, $10 ; Contador de tercios..., Tercer Tercio
	inicio2:
	ld (hl), $FF ; Pone el Caracter actual a todo 1
	inc l ; Avanza 1 caracter a la derecha...
	dec b ; Decrementa el contador
	jr nz, inicio2 ; 32 veces...
	dec h
	dec h ; Salta 2 scanlines
	ld l, 0 ; Vuelve el contador de columnas a 0
	ld a, l
	add a, c ; Añade la fila de caracteres
	ld l, a
	ld b, 32 ; 32 caracteres para la siguiente fila...
	dec d ; Contador de líneas del caracter...
	halt
	jr nz, inicio2 ; Se termina la fila de caracteres actual...
	ld a, e
	ld h, $47 ; Penúltimo Scanline...
	add a, h
	ld h, a ; H = 0x46 + E
	ld d, 4
	ld a, c ; Para sumar 1 al contador de filas...
	sub a, $20 ; Resta 1 al contador de filas...
	ld c, a
	ld l, a ; La parte baja de HL contiene ZZZ00000
	jr nc, inicio2 ; Fin de Tercio
	ld c, $E0
	ld l, c
	ld b, 32
	ld a, e
	sub a, 8 ; Decrementa el contador de tercios
	jr c, fin ; Si sale un número < 0
	ld e, a
	ld h, $47 ; Reinicia el contador de scanlines...
	add a, h ; H+E
	ld h, a
	jr inicio2
	fin: nop
;break;
	LINE	276
	jp	i_3
;}
.i_3
;}
	pop	de
	pop	bc
	push	de
	ret


;void drawGFX (unsigned char gfxnum, unsigned char xorig, unsigned char yorig)
;{

._drawGFX
	LINE	281
;}
	ret


;void waitForAnyKey()
;{

._waitForAnyKey
	LINE	289
;#asm
	LINE	290
	Wait_For_Keys_Pressed:
	XOR A ; A = 0
	IN A, (254)
	OR 224
	INC A
	JR Z, Wait_For_Keys_Pressed
;}
	ret


;void waitForNoKey()
;{

._waitForNoKey
	LINE	303
;#asm
	LINE	304
	Wait_For_Keys_NotPressed:
	XOR A ; A = 0
	IN A, (254)
	OR 224
	INC A
	JR NZ, Wait_For_Keys_NotPressed
;}
	ret


;unsigned char getKey()
;{

._getKey
	LINE	317
;#asm
	LINE	318
	Read_Keyboard: LD HL,Keyboard_Map ; Point HL at the keyboard list
	LD D,8 ; This is the number of ports (rows) to check
	LD C,0xFE ; C is always FEh for reading keyboard ports
	LD IXL,0
	Read_Keyboard_0: LD B,(HL) ; Get the keyboard port address from table
	INC HL ; Increment to list of keys
	IN A,(C) ; Read the row of keys in
	AND 0x1F ; We are only interested in the first five bits
	LD E,5 ; This is the number of keys in the row
	Read_Keyboard_1: SRL A ; Shift A right; bit 0 sets carry bit
	JR C,nokey ; If the bit is 1, we have not found our key
	LD B,A
	LD A,(HL)
	CP '#' ; No retorna con la tecla SHIFT
	JR NZ, Read_Keyboard_2 ; Salimos con el código de la tecla
	LD IXL, 4 ; Código SHIFT
	LD A,B
	nokey: INC HL ; Go to next table address
	DEC E ; Decrement key loop counter
	JR NZ,Read_Keyboard_1 ; Loop around until this row finished
	DEC D ; Decrement row loop counter
	JR NZ,Read_Keyboard_0 ; Loop around until we are done
	AND A ; Clear A (no key found)
	JR Z, Read_Keyboard
	Read_Keyboard_2:
	LD A,(HL) ; We have found a key at this point; fetch the character code!
	CP '0' ; Comprueba si está borrando...
	JR NZ, Return_Keyboard
	LD A, IXL
	CP A, 4 ; Código SHIFT
	JR Z, Return_Keyboard
	LD A, 4
	Return_Keyboard: LD H,0
	LD L,A
	RET
	Keyboard_Map: DEFB 0xFE,'#','z','x','c','v'
	DEFB 0xFD,'a','s','d','f','g'
	DEFB 0xFB,'q','w','e','r','t'
	DEFB 0xF7,'1','2','3','4','5'
	DEFB 0xEF,'0','9','8','7','6'
	DEFB 0xDF,'p','o','i','u','y'
	DEFB 0xBF,13,'l','k','j','h'
	DEFB 0x7F,' ',';','m','n','b'
;}
	ret


;void clearchar (unsigned char x, unsigned char y, unsigned char color)
;{

._clearchar
	LINE	366
;# 380
;unsigned char i;
	LINE	380
;unsigned char *video = (unsigned char*)(0x4000|( (y&0x18)<<8) | ((y&0x07)<<5)| x);
	LINE	381
	dec	sp
	ld	hl,5	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	a,l
	and	24
	ld	l,a
	ld	h,l
	ld	l,0
	set	6,h
	push	hl
	ld	hl,7	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	a,l
	and	7
	ld	l,a
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	call	l_or
	ex	de,hl
	ld	hl,9-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_or
	push	hl
;unsigned char *attr = (unsigned char*)(0x5800+x+(y*32));
	LINE	382
	ld	hl,9	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,22528
	add	hl,de
	push	hl
	ld	hl,9	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,32
	call	l_mult
	pop	de
	add	hl,de
	push	hl
;for (i=0;i<8;i++)
	LINE	384
	ld	hl,4	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_9
.i_7
	ld	hl,4	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
.i_9
	ld	hl,4	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,8	;const
	call	l_ult
	jp	nc,i_8
;{
	LINE	385
;*video = 0x00;
	LINE	386
	ld	hl,2	;const
	call	l_gintspsp	;
	ld	hl,0 % 256	;const
	pop	de
	ld	a,l
	ld	(de),a
;video+=256;
	LINE	387
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	bc,256
	add	hl,bc
	pop	de
	pop	bc
	push	hl
	push	de
;}
	jp	i_7
.i_8
;*attr = color;
	LINE	390
	ld	hl,0	;const
	call	l_gintspsp	;
	ld	hl,9	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	l,a
	ld	h,0
;}
	inc	sp
	pop	bc
	pop	bc
	ret


;void clear_screen (unsigned char color)
;{

._clear_screen
	LINE	394
;memset_callee(16384,0,6144);
	LINE	396
;16384;
	ld	hl,16384	;const
	push	hl
;0;
	ld	hl,0	;const
	push	hl
;6144;
	ld	hl,6144	;const
	push	hl
	call	memset_callee
;memset_callee(22528,color,768);
	LINE	397
;22528;
	ld	hl,22528	;const
	push	hl
;color;
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
;768;
	ld	hl,768	;const
	push	hl
	call	memset_callee
;#asm
	LINE	398
	;; Set border colour to black
	ld a,0x00
	out ($fe),a
;}
	pop	de
	pop	bc
	push	de
	ret


;void putpixel (unsigned char x, unsigned char y, unsigned char value)
;{

._putpixel
	LINE	409
;# 424
;}
	ret




; --- Start of Static Variables ---

	SECTION	bss_compiler

	SECTION	code_compiler



; --- Start of Scope Defns ---

	EXTERN	_putPixel
	PUBLIC	_scrollArriba
	EXTERN	___CALLEE__scrollArriba2
	EXTERN	___CALLEE__drawRectangle
	PUBLIC	_clsScreen
	EXTERN	___CALLEE__drawGFX
	PUBLIC	_waitForAnyKey
	EXTERN	___CALLEE__drawVline
	EXTERN	___CALLEE__drawHline
	EXTERN	___CALLEE__clearchar
	PUBLIC	_clear_screen
	PUBLIC	_waitForNoKey
	PUBLIC	_setRAMPage
	EXTERN	strlen
	EXTERN	strcat
	EXTERN	strcmp
	EXTERN	strcpy
	EXTERN	strncat
	EXTERN	strncmp
	EXTERN	strncpy
	EXTERN	strrev
	EXTERN	strchr
	EXTERN	strchrnul
	EXTERN	strrchr
	EXTERN	strrstrip
	EXTERN	strstrip
	EXTERN	strstr
	EXTERN	strrstr
	EXTERN	strtok
	EXTERN	strtok_r
	EXTERN	strtok_s
	EXTERN	strsep
	EXTERN	strpbrk
	EXTERN	strpos
	EXTERN	strcspn
	EXTERN	strspn
	EXTERN	stricmp
	EXTERN	strcasecmp
	EXTERN	strnicmp
	EXTERN	strncasecmp
	EXTERN	strlwr
	EXTERN	strupr
	EXTERN	strlcat
	EXTERN	strlcpy
	EXTERN	memset
	EXTERN	memcpy
	EXTERN	memmove
	EXTERN	memchr
	EXTERN	memrchr
	EXTERN	memcmp
	EXTERN	memswap
	EXTERN	memopi
	EXTERN	memopd
	EXTERN	strdup
	EXTERN	strcat_callee
	EXTERN	strcmp_callee
	EXTERN	strcpy_callee
	EXTERN	strncat_callee
	EXTERN	strncmp_callee
	EXTERN	strncpy_callee
	EXTERN	strchr_callee
	EXTERN	strchrnul_callee
	EXTERN	strrchr_callee
	EXTERN	strrstrip_callee
	EXTERN	strstrip_callee
	EXTERN	strstr_callee
	EXTERN	strrstr_callee
	EXTERN	strtok_callee
	EXTERN	strtok_r_callee
	EXTERN	strsep_callee
	EXTERN	strpbrk_callee
	EXTERN	strpos_callee
	EXTERN	strcspn_callee
	EXTERN	strspn_callee
	EXTERN	stricmp_callee
	EXTERN	strnicmp_callee
	EXTERN	strlcat_callee
	EXTERN	strlcpy_callee
	EXTERN	memset_callee
	EXTERN	memcpy_callee
	EXTERN	memmove_callee
	EXTERN	memchr_callee
	EXTERN	memrchr_callee
	EXTERN	memcmp_callee
	EXTERN	memswap_callee
	EXTERN	memopi_callee
	EXTERN	memopd_callee
	EXTERN	bzero
	EXTERN	bcmp
	EXTERN	bcopy
	EXTERN	index
	EXTERN	rindex
	EXTERN	strset
	EXTERN	strnset
	EXTERN	strcmpi
	EXTERN	strncmpi
	EXTERN	rawmemchr
	PUBLIC	_getRAMPage
	PUBLIC	_drawVline
	PUBLIC	_drawHline
	PUBLIC	_drawline
	PUBLIC	_drawRectangle
	PUBLIC	_drawGFX
	PUBLIC	_getKey
	PUBLIC	_clearchar
	PUBLIC	_putpixel


; --- End of Scope Defns ---


; --- End of Compilation ---
