; arguments:
;     d1: color index (0-7)
; returns:
;     nothing
set_bg_color:
    ; Set VDP register 7 to the color index in d1
    move.w  #(1<<15 | (7<<8)), d2    ; Create the command word for register 7
    or.w    d1, d2                   ; OR in the color index from d1
    move.w  d2, vdp_ctrl             ; Write to VDP control register
    rts
