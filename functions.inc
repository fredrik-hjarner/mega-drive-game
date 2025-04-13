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

; TODO: Comment
update_color:
        ; if not a then skip
        tst.b gamepad1_a
        beq.b .skip
        addq.w #1, color_index
        cmpi.w #(16<<2), color_index
        blo.b .increment
        move.w #0, color_index
    .increment:
        move.w color_index, d1
        ; right shift d1 to get the color index
        lsr.w #2, d1
        jsr set_bg_color
    .skip:
        rts

; TODO: Comment
update_hscroll:
        tst.b gamepad1_left
        beq.b .skip_left
        add.w #-1, hscroll_amount
        bra.b .increment
    .skip_left:
        tst.b gamepad1_right
        beq.b .skip_right
        add.w #1, hscroll_amount
    .increment:
        move.w hscroll_amount, d1
        ; right shift d1 to slower speed or something.
        lsr.w #2, d1
        ; now also scroll plane A and plane B
        set_write_vram vdp_hscroll_addr
        move.w d1, vdp_data
        move.w d1, vdp_data
    .skip_right:
        rte