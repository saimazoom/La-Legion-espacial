
XLIB fzx_write
LIB asm_fzx_write

fzx_write:

   pop hl
   pop bc
   pop de
   push de
   push bc
   push hl
   
   jp asm_fzx_write
