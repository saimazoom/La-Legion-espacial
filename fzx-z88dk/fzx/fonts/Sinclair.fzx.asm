;; FONT DEFINITION EXAMPLE
; (pasmo assembler; z80asm might require some changes)


; Sinclair by Steve Vickers
; Copyright (c) 1982 Amstrad, plc.

	org		0

; -----------------------------------------------------------------------------
; header

height:
	defb	9					; vertical gap between baselines in pixels

tracking:
	defb	2					; horizontal gap between characters in pixels

lastchar:
	defb	127					; last defined character (32-255)

; -----------------------------------------------------------------------------
; character table:
;
; defw address -$ + kern
; defb 16 * shift + width - 1

table:
	defw	space -$
	defb	16*0+6-1
	defw	exclamation_mark -$
	defb	16*1+1-1
	defw	quotation_mark -$
	defb	16*1+4-1
	defw	number_sign -$
	defb	16*1+6-1
	defw	dollar_sign -$
	defb	16*1+5-1
	defw	percent_sign -$
	defb	16*1+6-1
	defw	ampersand -$
	defb	16*1+6-1
	defw	apostrophe -$
	defb	16*0+2-1
	defw	left_parenthesis -$
	defb	16*0+2-1
	defw	right_parenthesis -$
	defb	16*0+2-1
	defw	asterisk -$
	defb	16*2+5-1
	defw	plus_sign -$
	defb	16*2+5-1
	defw	comma -$
	defb	16*6+2-1
	defw	hyphen_minus -$
	defb	16*4+5-1
	defw	full_stop -$
	defb	16*5+2-1
	defw	solidus -$
	defb	16*2+5-1
	defw	digit_zero -$
	defb	16*1+6-1
	defw	digit_one -$
	defb	16*1+5-1
	defw	digit_two -$
	defb	16*1+6-1
	defw	digit_three -$
	defb	16*1+6-1
	defw	digit_four -$
	defb	16*1+6-1
	defw	digit_five -$
	defb	16*1+6-1
	defw	digit_six -$
	defb	16*1+6-1
	defw	digit_seven -$
	defb	16*1+6-1
	defw	digit_eight -$
	defb	16*1+6-1
	defw	digit_nine -$
	defb	16*1+6-1
	defw	colon -$
	defb	16*3+1-1
	defw	semicolon -$ + 16384*1
	defb	16*3+2-1
	defw	less_than_sign -$
	defb	16*2+3-1
	defw	equals_sign -$
	defb	16*3+5-1
	defw	greater_than_sign -$
	defb	16*2+3-1
	defw	question_mark -$
	defb	16*1+6-1
	defw	commercial_at -$
	defb	16*1+6-1
	defw	latin_capital_letter_a -$
	defb	16*1+6-1
	defw	latin_capital_letter_b -$
	defb	16*1+6-1
	defw	latin_capital_letter_c -$
	defb	16*1+6-1
	defw	latin_capital_letter_d -$
	defb	16*1+6-1
	defw	latin_capital_letter_e -$
	defb	16*1+6-1
	defw	latin_capital_letter_f -$
	defb	16*1+6-1
	defw	latin_capital_letter_g -$
	defb	16*1+6-1
	defw	latin_capital_letter_h -$
	defb	16*1+6-1
	defw	latin_capital_letter_i -$
	defb	16*1+5-1
	defw	latin_capital_letter_j -$
	defb	16*1+6-1
	defw	latin_capital_letter_k -$
	defb	16*1+6-1
	defw	latin_capital_letter_l -$
	defb	16*1+6-1
	defw	latin_capital_letter_m -$
	defb	16*1+6-1
	defw	latin_capital_letter_n -$
	defb	16*1+6-1
	defw	latin_capital_letter_o -$
	defb	16*1+6-1
	defw	latin_capital_letter_p -$
	defb	16*1+6-1
	defw	latin_capital_letter_q -$
	defb	16*1+6-1
	defw	latin_capital_letter_r -$
	defb	16*1+6-1
	defw	latin_capital_letter_s -$
	defb	16*1+6-1
	defw	latin_capital_letter_t -$
	defb	16*1+7-1
	defw	latin_capital_letter_u -$
	defb	16*1+6-1
	defw	latin_capital_letter_v -$
	defb	16*1+6-1
	defw	latin_capital_letter_w -$
	defb	16*1+6-1
	defw	latin_capital_letter_x -$
	defb	16*1+6-1
	defw	latin_capital_letter_y -$
	defb	16*1+7-1
	defw	latin_capital_letter_z -$
	defb	16*1+6-1
	defw	left_square_bracket -$
	defb	16*0+3-1
	defw	reverse_solidus -$
	defb	16*2+5-1
	defw	right_square_bracket -$
	defb	16*0+3-1
	defw	circumflex_accent -$
	defb	16*1+5-1
	defw	low_line -$
	defb	16*7+8-1
	defw	grave_accent -$
	defb	16*1+6-1
	defw	latin_small_letter_a -$
	defb	16*2+5-1
	defw	latin_small_letter_b -$
	defb	16*0+5-1
	defw	latin_small_letter_c -$
	defb	16*2+4-1
	defw	latin_small_letter_d -$
	defb	16*0+5-1
	defw	latin_small_letter_e -$
	defb	16*2+5-1
	defw	latin_small_letter_f -$
	defb	16*0+3-1
	defw	latin_small_letter_g -$
	defb	16*2+5-1
	defw	latin_small_letter_h -$
	defb	16*0+5-1
	defw	latin_small_letter_i -$
	defb	16*0+3-1
	defw	latin_small_letter_j -$ + 16384*1
	defb	16*0+4-1
	defw	latin_small_letter_k -$
	defb	16*0+4-1
	defw	latin_small_letter_l -$
	defb	16*0+3-1
	defw	latin_small_letter_m -$
	defb	16*2+9-1
	defw	latin_small_letter_n -$
	defb	16*2+5-1
	defw	latin_small_letter_o -$
	defb	16*2+5-1
	defw	latin_small_letter_p -$
	defb	16*2+5-1
	defw	latin_small_letter_q -$
	defb	16*2+6-1
	defw	latin_small_letter_r -$
	defb	16*2+4-1
	defw	latin_small_letter_s -$
	defb	16*2+5-1
	defw	latin_small_letter_t -$
	defb	16*0+4-1
	defw	latin_small_letter_u -$
	defb	16*2+5-1
	defw	latin_small_letter_v -$
	defb	16*2+5-1
	defw	latin_small_letter_w -$
	defb	16*2+7-1
	defw	latin_small_letter_x -$
	defb	16*2+5-1
	defw	latin_small_letter_y -$
	defb	16*2+5-1
	defw	latin_small_letter_z -$
	defb	16*2+5-1
	defw	left_curly_bracket -$
	defb	16*0+5-1
	defw	vertical_line -$
	defb	16*0+1-1
	defw	right_curly_bracket -$
	defb	16*0+5-1
	defw	tilde -$
	defb	16*0+4-1
	defw	delete -$
	defb	16*0+8-1
	defw	terminus -$

