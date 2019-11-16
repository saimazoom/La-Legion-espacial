
; ===============================================================
; aralbrec - Nov 2013
; ===============================================================
;
; void *fzx_bPartition(void *buf, uint len, uint width)
;
; Finds longest prefix string of buf that has pixel width less than
; or equal to "width".  Newline, \0, and AT indicator cause the
; iteration to stop.
;
; Returned pointer points at one char past the prefix.
; ie (return - buf) is the number of chars in the prefix string.
;
; ===============================================================

XLIB fzx_bPartition_callee
XDEF asm_fzx_bPartition

LIB __fzx_glyph_width, _fzx

DEFC FONT = 0

fzx_bPartition_callee:

   pop af
   pop hl
   pop bc
   pop de
   push af

asm_fzx_bPartition:

   ; enter : de = void *buf
   ;         bc = uint len
   ;         hl = allowed width in pixels
   ;
   ; exit  : hl = buf + prefixlen
   ;         ix = struct fzx_font *
   ;         bc = remaining len in buf
   ;
   ;         carry reset if stopped with room available
   ;         de = remaining width in pixels
   ;
   ;         carry set if width exceeded
   ;         de = - remaining width in pixels
   ;
   ; uses  : af, bc, de, hl, ix

   ld ix,(_fzx + FONT)         ; ix = current font

loop_consume:

   ld a,b                      ; end of buffer?
   or c
   jr z, end_string
   
   ld a,(de)
   
   cp 13                       ; terminate at newline
   jr z, end_string
   
   cp 22                       ; terminate at AT sequence
   jr z, end_string

   push bc
   push hl
   
   call __fzx_glyph_width
   ld c,a
   ld b,0                      ; bc = char width
   
   pop hl
   sbc hl,bc                   ; is there room for the char?
   jr c, end_string
   
   pop bc
   
   dec bc
   inc de
   jp loop_consume

end_string:

   ex de,hl
   ret
