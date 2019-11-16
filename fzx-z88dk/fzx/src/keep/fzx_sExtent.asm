
; ===============================================================
; aralbrec - Nov 2013
; ===============================================================
;
; uint fzx_sExtent(char *s)
;
; Returns the width of the string in pixels.  Characters left
; undefined by the font are treated as '?'.  Unprinted chars,
; which include '\n' and three-byte AT sequences, are considered
; zero width.
;
; ===============================================================

XLIB fzx_sExtent
XDEF asm_fzx_sExtent

LIB __fzx_width_sm, _fzx, error_zc

DEFC FONT = 0

fzx_sExtent:
asm_fzx_sExtent:

   ; enter : hl = char *s
   ; 
   ; exit  : hl = width of string in pixels
   ;         de = address of terminating \0 in s
   ;         ix = struct fzx_font *
   ;
   ; uses  : af, bc, de, hl, ix

   ex de,hl                    ; de = char *s
   ld ix,(_fzx + FONT)         ; ix = current font; struct fzx_font *

   ; the first character's kern does not count in width

   ld b,1                      ; b = num chars to skip in string + 1
      
loop_first:

   ld a,(de)                   ; end of string reached?
   or a
   jp z, error_zc              ; return with hl = width = 0
   
   call __fzx_width_sm         ; get width of glyph
   jr nc, first_char

   inc de
   jp loop_first

first_char:

   ; add back kern to first char's width
   
   add a,b
   ld l,a
   ld h,0                      ; hl = current width of string
   
remaining_string:

   ld b,1                      ; b = num chars to skip in string + 1
   push hl

loop_rest:

   inc de
   ld a,(de)                   ; end of string reached?
   or a
   jr z, end_string

   call __fzx_width_sm         ; get width of glyph
   jr c, loop_rest             ; ignore unprintable char
   
   pop hl                      ; hl = current width of string
   
   add a,l                     ; add glyph width
   ld l,a
   jp nc, remaining_string
   
   inc h
   jp remaining_string
   
end_string:

   pop hl                      ; hl = string width in pixels
   
   ; need to subtract font tracking from last char
   
   ld a,(ix+1)                 ; font tracking
   neg
   ld c,a
   ld b,$ff
   
   add hl,bc
   ret
   