; -----------------------------------------------------------------------------
; definitions

space:

exclamation_mark:
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%00000000
	defb	%10000000

quotation_mark:
	defb	%10010000
	defb	%10010000

number_sign:
	defb	%01001000
	defb	%11111100
	defb	%01001000
	defb	%01001000
	defb	%11111100
	defb	%01001000

dollar_sign:
	defb	%00100000
	defb	%11111000
	defb	%10100000
	defb	%11111000
	defb	%00101000
	defb	%11111000
	defb	%00100000

percent_sign:
	defb	%11000100
	defb	%11001000
	defb	%00010000
	defb	%00100000
	defb	%01001100
	defb	%10001100

ampersand:
	defb	%00100000
	defb	%01010000
	defb	%00100000
	defb	%01010100
	defb	%10001000
	defb	%01110100

apostrophe:
	defb	%01000000
	defb	%10000000

left_parenthesis:
	defb	%01000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%01000000

right_parenthesis:
	defb	%10000000
	defb	%01000000
	defb	%01000000
	defb	%01000000
	defb	%01000000
	defb	%01000000
	defb	%10000000

asterisk:
	defb	%01010000
	defb	%00100000
	defb	%11111000
	defb	%00100000
	defb	%01010000

plus_sign:
	defb	%00100000
	defb	%00100000
	defb	%11111000
	defb	%00100000
	defb	%00100000

