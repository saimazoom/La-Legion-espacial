
XLIB fzx_cMetric
LIB asm_fzx_cMetric

fzx_cMetric:

   pop hl
   pop bc
   pop de
   push de
   push bc
   push hl
   
   ld a,c
   jp asm_fzx_cMetric
