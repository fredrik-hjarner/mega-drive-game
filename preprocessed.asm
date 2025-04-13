vdp_data equ $C00000
vdp_data2 equ $C00002
vdp_ctrl equ $C00004
vdp_ctrl2 equ $C00006
vdp_hscroll_addr equ $400
vdp_tiles_addr equ $0000
gamepad1_ctrl equ $A10009
gamepad1_data equ $A10003
gamepad2_ctrl equ $A1000B
gamepad2_data equ $A10005
set_palette_color macro
    move.w #((\3)<<9) | ((\2)<<5) | ((\1)<<1), vdp_data
    endm
set_write_vram macro
    move.l #$40000000+(((\1)&$3FFF)<<16)+(((\1)&$C000)>>14),vdp_ctrl
    endm
gamepads_get_input macro
    move.b #$40, gamepad1_ctrl
    lea gamepad1_data, a0
    move.b #$40, (a0)
    dc.b %01001110
    dc.b %01110001
    dc.b %01001110
    dc.b %01110001
    move.b (a0), d0
    not.b d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_up
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_down
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_left
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_right
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_b
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_c
    move.b #$00, (a0)
    dc.b %01001110
    dc.b %01110001
    dc.b %01001110
    dc.b %01110001
    move.b (a0), d0
    not.b d0
    lsr.b #4, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_a
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_start
    endm
    dc.l 0
    dc.l Start
    dc.l int2_bus_error
    dc.l int3_address_error
    dc.l int4_illegal_instruction
    dc.l error
    dc.l error
    dc.l error
    dc.l error
    dc.l error
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l error
    dc.l error
    dc.l error
    dc.l 0,0,0,0,0,0,0,0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l hblank
    dc.l 0
    dc.l vblank
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0
    dc.l 0,0,0,0,0
    dc.b 'SEGA GENESIS    '
    dc.b '                '
    dc.b 'EPIC LEGENDS OF DESTINY                         '
    dc.b 'EPIC LEGENDS OF DESTINY                         '
    dc.b 'GM 147858 '
    org $18E
    dc.w $0000
    dc.b 'J               '
    dc.l $00000000
    dc.l $00100000
    dc.l $00FF0000
    dc.l $00FFFFFF
    dc.l $00000000
    dc.l $00000000
    dc.l $00000000
    dc.b '    '
    dc.b '        '
    dc.b '        '
    dc.b '                '
    dc.b '                '
    dc.b 'JUE             '
    set_bg_color:
    move.w #(1<<15 | (7<<8)), d2
    or.w d1, d2
    move.w d2, vdp_ctrl
    dc.b %01001110
    dc.b %01110101
    Start:
    move.w #$2700,sr
    movea.l #$FF0000,sp
    move.b $A10001,d0
    andi.b #$F,d0
    beq.s skip_tmss
    move.l #'SEGA',$A14000
    skip_tmss:
    move.w #33028,vdp_ctrl
    move.w #33288,vdp_ctrl
    move.w #33552,vdp_ctrl
    move.w #33795,vdp_ctrl
    move.w #34112,vdp_ctrl
    move.w #34304,vdp_ctrl
    move.w #34816,vdp_ctrl
    move.w #35072,vdp_ctrl
    move.w #35328,vdp_ctrl
    move.w #35584,vdp_ctrl
    move.w #35969,vdp_ctrl
    move.w #36097,vdp_ctrl
    move.w #36352,vdp_ctrl
    move.w #36610,vdp_ctrl
    move.w #36864,vdp_ctrl
    move.w #37120,vdp_ctrl
    move.w #37376,vdp_ctrl
    move.l #$40000000, vdp_ctrl
    move.w #$3FFF, d7
    .ClearVRAM:
    move.l #$00000000, vdp_data
    dbra d7,.ClearVRAM
    move.l #$7FFF, d7
    movea.l #$FF0000, a0
    .ClearRAM:
    move.w #$0000, (a0)+
    dbra d7,.ClearRAM
    move.l #$C0000000, vdp_ctrl
    set_palette_color 0, 0, 0
    set_palette_color 1, 0, 0
    set_palette_color 2, 0, 0
    set_palette_color 3, 0, 0
    set_palette_color 4, 0, 0
    set_palette_color 5, 0, 0
    set_palette_color 6, 0, 0
    set_palette_color 7, 0, 0
    set_palette_color 7, 0, 1
    set_palette_color 7, 0, 2
    set_palette_color 7, 0, 3
    set_palette_color 7, 0, 4
    set_palette_color 7, 0, 5
    set_palette_color 7, 0, 6
    set_palette_color 7, 0, 7
    set_palette_color 7, 1, 7
    move.l #$40000000, vdp_ctrl
    move.l #$10000000, vdp_data
    move.l #$11000000, vdp_data
    move.l #$11100000, vdp_data
    move.l #$11110000, vdp_data
    move.l #$11111000, vdp_data
    move.l #$11111100, vdp_data
    move.l #$11111110, vdp_data
    move.l #$11111111, vdp_data
    move.w #34567,vdp_ctrl
    move.w #32772,vdp_ctrl
    move.w #33124,vdp_ctrl
    move #$2300, sr
    MainLoop:
    bra.b MainLoop
    hblank:
    dc.b %01001110
    dc.b %01110011
    vblank:
    movem.l d1-d2,-(sp)
    gamepads_get_input
    tst.b gamepad1_a
    beq.b .skip
    addq.w #1, color_index
    cmpi.w #(16<<2), color_index
    blo.s .done
    move.w #0, color_index
    .done:
    move.w color_index, d1
    lsr.w #2, d1
    jsr (set_bg_color).w
    set_write_vram vdp_hscroll_addr
    move.w d1, vdp_data
    move.w d1, vdp_data
    .skip:
    movem.l (sp)+,d1-d2
    dc.b %01001110
    dc.b %01110011
    int2_bus_error:
    dc.b %01001110
    dc.b %01110001
    dc.b %01001110
    dc.b %01110001
    bra.b int2_bus_error
    int3_address_error:
    dc.b %01001110
    dc.b %01110001
    dc.b %01001110
    dc.b %01110001
    dc.b %01001110
    dc.b %01110001
    bra.b int3_address_error
    int4_illegal_instruction:
    dc.b %01001110
    dc.b %01110001
    dc.b %01001110
    dc.b %01110001
    dc.b %01001110
    dc.b %01110001
    dc.b %01001110
    dc.b %01110001
    bra.b int4_illegal_instruction
    error:
    dc.b %01001110
    dc.b %01110001
    bra.b error
color_index equ 16711680
gamepad1_up equ 16711682
gamepad1_down equ 16711683
gamepad1_left equ 16711684
gamepad1_right equ 16711685
gamepad1_b equ 16711686
gamepad1_c equ 16711687
gamepad1_a equ 16711688
gamepad1_start equ 16711689
gamepad2_up equ 16711690
gamepad2_down equ 16711691
gamepad2_left equ 16711692
gamepad2_right equ 16711693
gamepad2_b equ 16711694
gamepad2_c equ 16711695
gamepad2_a equ 16711696
gamepad2_start equ 16711697
