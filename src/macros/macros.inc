; arguments:
;     reg_nr: register number: 0-23d
;     value:  value: 8 bits
calminstruction set_vdp_register reg_nr, value
    local   set_reg
    local   reg
    local   res
    local   cmd

    compute set_reg, 1 shl 15
    compute reg, reg_nr shl 8
    compute res, set_reg or reg or value

    asm     move.w #res, vdp_ctrl.l
end calminstruction

calminstruction meta_version
        local   tmp
        local   s_since_2025
        local   m_since_2025

        compute     tmp, __time__
        compute     s_since_2025, tmp - 1735686000
        compute     m_since_2025, s_since_2025 / 60
        arrange     tmp, =GM m_since_2025
        stringify   tmp
        emit        14, tmp
end calminstruction

; TODO: Explain exactly what this does and how it is intended to be used.
; arguments:
;     r: 0-7
;     g: 0-7
;     b: 0-7
; TODO: The name kinda sucks.
; TODO: This would be better as an inline fasmg macro.
calminstruction set_palette_color? r, g, b
    local tmp
    ; bbb0 ggg0 rrr0
    compute     tmp, (b shl 9) or (g shl 5) or (r shl 1)
    arrange     tmp, =move.=w= =#tmp,=vdp_data.=l
    assemble    tmp
end calminstruction

; arguments:
;     addr: address: $0000-$FFFF
; https://segaretro.org/Sega_Mega_Drive/VDP_general_usage
calminstruction set_write_vram? addr
    local   tmp
    compute tmp, $40000000 + ((addr and $3FFF) shl 16)+((addr and $C000) shr 14)
    asm     move.l #tmp, vdp_ctrl.l
end calminstruction

; arguments:
;     addr: address: $00-$FF
; https://segaretro.org/Sega_Mega_Drive/VDP_general_usage
calminstruction set_write_vsram? addr
    local   tmp
    compute tmp, $40000010 + addr shl 16
    asm     move.l #tmp, vdp_ctrl.l
end calminstruction

; bappend
; Util macro for CALM to concatenate strings with shorter syntax.
; Only works when added to preprocess.asm
; Example:
;     calminstruction tester
;         local tmp, tmp2
;         bappend tmp, 13, 10
;         display tmp ; Output: empty line
;         bappend tmp, "a", "b", "c", 13, 10
;         display tmp ; Output: abc
;         compute tmp2, "$"
;         bappend tmp, tmp2, "a", "b", "c", 13, 10
;         display tmp ; Output: $abc
;     end calminstruction
;     tester
; OBSERVE! I managed to make a version of append that works without
; preprocess.asm so I am using that instead.
; macro bappend dest*, strings&
;     emit compute dest, ""
;     iterate string, strings
;         emit compute dest, dest bappend string
;     end iterate
; end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; PLANE STUFF                                                                ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO: Explain what this is and why it is.
virtual at 0
    string_tile_row::
    rb 64 ; 40h
end virtual
; TODO: Explain what this is and why it is.
virtual at 0
    char_to_tile_map::
    rb 256 ; covers all ascii values
end virtual
iterate <char, tile>, \
        ' ',   0, \
        '0',   0, \
        '1',   1, \
        '2',   2, \
        '3',   3, \
        '4',   4, \
        '5',   5, \
        '6',   6, \
        '7',   7, \
        '8',   8, \
        '9',   9, \
        'A',   10, \
        'B',   11, \
        'C',   12, \
        'D',   13, \
        'E',   14, \
        'F',   15

        store tile:1 at char_to_tile_map:char
end iterate

calminstruction str_to_tile_indices str
        local tmp
        compute tmp, str
        ; Store the string in the string_tile_row
        store string_tile_row:0, \  ; offset to store at
              64, \                 ; number of bytes to store
              tmp                   ; the value to store (numeric or string)
        ; now go through all of them and emit each
        local i
        compute i, 0
    next:
        check i >= 64
        jyes done
        ; Quote: The loaded value is always a string of the specified length.
        load tmp, \                     ; target variable
             string_tile_row:i, \       ; offset to load from
             1                          ; number of bytes to load
        compute tmp, +tmp
        arrange tmp, tmp
        load tmp, \                     ; target variable
             char_to_tile_map:tmp, \    ; offset to load from
             1                          ; number of bytes to load

        emit_be 2, tmp
        ; compute tmp, +tmp
        ; arrange tmp, tmp
        ; arrange tmp, =dc.=w tmp
        ; assemble tmp

        compute i, i + 1
        jump next
    done:
end calminstruction

; arguments:
;     c: color: 0-15
; TODO: This is not working.
calminstruction create_single_color_tile? c
    local     tmp
    arrange   tmp, =move.=l= =#=$#c#c#c#c#c#c#c#c,=vdp_data.=l
    transform tmp
    assemble  tmp
end calminstruction
