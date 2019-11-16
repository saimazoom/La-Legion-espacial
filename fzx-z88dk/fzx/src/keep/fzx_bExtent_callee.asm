
; ===============================================================
; aralbrec - Nov 2013
; ===============================================================
;
; uint fzx_bExtent(void *buf, uint len)
;
; Returns the width of the buffer of chars in pixels.  Characters
; left undefined by the font are treated as '?'.  Unprinted chars,
; which include '\n' and three-byte AT sequences, are considered
; zero width.
;
; ===============================================================

XLIB fzx_bExtent_callee
XDEF asm_fzx_bExtent

LIB __fzx_width_sm, _fzx, error_zc

DEFC FONT = 0

fzx_bExtent_callee:

   pop hl
   pop de
   ex (sp),hl

asm_fzx_bExtent:

   ; enter : hl = void *buf
   ;         de = uint len
   ;
   ; exit  : hl = width of string in pixels
   ;         de = buf+len
   ;         ix = struct fzx_font *
   ;
   ; uses  : af, bc, de, hl, ix
   
   ld ix,(_fzx + FONT)         ; ix = current font = struct fzx_font *
   
   ; the first character's kern does not count in width
   
   ld b,1                      ; num chars to skip in buffer + 1
   
loop_first:

   ld a,d                      ; end of buffer reached?
   or e
   jp z, error_zc              ; return with hl = width = 0
   
   ld a,(hl)                   ; a = char
   push hl
   call __fzx_width_sm         ; get width of glyph
   jr nc, first_char
   pop hl
   
   inc hl
   dec de
   jp loop_first

first_char:

   ; add back kern to first char's width
   
   add a,b
   ld l,a
   ld h,0                      ; hl = current width of string
   
remaining_string:

   ld b,1                      ; b = num chars to skip in string + 1
   ex (sp),hl                  ; hl = void *buf, stack = width of string
   
loop_rest:

   ; de = remaining len in buffer
   ;  b = num chars to skip + 1
   ; hl = void *buf
   ; stack = width of string

   inc hl
   dec de
   
   ld a,d                      ; end of buffer reached?
   or e
   jr z, end_string

   ld a,(hl)                   ; a = char
   push hl
   call __fzx_width_sm         ; get width of glyph
   pop hl
   jr c, loop_rest             ; ignore unprintable char
   
   ex (sp),hl                  ; hl = current width of string
   
   add a,l                     ; add glyph width
   ld l,a
   jp nc, remaining_string
   
   inc h
   jp remaining_string
   
end_string:

   ex de,hl                    ; de = void *buf
   pop hl                      ; hl = string width in pixels
   
   ; need to subtract font tracking from last char
   
   ld a,(ix+1)                 ; font tracking
   neg
   ld c,a
   ld b,$ff
   
   add hl,bc
   ret