comma:
	defb	%01000000
	defb	%01000000
	defb	%10000000

hyphen_minus:
	defb	%11111000

full_stop:
	defb	%11000000
	defb	%11000000

solidus:
	defb	%00001000
	defb	%00010000
	defb	%00100000
	defb	%01000000
	defb	%10000000

digit_zero:
	defb	%01111000
	defb	%10001100
	defb	%10010100
	defb	%10100100
	defb	%11000100
	defb	%01111000

digit_one:
	defb	%01100000
	defb	%10100000
	defb	%00100000
	defb	%00100000
	defb	%00100000
	defb	%11111000

digit_two:
	defb	%01111000
	defb	%10000100
	defb	%00000100
	defb	%01111000
	defb	%10000000
	defb	%11111100

digit_three:
	defb	%01111000
	defb	%10000100
	defb	%00011000
	defb	%00000100
	defb	%10000100
	defb	%01111000

digit_four:
	defb	%00010000
	defb	%00110000
	defb	%01010000
	defb	%10010000
	defb	%11111100
	defb	%00010000

digit_five:
	defb	%11111100
	defb	%10000000
	defb	%11111000
	defb	%00000100
	defb	%10000100
	defb	%01111000

digit_six:
	defb	%01111000
	defb	%10000000
	defb	%11111000
	defb	%10000100
	defb	%10000100
	defb	%01111000

digit_seven:
	defb	%11111100
	defb	%00000100
	defb	%00001000
	defb	%00010000
	defb	%00100000
	defb	%00100000

digit_eight:
	defb	%01111000
	defb	%10000100
	defb	%01111000
	defb	%10000100
	defb	%10000100
	defb	%01111000

digit_nine:
	defb	%01111000
	defb	%10000100
	defb	%10000100
	defb	%01111100
	defb	%00000100
	defb	%01111000

colon:
	defb	%10000000
	defb	%00000000
	defb	%00000000
	defb	%10000000

semicolon:
	defb	%01000000
	defb	%00000000
	defb	%00000000
	defb	%01000000
	defb	%01000000
	defb	%10000000

less_than_sign:
	defb	%00100000
	defb	%01000000
	defb	%10000000
	defb	%01000000
	defb	%00100000

equals_sign:
	defb	%11111000
	defb	%00000000
	defb	%11111000

greater_than_sign:
	defb	%10000000
	defb	%01000000
	defb	%00100000
	defb	%01000000
	defb	%10000000

question_mark:
	defb	%01111000
	defb	%10000100
	defb	%00001000
	defb	%00010000
	defb	%00000000
	defb	%00010000

commercial_at:
	defb	%01111000
	defb	%10010100
	defb	%10101100
	defb	%10111100
	defb	%10000000
	defb	%01111000

latin_capital_letter_a:
	defb	%01111000
	defb	%10000100
	defb	%10000100
	defb	%11111100
	defb	%10000100
	defb	%10000100

latin_capital_letter_b:
	defb	%11111000
	defb	%10000100
	defb	%11111000
	defb	%10000100
	defb	%10000100
	defb	%11111000

latin_capital_letter_c:
	defb	%01111000
	defb	%10000100
	defb	%10000000
	defb	%10000000
	defb	%10000100
	defb	%01111000

latin_capital_letter_d:
	defb	%11110000
	defb	%10001000
	defb	%10000100
	defb	%10000100
	defb	%10001000
	defb	%11110000

latin_capital_letter_e:
	defb	%11111100
	defb	%10000000
	defb	%11111000
	defb	%10000000
	defb	%10000000
	defb	%11111100

latin_capital_letter_f:
	defb	%11111100
	defb	%10000000
	defb	%11111000
	defb	%10000000
	defb	%10000000
	defb	%10000000

latin_capital_letter_g:
	defb	%01111000
	defb	%10000100
	defb	%10000000
	defb	%10011100
	defb	%10000100
	defb	%01111000

