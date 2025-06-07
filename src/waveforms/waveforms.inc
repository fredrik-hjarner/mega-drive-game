; wf for waveform
struc wf byte_array&
    local l
    .:
    .length:
        dc.w l
    .data:
        dc.b byte_array
        l := $ - .
end struc ; really, and not end struct?

wf1 wf 10,10,0,1,2,3,4,5,4,3,2,1,0,-1,-2,-3,-4,-5,-4,-3,-2,-1

; wave1:
;     dc.b 0,1,2,3,4,5,4,3,2,1,0,-1,-2,-3,-4,-5,-4,-3,-2,-1
; wave1_length := $ - wave1

; parameters:
;     `a0.l`: waveform
;     `d0.w`: plane_start_row
;     `d1.b`: rows_to_animate (i.e. plane_end_row - plane_start_row)
; local variables:
;     
apply_waveform:
        ; To begin with just hardcode a hscroll.
        set_write_vram vram_hscroll_addr
        ; then just put something in
        move.w #01, vdp_data.l
        move.w #01, vdp_data.l
        move.w #02, vdp_data.l
        move.w #02, vdp_data.l
        move.w #03, vdp_data.l
        move.w #03, vdp_data.l
        move.w #04, vdp_data.l
        move.w #04, vdp_data.l
        move.w #05, vdp_data.l
        move.w #05, vdp_data.l
        move.w #06, vdp_data.l
        move.w #06, vdp_data.l
        move.w #07, vdp_data.l
        move.w #07, vdp_data.l
        move.w #08, vdp_data.l
        move.w #08, vdp_data.l
        move.w #09, vdp_data.l
        move.w #09, vdp_data.l
        move.w #10, vdp_data.l
        move.w #10, vdp_data.l
        move.w #11, vdp_data.l
        move.w #11, vdp_data.l
        move.w #12, vdp_data.l
        move.w #12, vdp_data.l
        move.w #13, vdp_data.l
        move.w #13, vdp_data.l
        move.w #14, vdp_data.l
        move.w #14, vdp_data.l

        rts