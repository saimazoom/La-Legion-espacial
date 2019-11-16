;          CRT_ORG_CODE = start address
;	       CRT_ORG_BSS = address for bss variables
;          CRT_MODEL   = 0 (RAM), 1 = (ROM, code copied), 2 = (ROM, code compressed)
;

        MODULE  crt0_base
;--------
; Include zcc_opt.def to find out some info
;--------

        defc    crt0 = 1
        INCLUDE "zcc_opt.def"

;--------
; Some scope definitions
;--------

        EXTERN    _main           ; main() is always external to crt0 code
        org     24200
        di
        XOR    A
        LD     I,A

        ld      iy,23610        ; restore the right iy value, 
                                ; fixing the self-relocating trick, if any
        ld      sp,STACKPTR
        ld      hl,-64
        add     hl,sp
        ld      sp,hl
        call    _main
        