latin_capital_letter_h:
	defb	%10000100
	defb	%10000100
	defb	%11111100
	defb	%10000100
	defb	%10000100
	defb	%10000100

latin_capital_letter_i:
	defb	%11111000
	defb	%00100000
	defb	%00100000
	defb	%00100000
	defb	%00100000
	defb	%11111000

latin_capital_letter_j:
	defb	%00000100
	defb	%00000100
	defb	%00000100
	defb	%10000100
	defb	%10000100
	defb	%01111000

latin_capital_letter_k:
	defb	%10001000
	defb	%10010000
	defb	%11100000
	defb	%10010000
	defb	%10001000
	defb	%10000100

latin_capital_letter_l:
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%11111100

latin_capital_letter_m:
	defb	%10000100
	defb	%11001100
	defb	%10110100
	defb	%10000100
	defb	%10000100
	defb	%10000100

latin_capital_letter_n:
	defb	%10000100
	defb	%11000100
	defb	%10100100
	defb	%10010100
	defb	%10001100
	defb	%10000100

latin_capital_letter_o:
	defb	%01111000
	defb	%10000100
	defb	%10000100
	defb	%10000100
	defb	%10000100
	defb	%01111000

latin_capital_letter_p:
	defb	%11111000
	defb	%10000100
	defb	%10000100
	defb	%11111000
	defb	%10000000
	defb	%10000000

latin_capital_letter_q:
	defb	%01111000
	defb	%10000100
	defb	%10000100
	defb	%10100100
	defb	%10010100
	defb	%01111000

latin_capital_letter_r:
	defb	%11111000
	defb	%10000100
	defb	%10000100
	defb	%11111000
	defb	%10001000
	defb	%10000100

latin_capital_letter_s:
	defb	%01111000
	defb	%10000000
	defb	%01111000
	defb	%00000100
	defb	%10000100
	defb	%01111000

latin_capital_letter_t:
	defb	%11111110
	defb	%00010000
	defb	%00010000
	defb	%00010000
	defb	%00010000
	defb	%00010000

latin_capital_letter_u:
	defb	%10000100
	defb	%10000100
	defb	%10000100
	defb	%10000100
	defb	%10000100
	defb	%01111000

latin_capital_letter_v:
	defb	%10000100
	defb	%10000100
	defb	%10000100
	defb	%10000100
	defb	%01001000
	defb	%00110000

latin_capital_letter_w:
	defb	%10000100
	defb	%10000100
	defb	%10000100
	defb	%10000100
	defb	%10110100
	defb	%01001000

latin_capital_letter_x:
	defb	%10000100
	defb	%01001000
	defb	%00110000
	defb	%00110000
	defb	%01001000
	defb	%10000100

latin_capital_letter_y:
	defb	%10000010
	defb	%01000100
	defb	%00101000
	defb	%00010000
	defb	%00010000
	defb	%00010000

latin_capital_letter_z:
	defb	%11111100
	defb	%00001000
	defb	%00010000
	defb	%00100000
	defb	%01000000
	defb	%11111100

left_square_bracket:
	defb	%11100000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%11100000

reverse_solidus:
	defb	%10000000
	defb	%01000000
	defb	%00100000
	defb	%00010000
	defb	%00001000

right_square_bracket:
	defb	%11100000
	defb	%00100000
	defb	%00100000
	defb	%00100000
	defb	%00100000
	defb	%00100000
	defb	%11100000

circumflex_accent:
	defb	%00100000
	defb	%01110000
	defb	%10101000
	defb	%00100000
	defb	%00100000
	defb	%00100000

low_line:
	defb	%11111111

grave_accent:
	defb	%00111000
	defb	%01000100
	defb	%11110000
	defb	%01000000
	defb	%01000000
	defb	%11111100

latin_small_letter_a:
	defb	%01110000
	defb	%00001000
	defb	%01111000
	defb	%10001000
	defb	%01111000

latin_small_letter_b:
	defb	%10000000
	defb	%10000000
	defb	%11110000
	defb	%10001000
	defb	%10001000
	defb	%10001000
	defb	%11110000

latin_small_letter_c:
	defb	%01110000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%01110000

