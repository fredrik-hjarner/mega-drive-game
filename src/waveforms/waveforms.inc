;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; WAVEFORM STRUC                                                             ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; virtual output area where string is stored for later/further processing.
virtual at 0
    wf_area::
        ;        negative  positive  zero
        rb 256 ; 128 +     127 +     1
end virtual

struc waveform?
    local l
    .:
    ; stores the length of the waveform as the first word.
    .length:
        dc.w l
    ; Observe current offset resides in RAM!
    .current_offset rs.w
    ; the data of the waveform is placed after the length word.
    .data:

    macro x? str*
        ; take the string and convert it to a number between -128 and 127.
        ; with the help of a virtual output area.
        ; then emit it as a byte.

        if lengthof str <> 256
            error "waveform:x: string must be 256 characters long"
        end if

        store str : 256 at wf_area:0

        ; loop through to find `#`, save index, take -65 to get value
        ; between -128 and 127
        local b
        local result
        result = -1000
        repeat 256, i:0
            ; load from virtual output area
            load b:1 from wf_area:i
            if b = '#'
                result = i - 127
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

; creates a new waveform that is the inverse of the given waveform.
struc invert_waveform? wf*
    .:
    .length:
        dc.w wf.length
    .size := wf.size
    ; Observe current offset resides in RAM!
    .current_offset rs.w

    .data:
        ; here I must load the the data of `wf` and invert each of them then
        ; `db` the result.
        local b
        repeat .size, i:wf.data
            load b:1 from i
            db -b
        end repeat
end struc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; WAVEFORM FUNCTIONS                                                         ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Defined three functions:
;     apply_waveform_a
;     apply_waveform_b
;     apply_waveform_ab
;
; Each function takes the same parameters, but the function name indicates
; which plane(s) to scroll.
iterate suffix, a, b, ab
    ; parameters:
    ;     `a0.l`: waveform
    ;     `d0.w`: plane_start_row
    ;     `d1.b`: rows_to_animate (i.e. plane_end_row - plane_start_row)
    ;     `d5.w`: start row/index in waveform
    ; local variables:
    ;     `d2.w`: current value from waveform
    ;     `d3.w`: loop counter
    ;     `d4.w`: loop counter max
    ;     `d6.b`: how many pixels at top of screen to ignore, i.e. when scrolling starts.
    apply_waveform_#suffix:
            set_write_vram vram_hscroll_addr

        .right_place_loop: ; TODO: This is dumb. Should instead directly set correct address!
            cmp.b #0, d6
            beq .init_main_loop ;  TODO: which is the correct ne hs or whatever?

            move.w #00, vdp_data.l
            move.w #00, vdp_data.l
            subi.b #1, d6
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

            ; TODO: This is dumb. Reason I put 0 here is becasue even are
            ; plane a and odd words are plane b. so inserted zero just meeans
            ; dont scroll that plane...
            match =a, suffix
                move.w d2,  vdp_data.l ; scroll a
                move.w #00, vdp_data.l ; dont scroll b
            else match =b, suffix
                move.w #00, vdp_data.l ; dont scroll a
                move.w d2,  vdp_data.l ; scroll b
            else match =ab, suffix
                move.w d2,  vdp_data.l ; scroll both
                move.w d2,  vdp_data.l ; scroll both
            end match

            addq #1, d3
            ; jump to loop if d3 < wf1.size
            cmp.b d4, d3
            ; bcc .loop
            bne .loop ;  TODO: which is the correct ne hs or whatever?

            rts
end iterate