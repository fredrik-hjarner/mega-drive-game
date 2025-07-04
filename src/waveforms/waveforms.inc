;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; WAVEFORM STRUC                                                             ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; virtual output area where string is stored for later/further processing.
virtual at 0
    wf_area::
        ;        negative  positive  zero
        rb 255 ; 127 +     127 +     1
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
        ; take the string and convert it to a number between -127 and 127.
        ; with the help of a virtual output area.
        ; then emit it as a byte.

        if lengthof str <> 255
            error "waveform:x: string must be 255 characters long"
        end if

        store str : 255 at wf_area:0

        ; loop through to find `#`, save index, take -65 to get value
        ; between -127 and 127
        local b
        local result
        result = -1000
        repeat 255, i:0
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
            ; Set vram auto increment to 4 if we're only scrolling one plane.
            ; Otherwise keep as-is (i.e. 2).
            match =a, suffix
                set_vdp_register $0F, 4
            else match =b, suffix
                set_vdp_register $0F, 4
            end match

            ; If scrolling just plane b we need to skip to first plane b row.
            match =b, suffix
                set_write_vram vram_hscroll_addr + 2
            else
                set_write_vram vram_hscroll_addr
            end match


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

            ; Remember that even words are plane a and odd words are plane b.
            ; Also remember that we set different auto increment values
            ; depending on if we're scrolling just one plane or both planes.
            match =a, suffix
                move.w d2,  vdp_data.l ; scroll a
            else match =b, suffix
                move.w d2,  vdp_data.l ; scroll b
            else match =ab, suffix
                move.w d2,  vdp_data.l ; scroll a
                move.w d2,  vdp_data.l ; scroll b
            end match

            addq #1, d3
            ; jump to loop if d3 < wf1.size
            cmp.b d4, d3
            ; bcc .loop
            bne .loop ;  TODO: which is the correct ne hs or whatever?

            ; Reset vram auto increment to 2.
            match =a, suffix
                set_vdp_register $0F, 2
            else match =b, suffix
                set_vdp_register $0F, 2
            end match

            rts
end iterate