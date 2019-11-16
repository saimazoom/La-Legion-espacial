#include "libgfx.h"
#include "fzx.h"
#include "fzxfonts_utz.h"
// 1.5Kb para la librería de fuentes

#define BYTE unsigned char
#define WORD unsigned int

void putPixel (BYTE x, BYTE y);
void scrollArriba (BYTE pixels);
void scrollArriba2 (BYTE num, BYTE step);
void drawRectangle (BYTE xorig, BYTE yorig, BYTE width, BYTE height);
void clsScreen (BYTE effect); // Distintos efectos para borrar la pantalla...
void drawGFX (BYTE gfxnum, BYTE xorig, BYTE yorig);
void printat (BYTE x, BYTE y, unsigned char *texto);
void setRAMBank (BYTE banco);
void waitForAnyKey();
void prints (unsigned char *texto);

BYTE x_scr, y_scr;

void main (void)
{
	// Puntos aleatorios en pantalla...
	fzx.font = ff_utz_Handpress;
	fzx.y=0;
	fzx.x=0;
	prints ("Entre arenas abrasadoras y un sol implacable se elevan majestuosos los monumentos de Cafax y Aceps.\n\n");
	putpixel (10,10);
	prints ("Entre arenas abrasadoras y un sol implacable se elevan majestuosos los monumentos de Cafax y Aceps.\n\n");
	prints ("Entre arenas abrasadoras y un sol implacable se elevan majestuosos los monumentos de Cafax y Aceps.\n\n");
	prints ("Entre arenas abrasadoras y un sol implacable se elevan majestuosos los monumentos de Cafax y Aceps.\n\n");
	prints ("Entre arenas abrasadoras y un sol implacable se elevan majestuosos los monumentos de Cafax y Aceps.\n\n");

	waitForanyKey();

    scrollArriba2 (2,1);
    scrollArriba2 (1,2);
    scrollArriba2 (25,4);
    scrollArriba2 (1,2);
    scrollArriba2 (2,1);

	while(1);

}

void prints (unsigned char *texto)
{
	fzx_puts(texto);
}

void setRAMBank (BYTE banco)
{
	#asm
;-----------------------------------------------------------------------
; SetRAMBank: Establece un banco de memoria sobre $c000
; Entrada: B = banco (0-7) a paginar entre $c000-$ffff
;-----------------------------------------------------------------------
     ld hl, 2
     add hl, sp
     ld a, (hl)

     ld b, a
     ld  A, ($5B5C)
     and $F8
     or  B
     ld  BC, $7FFD
     ld  ($5B5C), A
     out (C), A
   #endasm
}

void drawVline (BYTE x0, BYTE y0, BYTE len)
{
#asm

#endasm

}

void drawHline (BYTE x0, BYTE y0, BYTE len)
{
#asm

#endasm
}


