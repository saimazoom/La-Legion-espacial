
; void p_forward_list_alt_clear_fastcall(p_forward_list_alt_t *list)

SECTION code_clib
SECTION code_adt_p_forward_list_alt

PUBLIC _p_forward_list_alt_clear_fastcall

EXTERN asm_p_forward_list_alt_clear

defc _p_forward_list_alt_clear_fastcall = asm_p_forward_list_alt_clear