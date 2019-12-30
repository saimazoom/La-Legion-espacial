;
; Title:	ZX Spectrum Standard Output Routines
; Author:	Dean Belfield
; Created:	29/07/2011
; Last Updated:	02/07/2012
;
; Requires:
;
; Modinfo:
;
; 02/07/2012:	Added Pixel_Address_Down and Pixel_Address_Up routines
; 04/07/2012:	Moved Clear_Screen to Screen_Buffer
;

; Print String Data
; First two bytes of string contain X and Y char position, then the string
; Individual strings are terminated with &FE
; End of data is terminated with &FF
; HL: Address of string
;

; En la pila RET ADDRESS(2bytes), BYTE Y, BYTE X
; Otra forma:
;	   __asm
;		pop bc   ; bc = ret address
;		pop hl   ; hl = int b
;		pop de  ; de = int a
;		push bc  ; put the return address back
; Otro ejemplo:
; El puntero de pila crece hacia abajo 
; void scrollArriba (BYTE fila_inicial, BYTE columna_inicial)
;    ld     hl,$0002
;     add    hl,sp        ; skip over return address on stack
;     ld     b,(hl)       ; Columna inicial
;     inc    hl           ; La pila usa 16bit de ancho, Little Endian. Termina Word1
;     inc    hl           ; Comienza Word2
;     ld     c,(hl)       ; Fila inicial
;     ld     ixh,8        ; Contador de Scanlines
;     inc    hl


PUBLIC _print_string
PUBLIC _print_char
PUBLIC _set_attr

; Fonts
; Fonts can be edited easily using the fzx font editor, it can import/export .chr files.
_reynolds:
;BINARY "../res/L01_sala_trampa_sp.scr.rcs.zx7"
;BINARY "./res/Reynolds Bold.chr"
BINARY "./res/Reynolds.chr"

; =====================================================================
; extern void print_string (BYTE x, BYTE y, unsigned char *texto);
; =====================================================================
_print_string:
            POP BC              ; BC = RET ADDRESS
            POP HL              ; HL = STRING ADDRESS
            POP DE              ; DE = E = BYTE Y. Stack width is 16bits. LITTL ENDIAN
            LD  A,E
            POP DE               ; DE = E = BYTE X
            PUSH BC             ; PUT THE RETURN ADDRESS BACK        
            LD  D, A
            ;LD E,(HL)			; E = Fetch the X coordinate
			;LD D,(HL)			; D = Fetch the Y coordinate
			CALL Get_Char_Address		; Calculate the screen address (in DE)
Print_String_0:
            LD A,(HL)			; Fetch the character to print
			INC HL				; Increase HL to the next character
            OR A
            ;CP $FE				; Compare with 0xFE
			;JR Z,Print_String		; If it is equal to 0xFE then loop back to print next string
			RET Z				; If the current character is 0 then return.
			PUSH HL				; Push HL on stack (Print_Char will not preserve HL)
			CALL Print_Char			; Print the character
			POP HL				; Retrieve HL back off the stack
			INC E				; Go to the next screen address
			JR Print_String_0		; Loop back to print next character
			RET

; =====================================================================
;extern void __CALLEE__ print_char (BYTE x, BYTE y, unsigned char texto);
; =====================================================================
 _print_char:
            POP BC              ; BC = RET ADDRESS
            POP HL              ; HL = L = CHARACTER TO BE PRINTED
            POP DE              ; DE = E = BYTE Y. Stack width is 16bits. LITTL ENDIAN
            LD  A,E
            POP DE               ; DE = E = BYTE X
            PUSH BC             ; PUT THE RETURN ADDRESS BACK        
            LD  D, A
            ;LD E,(HL)			; E = Fetch the X coordinate
			;LD D,(HL)			; D = Fetch the Y coordinate
			CALL Get_Char_Address		; Calculate the screen address (in DE)
            LD A,L			; Fetch the character to print
			CALL Print_Char			; Print the character
			RET
            
; Get screen address
; D = Y character position (0-24)
; E = X character position (0-32)
; Returns address in DE
;
Get_Char_Address:	LD A,D
			AND %00000111
			RRA
			RRA
			RRA
			RRA
			OR E
			LD E,A
			LD A,D
			AND %00011000
			OR %01000000
			LD D,A
			RET				; Returns screen address in DE

