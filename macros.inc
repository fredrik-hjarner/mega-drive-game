    ; arguments:
    ;     \1: r: 0-7
    ;     \2: g: 0-7
    ;     \3: b: 0-7
    ; TODO: The name kinda sucks.
    ; TODO: This would be better as an inline fasmg macro.
    macro set_palette_color
        ; bbb0 ggg0 rrr0
        move.w  #((\3)<<9) | ((\2)<<5) | ((\1)<<1), vdp_data
    endm
