
; struct fzx_state fzx
;
; Holds state for the fzx driver

XLIB _fzx

_fzx:

   defw 0                      ; pointer to current font (struct fzx_font *)
   defb 0                      ; left margin in pixels
   defb 0                      ; flags
   defb 0                      ; x coordinate in pixels
   defb 0                      ; y coordinate in pixels

