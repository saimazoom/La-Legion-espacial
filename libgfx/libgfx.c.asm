;* * * * *  Small-C/Plus z88dk * * * * *
;  Version: 20170415-
;
;	Reconstructed for z80 Module Assembler
;
;	Module compile time: Sat Dec 28 15:28:46 2019



	MODULE	X__libgfx_libgfx


	INCLUDE "z80_crt0.hdr"


	SECTION	code_compiler


._setRAMPage
	;-----------------------------------------------------------------------
	; SetRAMPage: Establece un banco de memoria sobre $c000
	; Entrada: B = banco (0-7) a paginar entre $c000-$ffff
	;-----------------------------------------------------------------------
	; Extra�do del Manual de Usuario de Spectrum, P�gina 221
	;
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
	; ret
	ret



._setRAMBack
	ld A, ($5B5C)
	and $F8
	ld BC, $7FFD
	di
	ld ($5B5C), A
	out (C), A
	ei
	;ld a,$0F0
	;ld i,a
	;ei
	ret



._drawVline
	ret



._drawHline
	ret



._drawline
	ret



._scrollArriba
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
	ld l,a ; Ahora HL apunta a la direcci�n de la fila de destino
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
	ld e,a ; Ahora DE apunta a la direcci�n de la fila de origen
	push de
	push hl
	ld a,32
	sub b
	ld b,a
	ld ixl,b ; N�mero de columnas acopiar por scanline
	SA1loops: ; Bucle por scanline...
	ld b,ixl
	SA1loop: ; Bucle por columna
	ld a,(de)
	ld (hl),a ; Escribe el contenido de la direcci�n DE en la direcci�n apuntada por HL
	ld a,c
	cp 23 ; Si estamos en la �ltima linea de origen rellena con 0
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
	cp 24 ; La �ltima fila de origen es la 23
	jp nz,SA1start
	; Limpia la �ltima fila
	pop	de
	pop	bc
	pop	bc
	push	de
	ret



._drawRectangle
	ret



._clsScreen
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
.i_5
	ld hl, $4000 ; Inicio de la memoria de video
	ld b, 32 ; 32bytes por l�nea
	ld c, $00 ; Contador de fila de caracteres
	ld d, 4 ; 4 l�neas por caracter (alternas)
	ld e, 0 ; Contador de tercios..
	inicio: ld (hl), $FF ; Pone el Caracter actual a todo 1
	inc l ; Avanza 1 caracter a la derecha...
	dec b ; Decrementa el contador
	jr nz, inicio ; 32 veces...
	inc h
	inc h ; Salta 2 scanlines
	ld l, 0 ; Vuelve el contador de columnas a 0
	ld a, l
	add a, c ; A�ade la fila
	ld l, a
	ld b, 32 ; 32 caracteres para la siguiente fila...
	dec d ; Contador de l�neas del caracter...
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
	jp	i_3
.i_6
	ld hl, 22496 ; Inicio de la pen�ltima l�nea de la memoria de video
	ld b, 32 ; 32bytes por l�nea
	ld c, $E0 ; Contador de fila de caracteres
	ld d, 4 ; 4 l�neas por caracter (alternas)
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
	add a, c ; A�ade la fila de caracteres
	ld l, a
	ld b, 32 ; 32 caracteres para la siguiente fila...
	dec d ; Contador de l�neas del caracter...
	halt
	jr nz, inicio2 ; Se termina la fila de caracteres actual...
	ld a, e
	ld h, $47 ; Pen�ltimo Scanline...
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
	jr c, fin ; Si sale un n�mero < 0
	ld e, a
	ld h, $47 ; Reinicia el contador de scanlines...
	add a, h ; H+E
	ld h, a
	jr inicio2
	fin: nop
.i_3
	pop	de
	pop	bc
	push	de
	ret



._drawGFX
	ret



._drawSprite
	ret



._waitForAnyKey
	Wait_For_Keys_Pressed:
	XOR A ; A = 0
	IN A, (254)
	OR 224
	INC A
	JR Z, Wait_For_Keys_Pressed
	ret



._waitForNoKey
	Wait_For_Keys_NotPressed:
	XOR A ; A = 0
	IN A, (254)
	OR 224
	INC A
	JR NZ, Wait_For_Keys_NotPressed
	ret



._getKey
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
	JR NZ, Read_Keyboard_2 ; Salimos con el c�digo de la tecla
	LD IXL, 4 ; C�digo SHIFT
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
	CP '0' ; Comprueba si est� borrando...
	JR NZ, Return_Keyboard
	LD A, IXL
	CP A, 4 ; C�digo SHIFT
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
	ret



._clearchar
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
	ld	a,(hl)
	cp	#(8 % 256)
	jp	z,i_8
	jp	nc,i_8
	ld	hl,2	;const
	call	l_gintspsp	;
	ld	hl,0 % 256	;const
	pop	de
	ld	a,l
	ld	(de),a
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
	jp	i_7
.i_8
	ld	hl,0	;const
	call	l_gintspsp	;
	ld	hl,9	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	l,a
	ld	h,0
	inc	sp
	pop	bc
	pop	bc
	ret



._clear_screen
	ld	hl,16384	;const
	push	hl
	ld	hl,0	;const
	push	hl
	ld	hl,6144	;const
	push	hl
	call	memset_callee
	ld	hl,22528	;const
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,768	;const
	push	hl
	call	memset_callee
	;; Set border colour to black
	ld a,0x00
	out ($fe),a
	pop	de
	pop	bc
	push	de
	ret



._putpixel
	ret



._fzx_setat
	ld	hl,_fzx
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_fzx+1
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	l,a
	ld	h,0
	ret



._fzx_putc
	ld	hl,(_fzx)
	ld	h,0
	push	hl
	ld	hl,(_fzx+1)
	ld	h,0
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_print_char
	ret



._fzx_puts
	ld	hl,(_fzx)
	ld	h,0
	push	hl
	ld	hl,(_fzx+1)
	ld	h,0
	push	hl
	ld	hl,6	;const
	call	l_gintsp	;
	push	hl
	call	_print_string
	ret




; --- Start of Static Variables ---

	SECTION	bss_compiler

._fzx	defs	2
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
	PUBLIC	_setRAMBack
	PUBLIC	_drawGFX
	PUBLIC	_drawSprite
	PUBLIC	_fzx_setat
	PUBLIC	_fzx_putc
	PUBLIC	_fzx_puts
	EXTERN	_fzx_write
	EXTERN	_print_string
	EXTERN	_print_char
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
	PUBLIC	_fzx
	PUBLIC	_drawVline
	PUBLIC	_drawHline
	PUBLIC	_drawline
	PUBLIC	_drawRectangle
	PUBLIC	_getKey
	PUBLIC	_clearchar
	PUBLIC	_putpixel


; --- End of Scope Defns ---


; --- End of Compilation ---
