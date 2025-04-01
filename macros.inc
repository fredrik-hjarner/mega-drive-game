    ; arguments:
    ;     \1: r: 0-7
    ;     \2: g: 0-7
    ;     \3: b: 0-7
    ; TODO: The name kinda sucks.
    ; TODO: This would be better as an inline fasmg macro.
    set_palette_color macro
        ; bbb0 ggg0 rrr0
        move.w  #((\3)<<9) | ((\2)<<5) | ((\1)<<1), vdp_data
    endm

    ; arguments:
    ;     \1: register number: 0-23d
    ;     \2: value: 8 bits
    ; macro set_vdp_register
    ;     move.w  #(1<<15 | ((\1)<<8) | (\2)), vdp_ctrl
    ; endm

    ; arguments:
    ;     \1: address: $0000-$FFFF
    ; https://segaretro.org/Sega_Mega_Drive/VDP_general_usage
    set_write_vram macro
        move.l #$40000000+(((\1)&$3FFF)<<16)+(((\1)&$C000)>>14),vdp_ctrl
    endm