void putpixel (BYTE x, BYTE y)
{
	// http://www.z88dk.org/forum/viewtopic.php?id=9177
	// En la pila RET ADDRESS(2bytes), BYTE Y, BYTE X
	/* Otra forma:
	   #asm
		pop bc   ; bc = ret address
		pop hl   ; hl = int b
		pop de  ; de = int a
		push bc  ; put the return address back
	*/
   // Formato de memoria: 010xxYYY ZZZCCCCC
   // xx: Tercio
   // YYY: Scan Line 0-7
   // ZZZ: Caracter 0-7 Fila
   // CCCC: Columna 0-31

	#asm
	ld	hl, 2
	add hl, sp ; Salta la RET ADDRESS
	ld a, (hl) ; A = X
	inc hl
	ld b, (hl) ; B = Y


	#endasm
}
void scrollArriba2 (BYTE num, BYTE step)
{
    // Scroll Vertical configurable

    #asm
            ld      hl,2
            add     hl,sp        ; skip over return address on stack
            ld      c,(hl)       ; Step en pixels ( DE= step * 256)
            inc     hl           ; La pila usa 16bit de ancho, Little Endian. Termina Word1
            inc     hl           ; Comienza Word2
            ld      b, (hl)      ; Número de veces a repetir el scroll

    SAstart:
            push    bc
            ld      hl,16384    ; Origen siempre comienza en Y=0
            ld      a,c         ; El Step nos indica cual es la primera línea de origen
            add     h           ;
            ld      d,a         ; DE = 16384+256*Step.
            ld      e,0         ; Siempre comienza en fila=0/Columna=0
            ld      b,32        ; 32 columnas. El 0 también cuenta...

    SAloop0:                    ; Copia toda la fila....
            ld      a,(de)
            ld      (hl),a      ; Escribe el contenido de la dirección DE en la dirección apuntada por HL
            inc     de
            inc     hl
            djnz    SAloop0     ; Fin del scanline actual...
            dec     de
            dec     hl
            push    de
            push    hl
            call    SAcalc      ; Incrementa en '1' el scanline y recalcula la dirección de comienzo de línea.
            pop     hl
            pop     de
            push    hl
            push    de
            call    SAcalc
            pop     DE          ; DE y HL contienen las direcciones finales.
            pop     hl
            ld      b,32        ; 32 columnas. El 0 también cuenta...
            ld      a, d
            cp      0x58         ; más allá del último tercio
            jp      nz,SAloop0
            pop     bc
            djnz    SAstart

    SAcalc:
            pop     hl          ; Dirección de retorno...
            pop     de          ; El dato que necesitamos

            ld      a,e
            and     0xE0        ; Resetea el contador de columnas
            ld      e,a
            ld      a,d
            and     a,0x07      ; Nos quedamos con los bits del scanline
            cp      a,7         ; Scanline=7 -> Cambio de caracter.
            jr      nz,SAcar    ; Seguimos dentro de la misma fila...

            ld      a,d
            and     a,0xF8      ; Resetea el contador de scanlines
            ld      d,a         ; D=A

            ld      a,0x20
            add     e           ; Incrementa el contador de fila
            ld      e,a
            jr      nc,SANcar   ; No hay cambio de tercio
 tercios:
            ld     a, 0x08     ; Si hay cambio de tercio incrementa el contador DE
            add    d
    ;        cp     0x58         ; más allá del último tercio
            ld     d,a
            ld     e,0
            jp     SANcar

    SAcar:
            inc     d           ; Siguiente scanline
    SANcar: push    de
            push    hl          ; Dirección de retorno...
            ret
    #endasm

}
void scrollArriba (BYTE num)
{
// Microhobby: Microficha R-21
// Recuerda que en estos tiempos: Abcisas: Y, Ordenadas: X.
// http://z88dk.org/wiki/doku.php?id=usage:stackframe

    #asm
            ld      hl,2
            add     hl,sp               ; skip over return address on stack
            ld      b,(hl)              ; Step en pixels ( Pixels * 256)
            ;inc     hl                  ; La pila usa 16bit de ancho, Little Endian. Termina Word1
            ;inc     hl                  ; Comienza Word2
            ;ld      b,(hl)              ; Número de scrolles
    start:
            push    bc

            ld      hl, 16384 ; Primer byte de la memoría de vídeo
            ld      de, 16640 ; Una línea de píxeles abajo: 16384+32*8 = 16384 + 256, 0x4100
            ld      a,  192   ; Número de líneas totales
            ;sub     c         ; C = 192 - Número de píxeles a saltar
            ld      c,  a     ;

    blnpix: ld      b,  32    ; Contador de columnas
    bcolum: ld      a, (de)   ; Byte de origen
            ld      (hl),a    ; Escribe en destino
            ld      a,c       ; Contador de líneas
            cp      2         ; Compara si es la última
            jr      nz, proxby ; Salta a la próxima columna
            xor     a         ; Si era la última la borra
            ld      (de),a    ; Escribe en destino...
    proxby: inc     de
            inc     hl
            djnz    bcolum    ; Decrementa B y lo compara con Cero, Bucle de columnas...
                              ; Fin de la columna...
            push    de        ; Guarda puntero
            ld      de, 224   ; Dist a próxima línea... (256-32)
            add     hl, de      ; HL próxima línea
            ex      (sp), hl    ; Recupera DE en HL
            add     hl,de       ; HL = Próxima línea
            ex      de, hl
            pop     hl
            dec     c         ; Decrementa contador de lineas
            ld      a,c       ; A = C
            and     7         ; C & 0000 0111, Múltiplo 8
            jr      z, scarde ; Siguiente caracter destino
            cp      1         ; Si es múltiplo de 8-1
            jr      z, scaror ; Siguiente caracter origen
            jr      blnpix
    scarde: push    de         ; Guarda puntero origen
            ld      de, 2016    ; 2K-32
            sbc     hl,de       ; HLProx lin caracters
            pop     de          ; Recupera puntero origen
            ld      a,c     ; Contador líneas
            and     63      ; Si no es múltiplo de 64
            jr      nz, blnpix  ; Siguiente línea...
    sterde:
            ld      a,7     ; Suma 792 al destino
            add     a,h     ; Para cambiar el tercio
            ld      h,a
            jr      blnpix  ; siguiente línea píxeles
    scaror: push    hl      ; Guarda puntero destino
            ex      de,hl   ; Intercmbio regs
            ld      de, 2016; 2K-32
            sbc     hl,de   ; HL=prox lin cars
            ex      de,hl   ; Intercambia regs
            pop     hl      ; Recupera puntero origen
            ld      a,c     ; Contador líneas
            and     63      ; Si no es múltiplo 64
            cp      1       ; siguiente línea
            jr      nz, blnpix
    steror: ld      a,7     ; Suma 1792 al origen
            add     a,d     ; para cambiar de tercio
            ld      d,a     ; Contador líneas
            ld      a,c
            cp      1       ; Si no se ha acabado
            jr      nz, blnpix  ; Siguiente línea

            pop     bc
            djnz    start

	#endasm

}

void drawRectangle (BYTE xorig, BYTE yorig, BYTE width, BYTE height)
{

}
   // Formato de memoria: 010xxYYY ZZZCCCCC
   // xx: Tercio
   // YYY: Scan Line 0-7
   // ZZZ: Caracter 0-7 Fila
   // CCCC: Columna 0-31

void clscreen (BYTE effect)
{
	switch (effect)
	{
		case 0: // Persiana arriba-abajo
		#asm
			ld  	hl, 0x4000      ; Inicio de la memoria de video
			ld 		b, 	32          ; 32bytes por línea
			ld      c,  0x00        ; Contador de fila de caracteres
			ld      d,  4           ; 4 líneas por caracter (alternas)
			ld      e,  0           ; Contador de tercios..
    inicio: ld 		(hl), 0xFF		; Pone el Caracter actual a todo 1
			inc 	l               ; Avanza 1 caracter a la derecha...
			dec		b			    ; Decrementa el contador
			jr		nz, inicio      ; 32 veces...
			inc		h
			inc     h               ; Salta 2 scanlines
			ld      l,  0           ; Vuelve el contador de columnas a 0
			ld      a,  l
			add     a,  c           ; Añade la fila
			ld      l,  a
			ld 		b, 	32          ; 32 caracteres para la siguiente fila...
			dec     d               ; Contador de líneas del caracter...
			halt
			jr      nz, inicio      ; Se termina la fila de caracteres actual...
            ld      a,  e
            ld      h,  0x40
            add     a,  h
            ld      h,  a
            ld      d,  4
            ld      a,  0x20        ; Para sumar 1 al contador de filas...
            add     a,  c           ; Suma 1 al contador de filas...
            ld      c,  a
            ld      l,  a           ; La parte baja de HL contiene ZZZ00000
            jr      nc, inicio      ; Fin de Tercio

            ld      c,  0x00
            ld      l,  0
            ld      b,  32

            ld      a,  e
            add     a,  0x08         ; Incrementa el contador de tercios
            ld      e,  a
            ld      h,  0x40        ; Reinicia el contador de scanlines...
            add     a,  h           ; H+E
            ld      h,  a
            cp      0x58
            jr      nz, inicio
		#endasm
		break;
	case 1: // Persiana abajo-arriba

		#asm
			ld  	hl, 22496       ; Inicio de la penúltima línea de la memoria de video
			ld 		b, 	32          ; 32bytes por línea
			ld      c,  0xE0        ; Contador de fila de caracteres
			ld      d,  4           ; 4 líneas por caracter (alternas)
			ld      e,  0x10        ; Contador de tercios..., Tercer Tercio
    inicio2: ld 		(hl), 0xFF		; Pone el Caracter actual a todo 1
			inc 	l               ; Avanza 1 caracter a la derecha...
			dec		b			    ; Decrementa el contador
			jr		nz, inicio2     ; 32 veces...
			dec		h
			dec     h               ; Salta 2 scanlines
			ld      l,  0           ; Vuelve el contador de columnas a 0
			ld      a,  l
			add     a,  c           ; Añade la fila de caracteres
			ld      l,  a
			ld 		b, 	32          ; 32 caracteres para la siguiente fila...
			dec     d               ; Contador de líneas del caracter...
			halt
			jr      nz, inicio2      ; Se termina la fila de caracteres actual...

            ld      a,  e
            ld      h,  0x47        ; Penúltimo Scanline...
            add     a,  h
            ld      h,  a           ; H = 0x46 + E
            ld      d,  4

            ld      a,  c            ; Para sumar 1 al contador de filas...
            sub     a,  0x20         ; Resta 1 al contador de filas...
            ld      c,  a
            ld      l,  a           ; La parte baja de HL contiene ZZZ00000
            jr      nc, inicio2      ; Fin de Tercio

            ld      c,  0xE0
            ld      l,  c
            ld      b,  32

            ld      a,  e
            sub     a,  0x08         ; Decrementa el contador de tercios
            jr      c,  fin         ; Si sale un número < 0
            ld      e,  a
            ld      h,  0x47        ; Reinicia el contador de scanlines...
            add     a,  h           ; H+E
            ld      h,  a
            jr      inicio2
    fin:    nop

        #endasm
        break;
	}
}

void drawGFX (BYTE gfxnum, BYTE xorig, BYTE yorig)
{

}

void printat (BYTE x, BYTE y, unsigned char *texto)
{
	/* Códigos de escape:
		\n
		\a \e \i \o \u \n
		\A \E \I \O \U \N
		\b
		\i
		\t
	*/
}

void waitForanyKey()
{
#asm
Wait_For_Keys_Pressed:
   XOR A                        ; A = 0
   IN A, (254)
   OR 224
   INC A
   JR Z, Wait_For_Keys_Pressed
#endasm
}


