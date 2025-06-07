; wf for waveform
struc wf byte_array&
    .:
    .length:
        dc.w l
    .data:
        dc.b byte_array
    .size := l
        l := $ - .data
end struc ; really, and not end struct?

repeat 1, i:wf1
    display 'wf: ', `i, 10
end repeat

repeat 1, i:wf1.data
    display 'wf.data: ', `i, 10
end repeat

repeat 1, i:wf1.size
    display 'wf.size: ', `i, 10
end repeat

wf1 wf  0, 1, 2, 3,     4, 5, 4, 3, \ 
        2, 1, 0,-1,    -2,-3,-4,-5, \
       -4,-3,-2,-1,     0, 1, 2, 3, \
        4, 3, 2, 1,     0,-1,-2,-3, \
       -4,-5,-4,-3,    -2,-1, 0, 1

; parameters:
;     `a0.l`: waveform
;     `d0.w`: plane_start_row
;     `d1.b`: rows_to_animate (i.e. plane_end_row - plane_start_row)
; local variables:
;     `d2.w`: current value
;     `d3.b`: loop counter
apply_waveform:
        set_write_vram vram_hscroll_addr

        ; init loop counter
        move.w #0, d3

    .loop:

        move.b (a0,d3.w), d2    ; get wf[i]
        ext.w d2            ; extend to word

        move.w d2,  vdp_data.l
        move.w #00, vdp_data.l

        addq #1, d3
        ; jump to loop if d3 < wf1.size
        cmp.b #wf1.size, d3
        ; bcc .loop
        bne .loop ;  TODO: which is the correct ne hs or whatever?

        rts

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; RAM                                                                        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; where is the waveform we are currently
wf_current_index    rs.w