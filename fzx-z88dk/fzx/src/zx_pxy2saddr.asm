
; the one in the spectrum library is not as useful as this one is
; place this here temporarily until I decide what to do about it

XLIB zx_pxy2saddr

zx_pxy2saddr:

   ; enter:  h = y coord 0-191
   ;         l = x coord 0-255
   ; exit : hl = screen address
   ;        carry reset if off screen
   ; uses : af, hl

   ld a,h
   cp 192
   ret nc
   
   and $07
   or $40
   ld d,a
   ld a,h
   rra
   rra
   rra
   and $18
   or d
   ld d,a

   srl l
   srl l
   srl l
   ld a,h
   rla
   rla
   and $e0
   or l

   ld l,a
   ld h,d
   ret
