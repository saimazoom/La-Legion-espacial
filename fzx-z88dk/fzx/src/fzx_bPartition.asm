
XLIB fzx_bPartition
LIB asm_fzx_bPartition

fzx_bPartition:

   pop af
   pop hl
   pop bc
   pop de
   push de
   push bc
   push hl
   push af
   
   jp asm_fzx_bPartition
