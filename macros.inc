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

    ; https://plutiedev.com/controllers
    ; #$40 needs to be sent to control and data ports for some reason.
    ; init_gampads macro
    ;     ; set bit 6 to "write"
    ;     move.b #$40, gamepad1_ctrl
    ;     ; move.b #$40, gamepad1_data
    ;     move.b #$40, gamepad2_ctrl
    ;     ; move.b #$40, gamepad2_data
    ; endm

    ; https://plutiedev.com/controllers
    gamepads_get_input macro
        ; a0 = IoData1 for player 1
        ;    = IoData2 for player 2

        move.b #$40, gamepad1_ctrl

        lea  gamepad1_data, a0
        
        ; set bit 6 (TH) to 1 to get first group of buttons
        move.b  #$40, (a0)  ; Do 1st step
        nop                 ; D-pad, B and C
        nop
        move.b  (a0), d0
        
        ; set bit 6 (TH) to 0 to get second group of buttons
        move.b  #$00, (a0)  ; Do 2nd step
        nop                 ; A and Start
        nop
        move.b  (a0), d1
        
        andi.b   #$3F, d0    ; Rearrange bits
        andi.b   #$30, d1    ; into SACBRLDU
        lsl.b   #2, d1
        or.b    d1, d0

        ; invert
        not.b d0

        move.b d0, gamepad1
        
        ; Now d0 contains all the buttons
        ; May want to use a NOT if you prefer
        ; 1 = pressed and 0 = released
    endm
