; wf for waveform
struc wf byte_array&
    .:
    .length:
        dc.w l
    ; Observe current offset resides in RAM!
    .current_offset rs.w
    .data:
        dc.b byte_array
    .size := l
        l := $ - .data
end struc

repeat 1, i:wf1
    display 'wf: ', `i, 10
end repeat

repeat 1, i:wf1.data
    display 'wf.data: ', `i, 10
end repeat

repeat 1, i:wf1.size
    display 'wf.size: ', `i, 10
end repeat

; Just testing to do some anination of one tile (i.e. 8 pixels hight)
wf1 wf \
    \ ; start off with no transform
     0, 0, 0, 0,     0, 0, 0, 0, \
     0, 0, 0, 0,     0, 0, 0, 0, \
     0, 0, 0, 0,     0, 0, 0, 0, \
     0, 0, 0, 0,     0, 0, 0, 0, \
    \ ; right
     1, 2, 3, 4,     5, 6, 7, 8, \ 
    \ ; left
     7, 6, 5, 4,     3, 2, 1, 0, \ 
    \ ; go back to beging "normal"/untransformed again
     0, 0, 0, 0,     0, 0, 0, 0, \
     0, 0, 0, 0,     0, 0, 0, 0, \
     0, 0, 0, 0,     0, 0, 0, 0, \
     0, 0, 0, 0,     0, 0, 0, 0

; parameters:
;     `a0.l`: waveform
;     `d0.w`: plane_start_row
;     `d1.b`: rows_to_animate (i.e. plane_end_row - plane_start_row)
;     `d5.w`: start row/index in waveform
; local variables:
;     `d2.w`: current value from waveform
;     `d3.w`: loop counter
;     `d4.w`: loop counter max
apply_waveform:
        set_write_vram vram_hscroll_addr

        ; init loop counter = start row/index in waveform
        move.w d5, d3
        ; init loop counter max = waveform size + start row/index in waveform
        move.w d5, d4
        add.b d1, d4

    .loop:

        move.b (a0,d3.w), d2    ; get wf[i]
        ext.w d2            ; extend to word

        move.w d2,  vdp_data.l
        move.w #00, vdp_data.l

        addq #1, d3
        ; jump to loop if d3 < wf1.size
        cmp.b d4, d3
        ; bcc .loop
        bne .loop ;  TODO: which is the correct ne hs or whatever?

        rts