; Get screen address
; B = Y pixel position
; C = X pixel position
; Returns address in HL and pixel position within character in A
;
Get_Pixel_Address:	LD A,B				; Calculate Y2,Y1,Y0
			AND %00000111			; Mask out unwanted bits
			OR %01000000			; Set base address of screen
			LD H,A				; Store in H
			LD A,B				; Calculate Y7,Y6
			RRA				; Shift to position
			RRA
			RRA
			AND %00011000			; Mask out unwanted bits
			OR H				; OR with Y2,Y1,Y0
			LD H,A				; Store in H
			LD A,B				; Calculate Y5,Y4,Y3
			RLA				; Shift to position
			RLA
			AND %11100000			; Mask out unwanted bits
			LD L,A				; Store in L
			LD A,C				; Calculate X4,X3,X2,X1,X0
			RRA				; Shift into position
			RRA
			RRA
			AND %00011111			; Mask out unwanted bits
			OR L				; OR with Y5,Y4,Y3
			LD L,A				; Store in L
			LD A,C
			AND 7
			RET

; Move HL down one pixel line
;
Pixel_Address_Down:	INC H			; Go down onto the next pixel line
			LD A,H			; Check if we have gone onto next character boundary
			AND 7
			RET NZ			; No, so skip the next bit
			LD A,L			; Go onto the next character line
			ADD A,32
			LD L,A
			RET C			; Check if we have gone onto next third of screen
			LD A,H			; Yes, so go onto next third
			SUB 8
			LD H,A
			RET

; Move HL up one pixel line
;
Pixel_Address_Up:	DEC H			; Go up onto the next pixel line
			LD A,H			; Check if we have gone onto the next character boundary
			AND 7
			CP 7
			RET NZ
			LD A,L
			SUB 32
			LD L,A
			RET C
			LD A,H
			ADD A,8
			LD H,A
			RET

; Print a single character out
; A:  Character to print
; DE: Screen address to print character at
;
Print_Char:		
            ;LD HL,$3C00			; Address of character set table in ROM
			LD HL, _reynolds-32*8
            LD B,0				; Set BC to A
			LD C,A
			AND $FF				; Clear the carry bit
			RL C				; Multiply BC by 8 (shift left 3 times)
			RL B
			RL C
			RL B
			RL C
			RL B
			ADD HL,BC			; Get the character address in HL
		    LD C,8				; Loop counter
			PUSH DE
Print_Char_1:		LD A,(HL)			; Get the byte from the ROM into A
            ;LD B,A
			;RR B
            ;OR B
            LD (DE),A			; Stick A onto the screen
			
            ;RRC A
            INC D				; Goto next line on screen
			INC HL				; Goto next byte of character
			DEC C				; Decrease the loop counter
			JR NZ,Print_Char_1		; Loop around whilst it is Not Zero (NZ)
			POP DE
			RET				; Return from the subroutine

; =====================================================================
;extern void __CALLEE__ set_attr (BYTE x, BYTE Y, BYTE attr);
; http://www.breakintoprogram.co.uk/computers/zx-spectrum/screen-memory-layout
; BYTE *attr = (BYTE*)(0x5800+x+(y*32));  // Dirección base
; =====================================================================

_set_attr:
            POP BC              ; BC = RET ADDRESS
            POP HL              ; HL = L = ATTRIBUTE TO BE SET 
            POP DE              ; DE = E = BYTE Y. Stack width is 16bits. LITTL ENDIAN
            LD  A,E				; A = Y
        	POP DE               ; DE = E = BYTE X
            PUSH BC             ; PUT THE RETURN ADDRESS BACK in the STACK       
			LD B,L				; Store in B the attribute value
								; Calculates the attribute address 
		    rrca                ; multiply Y by 32.
       		rrca
       		rrca
            LD 	L,A				; Stores A in L 
			and 3               ; mask bits for high byte.
       		add a,88            ; 88*256=22528, start of attributes.
       		ld h,a              ; high byte done.
       		ld a,l              ; get x*32 again.
       		and 224             ; mask low byte.
       		ld l,a              ; put in l.
       		ld a,e              ; get x displacement.
       		add a,l             ; add to low byte.
       		ld l,a              ; hl=address of attributes.
       		ld (hl),B           ; Write attribute in (HL).
			RET 