latin_small_letter_d:
	defb	%00001000
	defb	%00001000
	defb	%01111000
	defb	%10001000
	defb	%10001000
	defb	%10001000
	defb	%01111000

latin_small_letter_e:
	defb	%01110000
	defb	%10001000
	defb	%11110000
	defb	%10000000
	defb	%01111000

latin_small_letter_f:
	defb	%01100000
	defb	%10000000
	defb	%11000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000

latin_small_letter_g:
	defb	%01111000
	defb	%10001000
	defb	%10001000
	defb	%10001000
	defb	%01111000
	defb	%00001000
	defb	%01110000

latin_small_letter_h:
	defb	%10000000
	defb	%10000000
	defb	%11110000
	defb	%10001000
	defb	%10001000
	defb	%10001000
	defb	%10001000

latin_small_letter_i:
	defb	%01000000
	defb	%00000000
	defb	%11000000
	defb	%01000000
	defb	%01000000
	defb	%01000000
	defb	%11100000

latin_small_letter_j:
	defb	%00010000
	defb	%00000000
	defb	%00010000
	defb	%00010000
	defb	%00010000
	defb	%00010000
	defb	%00010000
	defb	%10010000
	defb	%01100000

latin_small_letter_k:
	defb	%10000000
	defb	%10000000
	defb	%10100000
	defb	%11000000
	defb	%11000000
	defb	%10100000
	defb	%10010000

latin_small_letter_l:
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%01100000

latin_small_letter_m:
	defb	%11110111, %00000000
	defb	%10001000, %10000000
	defb	%10001000, %10000000
	defb	%10001000, %10000000
	defb	%10001000, %10000000

latin_small_letter_n:
	defb	%11110000
	defb	%10001000
	defb	%10001000
	defb	%10001000
	defb	%10001000

latin_small_letter_o:
	defb	%01110000
	defb	%10001000
	defb	%10001000
	defb	%10001000
	defb	%01110000

latin_small_letter_p:
	defb	%11110000
	defb	%10001000
	defb	%10001000
	defb	%10001000
	defb	%11110000
	defb	%10000000
	defb	%10000000

latin_small_letter_q:
	defb	%01111000
	defb	%10001000
	defb	%10001000
	defb	%10001000
	defb	%01111000
	defb	%00001000
	defb	%00001100

latin_small_letter_r:
	defb	%01110000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000

latin_small_letter_s:
	defb	%01110000
	defb	%10000000
	defb	%01110000
	defb	%00001000
	defb	%11110000

latin_small_letter_t:
	defb	%01000000
	defb	%01000000
	defb	%11100000
	defb	%01000000
	defb	%01000000
	defb	%01000000
	defb	%00110000

latin_small_letter_u:
	defb	%10001000
	defb	%10001000
	defb	%10001000
	defb	%10001000
	defb	%01110000

latin_small_letter_v:
	defb	%10001000
	defb	%10001000
	defb	%01010000
	defb	%01010000
	defb	%00100000

latin_small_letter_w:
	defb	%10010010
	defb	%10010010
	defb	%10010010
	defb	%10010010
	defb	%01101100

latin_small_letter_x:
	defb	%10001000
	defb	%01010000
	defb	%00100000
	defb	%01010000
	defb	%10001000

latin_small_letter_y:
	defb	%10001000
	defb	%10001000
	defb	%10001000
	defb	%10001000
	defb	%01111000
	defb	%00001000
	defb	%01110000

latin_small_letter_z:
	defb	%11111000
	defb	%00010000
	defb	%00100000
	defb	%01000000
	defb	%11111000

left_curly_bracket:
	defb	%00111000
	defb	%00100000
	defb	%00100000
	defb	%11000000
	defb	%00100000
	defb	%00100000
	defb	%00111000

vertical_line:
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000
	defb	%10000000

right_curly_bracket:
	defb	%11100000
	defb	%00100000
	defb	%00100000
	defb	%00011000
	defb	%00100000
	defb	%00100000
	defb	%11100000

tilde:
	defb	%01010000
	defb	%10100000

delete:
	defb	%00111100
	defb	%01000010
	defb	%10011001
	defb	%10100001
	defb	%10100001
	defb	%10011001
	defb	%01000010
	defb	%00111100

terminus:
