
#include ".\libgfx\libgfx.h"
#include <string.h>


void setRAMPage (BYTE banco)
{
    #asm
;-----------------------------------------------------------------------
; SetRAMPage: Establece un banco de memoria sobre $c000
; Entrada: B = banco (0-7) a paginar entre $c000-$ffff
;-----------------------------------------------------------------------
; Extra�do del Manual de Usuario de Spectrum, P�gina 221
;
     ld     hl, $0002
     add    hl, sp
     ld     a, (hl) ; A= Banco
     ld     b, a
     ld     A, ($5B5C)
     and    $F8
     or     B
     ld     BC, $7FFD
     ld     ($5B5C), A
     out    (C), A
;     ret
    #endasm
}

void setRAMBack()
{

#asm
    ld      A, ($5B5C)
    and     $F8
    ld      BC, $7FFD
    di
    ld      ($5B5C), A
    out     (C), A
    ei
    ;ld      a,$0F0
    ;ld i,a
    ;ei
#endasm

}



void drawVline (BYTE x0, BYTE y0, BYTE len)
{

}

void drawHline (BYTE x0, BYTE y0, BYTE len)
{

}

void drawline (BYTE x0, BYTE y0, BYTE len)
{

}

   // Formato de memoria de v�deo: 010xxYYY ZZZCCCCC
   // xx: Tercio
   // YYY: Scan Line 0-7
   // ZZZ: Caracter 0-7 Fila
   // CCCC: Columna 0-31
/*
 Tercio 0
 Tercio 1 18432 0x4800
 Tercio 2

*/

void scrollArriba (BYTE fila_inicial, BYTE columna_inicial)
{
    // ScrollVertical de 1 fila partiendo de una fila inicial
    // Fila: 0 a 24 -> 0000 0000 a 0000 1100
    //                 0000 0000 a 0000 0111
    //                 0000 1000 a 0000 1111
    //                 0001 0000 a 0001 0111
#asm
     ld     hl,$0002
     add    hl,sp        ; skip over return address on stack
     ld     b,(hl)       ; Columna inicial
     inc    hl           ; La pila usa 16bit de ancho, Little Endian. Termina Word1
     inc    hl           ; Comienza Word2
     ld     c,(hl)       ; Fila inicial
     ld     ixh,8        ; Contador de Scanlines
     inc    hl
SA1start:
     push   bc           ; B=Columa inicial, C=Fila actual
     ld     hl, 16384    ; Origen de pantalla Y=0, HL = 0x4000
     ld     a,c          ; A = fila inicial
     and    $18          ; Estos dos bit indican el tercio
     or     h
     ld     h,a          ; H Apunta al tercio correcto, Scanline =0
     ld     a,c
     and    $07          ; Fila 0-7
     rlca
     rlca
     rlca
     rlca
     rlca
     or     b             ;Bits 0-4 Columna inicial
     ld     l,a          ; Ahora HL apunta a la direcci�n de la fila de destino

     ld     de, 16384    ; DE debe apuntar a la fila de origen (1 fila por debajo de HL)
     ld     a,c
     inc    a
     and    $18          ; Estos dos bit indican el tercio
     or     d
     ld     d,a          ; H Apunta al tercio correcto, Scanline =0
     ld     a,c
     inc    a            ; Fila A = Fila HL+1
     and    $07          ; Fila 0-7
     rlca
     rlca
     rlca
     rlca
     rlca
     or     b             ; Bits 0-5 Columna inicial
     ld     e,a          ; Ahora DE apunta a la direcci�n de la fila de origen

     push   de
     push   hl

     ld     a,32
     sub    b
     ld     b,a
     ld     ixl,b        ; N�mero de columnas  acopiar por scanline
SA1loops:                ; Bucle por scanline...
     ld     b,ixl

SA1loop:                ; Bucle por columna
     ld     a,(de)
     ld     (hl),a      ; Escribe el contenido de la direcci�n DE en la direcci�n apuntada por HL
     ld     a,c
     cp     23           ; Si estamos en la �ltima linea de origen rellena con 0
     jp     nz, notfillzero
     ld     (hl),0
notfillzero:
     inc     de
     inc     hl
     djnz    SA1loop
                         ; Termina de copiar todas las columnas
     pop    hl
     pop    de
     ld     b,ixh
     djnz   nextscan
     jp     nextrow
nextscan:
     ld     ixh,b
     inc    h
     inc    d           ; Incrementa DE=DE+256, siguiente scanline
     push   de
     push   hl
     jp     SA1loops
nextrow:
     pop     bc           ; B=Columa inicial, C=Fila
     ld      ixh,8
     ld      a,c
     inc     a           ;
     ld      c,a         ; Almacena Siguiente fila de origen
     cp      24          ; La �ltima fila de origen es la 23
     jp      nz,SA1start
                         ; Limpia la �ltima fila
#endasm
}

void drawRectangle (BYTE xorig, BYTE yorig, BYTE width, BYTE height)
{

}
   // Formato de memoria de v�deo: 010xxYYY ZZZCCCCC
   // xx: Tercio
   // YYY: Scan Line 0-7
   // ZZZ: Caracter 0-7 Fila
   // CCCC: Columna 0-31

void clsScreen (BYTE effect)
{
	switch (effect)
	{
		case 0: // Persiana arriba-abajo
        #asm
			ld  	hl, $4000      ; Inicio de la memoria de video
			ld 		b, 	32          ; 32bytes por l�nea
			ld      c,  $00        ; Contador de fila de caracteres
			ld      d,  4           ; 4 l�neas por caracter (alternas)
			ld      e,  0           ; Contador de tercios..
inicio:     ld 		(hl), $FF		; Pone el Caracter actual a todo 1
            inc 	l               ; Avanza 1 caracter a la derecha...
            dec		b			    ; Decrementa el contador
            jr		nz, inicio      ; 32 veces...
            inc		h
            inc     h               ; Salta 2 scanlines
            ld      l,  0           ; Vuelve el contador de columnas a 0
            ld      a,  l
            add     a,  c           ; A�ade la fila
            ld      l,  a
            ld 		b, 	32          ; 32 caracteres para la siguiente fila...
            dec     d               ; Contador de l�neas del caracter...
            halt
            jr      nz, inicio      ; Se termina la fila de caracteres actual...
            ld      a,  e
            ld      h,  $40
            add     a,  h
            ld      h,  a
            ld      d,  4
            ld      a,  $20        ; Para sumar 1 al contador de filas...
            add     a,  c           ; Suma 1 al contador de filas...
            ld      c,  a
            ld      l,  a           ; La parte baja de HL contiene ZZZ00000
            jr      nc, inicio      ; Fin de Tercio

            ld      c,  $00
            ld      l,  0
            ld      b,  32

            ld      a,  e
            add     a,  8         ; Incrementa el contador de tercios
            ld      e,  a
            ld      h,  $40        ; Reinicia el contador de scanlines...
            add     a,  h           ; H+E
            ld      h,  a
            cp      $58
            jr      nz, inicio
        #endasm

		break;
	case 1: // Persiana abajo-arriba
        #asm
			ld  	hl, 22496       ; Inicio de la pen�ltima l�nea de la memoria de video
			ld 		b, 	32          ; 32bytes por l�nea
			ld      c,  $E0        ; Contador de fila de caracteres
			ld      d,  4           ; 4 l�neas por caracter (alternas)
			ld      e,  $10        ; Contador de tercios..., Tercer Tercio
    inicio2:
            ld 		(hl), $FF		; Pone el Caracter actual a todo 1
			inc 	l               ; Avanza 1 caracter a la derecha...
			dec		b			    ; Decrementa el contador
			jr		nz, inicio2     ; 32 veces...
			dec		h
			dec     h               ; Salta 2 scanlines
			ld      l,  0           ; Vuelve el contador de columnas a 0
			ld      a,  l
			add     a,  c           ; A�ade la fila de caracteres
			ld      l,  a
			ld 		b, 	32          ; 32 caracteres para la siguiente fila...
			dec     d               ; Contador de l�neas del caracter...
			halt
			jr      nz, inicio2      ; Se termina la fila de caracteres actual...

            ld      a,  e
            ld      h,  $47        ; Pen�ltimo Scanline...
            add     a,  h
            ld      h,  a           ; H = 0x46 + E
            ld      d,  4

            ld      a,  c            ; Para sumar 1 al contador de filas...
            sub     a,  $20         ; Resta 1 al contador de filas...
            ld      c,  a
            ld      l,  a           ; La parte baja de HL contiene ZZZ00000
            jr      nc, inicio2      ; Fin de Tercio

            ld      c,  $E0
            ld      l,  c
            ld      b,  32

            ld      a,  e
            sub     a,  8         ; Decrementa el contador de tercios
            jr      c,  fin         ; Si sale un n�mero < 0
            ld      e,  a
            ld      h,  $47        ; Reinicia el contador de scanlines...
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
// Cambia de banco
// Vuelca la pantalla
// Vuelve al banco 0
}


void waitForAnyKey()
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

void waitForNoKey()
{
#asm
    Wait_For_Keys_NotPressed:
       XOR A                        ; A = 0
       IN A, (254)
       OR 224
       INC A
       JR NZ, Wait_For_Keys_NotPressed
#endasm
}

unsigned char getKey()
{
//    http://www.animatez.co.uk/computers/zx-spectrum/keyboard/
//    https://chuntey.wordpress.com/2012/12/19/how-to-write-zx-spectrum-games-chapter-2/
//    Teclas especiales: Borrar SHIFT+0, se devuelve como 0
//                       ALTGR + O como ;

#asm
Read_Keyboard:      LD HL,Keyboard_Map      ; Point HL at the keyboard list
                    LD D,8                  ; This is the number of ports (rows) to check
                    LD C,0xFE                ; C is always FEh for reading keyboard ports
                    LD IXL,0
Read_Keyboard_0:    LD B,(HL)               ; Get the keyboard port address from table
                    INC HL                  ; Increment to list of keys
                    IN A,(C)                ; Read the row of keys in
                    AND 0x1F                 ; We are only interested in the first five bits
                    LD E,5                  ; This is the number of keys in the row
Read_Keyboard_1:    SRL A                   ; Shift A right; bit 0 sets carry bit
                    JR  C,nokey             ; If the bit is 1, we have not found our key
                    LD  B,A
                    LD  A,(HL)
                    CP '#'                   ; No retorna con la tecla SHIFT
                    JR  NZ,  Read_Keyboard_2 ; Salimos con el c�digo de la tecla
                    LD  IXL, 4              ; C�digo SHIFT
                    LD  A,B
nokey:              INC HL                  ; Go to next table address
                    DEC E                   ; Decrement key loop counter
                    JR  NZ,Read_Keyboard_1   ; Loop around until this row finished
                    DEC D                   ; Decrement row loop counter
                    JR  NZ,Read_Keyboard_0   ; Loop around until we are done
                    AND A                   ; Clear A (no key found)
                    JR  Z, Read_Keyboard
Read_Keyboard_2:
                    LD  A,(HL)               ; We have found a key at this point; fetch the character code!
                    CP '0'                   ; Comprueba si est� borrando...
                    JR  NZ, Return_Keyboard
                    LD  A, IXL
                    CP  A, 4                 ; C�digo SHIFT
                    JR  Z, Return_Keyboard
                    LD  A, 4
Return_Keyboard:    LD  H,0
                    LD  L,A
                    RET

Keyboard_Map:       DEFB 0xFE,'#','z','x','c','v'
                    DEFB 0xFD,'a','s','d','f','g'
                    DEFB 0xFB,'q','w','e','r','t'
                    DEFB 0xF7,'1','2','3','4','5'
                    DEFB 0xEF,'0','9','8','7','6'
                    DEFB 0xDF,'p','o','i','u','y'
                    DEFB 0xBF,13,'l','k','j','h'
                    DEFB 0x7F,' ',';','m','n','b'
#endasm
}


void clearchar (BYTE x, BYTE y, BYTE color)
{
   // http://www.animatez.co.uk/computers/zx-spectrum/screen-memory-layout/
   // Input: x 0 to 31 0000 0000 to 0001 1111
   //        y 0 to 23 0000 0000 to 0001 0111
   // Formato de memoria de v�deo: 010xxYYY ZZZCCCCC
   // xx: Tercio
   // YYY: Scan Line 0-7
   // ZZZ: Fila 0-7 del tercio
   // CCCC: Columna 0-31

   // Tercio 1 0-7 -> 0x00 a 0x07 -> 0100 0000 a 0000 0111
   // Tercio 2 8-15-> 0x08 a 0x0F -> 0100 1000 a 0000 1111
   // Tercio 3 16-23->0x10 a 0x17 -> 0101 0000 a 0001 1111

   // Pone a 0 los bits del caracter
   BYTE i;
   BYTE *video = (BYTE*)(0x4000|( (y&0x18)<<8) | ((y&0x07)<<5)| x); // Direcci�n base
   BYTE *attr = (BYTE*)(0x5800+x+(y*32));  // Direcci�n base

   for (i=0;i<8;i++)
   {
        *video = 0x00;
        video+=256;
   }
   // Setea el atributo
   *attr = color;
}

void clear_screen (BYTE color)
{
// Pasar esto a asm...
 memset(16384, 0, 6144);    // P�xeles...
 memset(22528, color, 768); // Atributos
 #asm
 ;; Set border colour to black
	ld a,0x00
	out ($fe),a
 #endasm
}


void putpixel (BYTE x, BYTE y, BYTE value)
{
    // http://www.animatez.co.uk/computers/zx-spectrum/screen-memory-layout/
	// http://www.z88dk.org/forum/viewtopic.php?id=9177
	// En la pila RET ADDRESS(2bytes), BYTE Y, BYTE X
	/* Otra forma:
	   __asm
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

}
