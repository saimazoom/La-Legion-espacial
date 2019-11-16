; **************************************************
; SMSlib - C programming library for the SMS/GG
; ( part of devkitSMS - github.com/sverx/devkitSMS )
; **************************************************

INCLUDE "SMSlib_private.inc"

SECTION code_clib
SECTION code_SMSlib

PUBLIC asm_SMSlib_UNSAFE_VRAMmemcpy32

EXTERN asm_SMSlib_outi32

asm_SMSlib_UNSAFE_VRAMmemcpy32:

   ; void UNSAFE_SMS_VRAMmemcpy32 (unsigned int dst, void *src)
   ;
   ; enter : hl = unsigned int dst
   ;         de = void *src
   ;
   ; uses  : f, bc, de, hl
   
   set 6,h
   INCLUDE "SMS_CRT0_RST08.inc"
   
   ld c,VDPDataPort
   ex de,hl

   jp asm_SMSlib_outi32
