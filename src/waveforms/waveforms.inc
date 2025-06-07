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
;     
apply_waveform:
        ; To begin with just hardcode a hscroll.
        set_write_vram vram_hscroll_addr
        ; then just put something in

    repeat wf1.size, i:0
        move.b i(a0), d2    ; get wf[0]
        ext.w d2            ; extend to word

        move.w d2,  vdp_data.l
        move.w #00, vdp_data.l
    end repeat

        rts

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; RAM                                                                        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; where is the waveform we are currently
wf_current_index    rs.w