
XLIB fzx_setat
LIB asm_fzx_setat

fzx_setat:

   pop af
   pop de
   pop hl
   push hl
   push de
   push af
   
   ld h,l
   ld l,e
   jp asm_fzx_setat
