
; int wa_priority_queue_push(wa_priority_queue_t *q, void *item)

SECTION code_clib
SECTION code_adt_wa_priority_queue

PUBLIC wa_priority_queue_push_callee

EXTERN asm_wa_priority_queue_push

wa_priority_queue_push_callee:

   pop hl
   pop bc
   ex (sp),hl
   
   jp asm_wa_priority_queue_push
