;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; WAVEFORM STRUC                                                             ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

virtual at 0
    wf_area::
        rb 129 ; 64 + 64 + 1
end virtual

struc waveform?
    local l
    .:
    .length:
        dc.w l
    ; Observe current offset resides in RAM!
    .current_offset rs.w
    .data:

    macro x? str*
        ; take the string and convert it to a number between -64 and 64.
        ; with the help of a virtual output area.
        ; then emit it as a byte.

        if lengthof str <> 129
            error "waveform:x: string must be 129 characters long"
        end if

        store str : 129 at wf_area:0

        ; loop through to find `#`, save index, take -65 to get value
        ; between -64 and 64
        local b
        local result
        result = -1000
        repeat 129, i:0
            ; load from virtual output area
            load b:1 from wf_area:i
            if b = '#'
                result = i - 64
                break
            end if
        end repeat

        if result = -1000
            error "waveform:x: string must contain a `#`"
        else
            db result
        end if
    end macro

    macro end?.waveform?
        purge x?
        purge end?.waveform?

        .size := l
        l := $ - .data
    end macro
end struc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; WAVEFORM FUNCTIONS                                                         ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; parameters:
;     `a0.l`: waveform
;     `d0.w`: plane_start_row
;     `d1.b`: rows_to_animate (i.e. plane_end_row - plane_start_row)
;     `d5.w`: start row/index in waveform
; local variables:
;     `d2.w`: current value from waveform
;     `d3.w`: loop counter
;     `d4.w`: loop counter max
;     `d6.b`: hscroll addr ; TODO: improve comments!!!
apply_waveform:
        set_write_vram vram_hscroll_addr

    .right_place_loop: ; TODO: This is dumb. Should instead directly set correct address!
        cmp.b #0, d6
        beq .init_main_loop ;  TODO: which is the correct ne hs or whatever?

        move.w #00, vdp_data.l
        move.w #00, vdp_data.l
        sub.b #1, d6
        jmp .right_place_loop

    .init_main_loop:

        ; init loop counter = start row/index in waveform
        move.w d5, d3
        ; init loop counter max = waveform size + start row/index in waveform
        move.w d5, d4
        add.b d1, d4

    .loop:

        move.b (a0,d3.w), d2    ; get wf[i]
        ext.w d2            ; extend to word

        move.w d2,  vdp_data.l
        move.w d2,  vdp_data.l
        ; TODO: This is dumb. Reason I put 0 here is becasue even are plane a
        ;       and odd words are plane b. so this just means, dont scroll b...
        ; move.w #00, vdp_data.l
        addq #1, d3
        ; jump to loop if d3 < wf1.size
        cmp.b d4, d3
        ; bcc .loop
        bne .loop ;  TODO: which is the correct ne hs or whatever?

        rts