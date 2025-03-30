vdp_data equ $C00000
vdp_data2 equ $C00002
vdp_ctrl equ $C00004
vdp_ctrl2 equ $C00006
    macro set_palette_color
    move.w #((\3)<<9) | ((\2)<<5) | ((\1)<<1), vdp_data
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
    dc.b 'GM XXXXXXXX-XX'
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
    move.l #$FF0000,sp
    move.b $A10001,d0
    andi.b #$F,d0
    beq.s skip_tmss
    move.l #'SEGA',$A14000
    skip_tmss:
    move.w #32773,vdp_ctrl
    move.w #33036,vdp_ctrl
    move.w #33280,vdp_ctrl
    move.w #33544,vdp_ctrl
    move.w #33794,vdp_ctrl
    move.w #34096,vdp_ctrl
    move.w #34304,vdp_ctrl
    move.w #34816,vdp_ctrl
    move.w #35072,vdp_ctrl
    move.w #35328,vdp_ctrl
    move.w #35584,vdp_ctrl
    move.w #35969,vdp_ctrl
    move.w #36128,vdp_ctrl
    move.w #36352,vdp_ctrl
    move.w #36610,vdp_ctrl
    move.w #36864,vdp_ctrl
    move.w #37120,vdp_ctrl
    move.w #37376,vdp_ctrl
    move.w #37632,vdp_ctrl
    move.w #37888,vdp_ctrl
    move.w #38144,vdp_ctrl
    move.w #38400,vdp_ctrl
    move.w #38656,vdp_ctrl
    move.l #$40000000, vdp_ctrl
    move.w #$7FFF, d7
    .ClearVRAM:
    move.w #$0000, vdp_data
    dbra d7,.ClearVRAM
    move.l #$7FFF, d7
    move.l #$FF0000, a0
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
    set_palette_color 7, 7, 7
    move.w #34567,vdp_ctrl
    move.w #32772,vdp_ctrl
    move.w #33068,vdp_ctrl
    move #$2300, sr
    MainLoop:
    bra MainLoop
    hblank:
    dc.b %01001110
    dc.b %01110011
    vblank:
    movem.l d1-d2,-(sp)
    add.w #1, color_index
    cmpi.w #(16<<2), color_index
    blo.s .done
    move.w #0, color_index
    .done:
    move.w color_index, d1
    lsr.w #2, d1
    jsr set_bg_color
    movem.l (sp)+,d1-d2
    dc.b %01001110
    dc.b %01110011
    int2_bus_error:
    dc.b %01001110
    dc.b %01110001
    dc.b %01001110
    dc.b %01110001
    bra int2_bus_error
    int3_address_error:
    dc.b %01001110
    dc.b %01110001
    dc.b %01001110
    dc.b %01110001
    dc.b %01001110
    dc.b %01110001
    bra int3_address_error
    int4_illegal_instruction:
    dc.b %01001110
    dc.b %01110001
    dc.b %01001110
    dc.b %01110001
    dc.b %01001110
    dc.b %01110001
    dc.b %01001110
    dc.b %01110001
    bra int4_illegal_instruction
    error:
    dc.b %01001110
    dc.b %01110001
    bra error
color_index equ 16711680
