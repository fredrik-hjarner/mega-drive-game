    rsset $FF0000
vdp_data equ $C00000
vdp_data2 equ $C00002
vdp_ctrl equ $C00004
vdp_ctrl2 equ $C00006
vram_hscroll_addr equ $0400
vram_plane_a_addr equ $2000
vdp_tiles_addr equ $0000
gamepad1_ctrl equ $A10009
gamepad1_data equ $A10003
gamepad2_ctrl equ $A1000B
gamepad2_data equ $A10005
screen_w_in_tiles equ 40
screen_h_in_tiles equ 28
plane_w_in_tiles equ 32
plane_h_in_tiles equ 32
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
    dc.b 'GM 182532 '
    cnop 0,$18E
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
    move.w d2, vdp_ctrl.l
    rts
    update_color:
    tst.b (gamepad1_a).l
    beq.b .skip
    addq.w #1, color_index.l
    cmpi.w #(16<<2), color_index.l
    blo.b .increment
    move.w #0, color_index.l
    .increment:
    move.w color_index.l, d1
    lsr.w #2, d1
    jsr set_bg_color.l
    .skip:
    rts
    update_hscroll:
    tst.b gamepad1_left.l
    beq.b .skip_left
    addi.w #-1, hscroll_amount.l
    bra.b .increment
    .skip_left:
    tst.b gamepad1_right.l
    beq.b .skip_right
    addi.w #1, hscroll_amount.l
    .increment:
    move.w hscroll_amount.l, d1
    lsr.w #2, d1
    move.l #$40000000+(((vram_hscroll_addr)&$3FFF)<<16)+(((vram_hscroll_addr)&$C000)>>14),vdp_ctrl.l
    move.w d1, vdp_data.l
    move.w d1, vdp_data.l
    move.l #$40000010+(($0)<<16),vdp_ctrl.l
    move.w d1, vdp_data.l
    move.w d1, vdp_data.l
    .skip_right:
    rte
    set_plane_tile:
    move.w d0, vdp_data.l
    rts
hblanks_per_100Hz_tick equ 156
hblanks_per_50Hz_tick equ 312
hblanks_per_1Hz_tick equ 15600
timer_100Hz_counter rs.w 1
timer_50Hz_counter rs.w 1
timer_1Hz_counter rs.w 1
    hblank:
    move.w d0, -(sp)
    addi.w #1, timer_100Hz_counter.l
    move.w timer_100Hz_counter.l, d0
    cmpi.w #hblanks_per_100Hz_tick, d0
    blt.w .skip100HzCallback
    move.w #0, timer_100Hz_counter.l
    jsr timer_100Hz_callback.l
    .skip100HzCallback:
    addi.w #1, timer_50Hz_counter.l
    move.w timer_50Hz_counter.l, d0
    cmpi.w #hblanks_per_50Hz_tick, d0
    blt.w .skip50HzCallback
    move.w #0, timer_50Hz_counter.l
    jsr timer_50Hz_callback.l
    .skip50HzCallback:
    addi.w #1, timer_1Hz_counter.l
    move.w timer_1Hz_counter.l, d0
    cmpi.w #hblanks_per_1Hz_tick, d0
    blt.w .skip1HzCallback
    move.w #0, timer_1Hz_counter.l
    jsr timer_1Hz_callback.l
    .skip1HzCallback:
    move.w (sp)+, d0
    rte
    timer_100Hz_callback:
    rts
    timer_50Hz_callback:
    rts
    timer_1Hz_callback:
    rts
    Start:
    move.w #$2700,sr
    movea.l #$FF0000,sp
    move.b $A10001.l,d0
    andi.b #$F,d0
    beq.b skip_tmss
    move.l #'SEGA',$A14000.l
    skip_tmss:
    move.w #32772,vdp_ctrl.l
    move.w #33028,vdp_ctrl.l
    move.w #33288,vdp_ctrl.l
    move.w #33536,vdp_ctrl.l
    move.w #33795,vdp_ctrl.l
    move.w #34112,vdp_ctrl.l
    move.w #34304,vdp_ctrl.l
    move.w #34816,vdp_ctrl.l
    move.w #35072,vdp_ctrl.l
    move.w #35328,vdp_ctrl.l
    move.w #35584,vdp_ctrl.l
    move.w #35969,vdp_ctrl.l
    move.w #36097,vdp_ctrl.l
    move.w #36352,vdp_ctrl.l
    move.w #36610,vdp_ctrl.l
    move.w #36864,vdp_ctrl.l
    move.w #37120,vdp_ctrl.l
    move.w #37376,vdp_ctrl.l
    move.l #$40000000, vdp_ctrl.l
    move.w #$3FFF, d7
    .ClearVRAM:
    move.l #$00000000, vdp_data.l
    dbra.w d7,.ClearVRAM
    move.l #$7FFF, d7
    movea.l #$FF0000, a0
    .ClearRAM:
    move.w #$0000, (a0)+
    dbra.w d7,.ClearRAM
    move.l #$C0000000, vdp_ctrl.l
    move.w #((0)<<9) | ((0)<<5) | ((0)<<1), vdp_data.l
    move.w #((1)<<9) | ((1)<<5) | ((7)<<1), vdp_data.l
    move.w #((0)<<9) | ((7)<<5) | ((7)<<1), vdp_data.l
    move.w #((1)<<9) | ((7)<<5) | ((1)<<1), vdp_data.l
    move.w #((6)<<9) | ((6)<<5) | ((0)<<1), vdp_data.l
    move.w #((7)<<9) | ((1)<<5) | ((1)<<1), vdp_data.l
    move.w #((5)<<9) | ((0)<<5) | ((5)<<1), vdp_data.l
    move.w #((0)<<9) | ((0)<<5) | ((5)<<1), vdp_data.l
    move.w #((0)<<9) | ((3)<<5) | ((3)<<1), vdp_data.l
    move.w #((0)<<9) | ((5)<<5) | ((0)<<1), vdp_data.l
    move.w #((3)<<9) | ((3)<<5) | ((0)<<1), vdp_data.l
    move.w #((5)<<9) | ((0)<<5) | ((0)<<1), vdp_data.l
    move.w #((3)<<9) | ((0)<<5) | ((3)<<1), vdp_data.l
    move.w #((0)<<9) | ((0)<<5) | ((0)<<1), vdp_data.l
    move.w #((4)<<9) | ((4)<<5) | ((4)<<1), vdp_data.l
    move.w #((7)<<9) | ((7)<<5) | ((7)<<1), vdp_data.l
    move.l #$40000000, vdp_ctrl.l
    move.l #$00000000, vdp_data.l
    move.l #$00000000, vdp_data.l
    move.l #$00000000, vdp_data.l
    move.l #$00000000, vdp_data.l
    move.l #$00000000, vdp_data.l
    move.l #$00000000, vdp_data.l
    move.l #$00000000, vdp_data.l
    move.l #$00000000, vdp_data.l
    move.l #$11111111, vdp_data.l
    move.l #$11111111, vdp_data.l
    move.l #$11111111, vdp_data.l
    move.l #$11111111, vdp_data.l
    move.l #$11111111, vdp_data.l
    move.l #$11111111, vdp_data.l
    move.l #$11111111, vdp_data.l
    move.l #$11111111, vdp_data.l
    move.l #$22222222, vdp_data.l
    move.l #$22222222, vdp_data.l
    move.l #$22222222, vdp_data.l
    move.l #$22222222, vdp_data.l
    move.l #$22222222, vdp_data.l
    move.l #$22222222, vdp_data.l
    move.l #$22222222, vdp_data.l
    move.l #$22222222, vdp_data.l
    move.l #$33333333, vdp_data.l
    move.l #$33333333, vdp_data.l
    move.l #$33333333, vdp_data.l
    move.l #$33333333, vdp_data.l
    move.l #$33333333, vdp_data.l
    move.l #$33333333, vdp_data.l
    move.l #$33333333, vdp_data.l
    move.l #$33333333, vdp_data.l
    move.l #$44444444, vdp_data.l
    move.l #$44444444, vdp_data.l
    move.l #$44444444, vdp_data.l
    move.l #$44444444, vdp_data.l
    move.l #$44444444, vdp_data.l
    move.l #$44444444, vdp_data.l
    move.l #$44444444, vdp_data.l
    move.l #$44444444, vdp_data.l
    move.l #$55555555, vdp_data.l
    move.l #$55555555, vdp_data.l
    move.l #$55555555, vdp_data.l
    move.l #$55555555, vdp_data.l
    move.l #$55555555, vdp_data.l
    move.l #$55555555, vdp_data.l
    move.l #$55555555, vdp_data.l
    move.l #$55555555, vdp_data.l
    move.l #$66666666, vdp_data.l
    move.l #$66666666, vdp_data.l
    move.l #$66666666, vdp_data.l
    move.l #$66666666, vdp_data.l
    move.l #$66666666, vdp_data.l
    move.l #$66666666, vdp_data.l
    move.l #$66666666, vdp_data.l
    move.l #$66666666, vdp_data.l
    move.l #$40000000+(((vram_plane_a_addr)&$3FFF)<<16)+(((vram_plane_a_addr)&$C000)>>14),vdp_ctrl.l
    move.w #plane_w_in_tiles-1, d1
    .loop:
    move.w #$1, d0
    jsr set_plane_tile.l
    dbra.w d1, .loop
    move.w #plane_w_in_tiles-1, d1
    .loop2:
    move.w #$2, d0
    jsr set_plane_tile.l
    dbra.w d1, .loop2
    move.w #plane_w_in_tiles-1, d1
    .loop3:
    move.w #$3, d0
    jsr set_plane_tile.l
    dbra.w d1, .loop3
    move.w #plane_w_in_tiles-1, d1
    .loop4:
    move.w #$4, d0
    jsr set_plane_tile.l
    dbra.w d1, .loop4
    move.w #plane_w_in_tiles-1, d1
    .loop5:
    move.w #$5, d0
    jsr set_plane_tile.l
    dbra.w d1, .loop5
    move.w #plane_w_in_tiles-1, d1
    .loop6:
    move.w #$6, d0
    jsr set_plane_tile.l
    dbra.w d1, .loop6
    move.w #34567,vdp_ctrl.l
    move.w #33124,vdp_ctrl.l
    move.w #$2300, sr
    MainLoop:
    bra.b MainLoop
    vblank:
    movem.l d1-d2,-(sp)
    move.b #$40, gamepad1_ctrl.l
    lea.l gamepad1_data.l, a0
    move.b #$40, (a0)
    nop
    nop
    move.b (a0), d0
    not.b d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_up.l
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_down.l
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_left.l
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_right.l
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_b.l
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_c.l
    move.b #$00, (a0)
    nop
    nop
    move.b (a0), d0
    not.b d0
    lsr.b #4, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_a.l
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_start.l
    jsr update_color.l
    jsr update_hscroll.l
    movem.l (sp)+,d1-d2
    rte
    int2_bus_error:
    nop
    nop
    bra.b int2_bus_error
    int3_address_error:
    nop
    nop
    nop
    bra.b int3_address_error
    int4_illegal_instruction:
    nop
    nop
    nop
    nop
    bra.b int4_illegal_instruction
    error:
    nop
    bra.b error
color_index rs.w 1
hscroll_amount rs.w 1
gamepad1_up rs.b 1
gamepad1_down rs.b 1
gamepad1_left rs.b 1
gamepad1_right rs.b 1
gamepad1_b rs.b 1
gamepad1_c rs.b 1
gamepad1_a rs.b 1
gamepad1_start rs.b 1
gamepad2_up rs.b 1
gamepad2_down rs.b 1
gamepad2_left rs.b 1
gamepad2_right rs.b 1
gamepad2_b rs.b 1
gamepad2_c rs.b 1
gamepad2_a rs.b 1
gamepad2_start rs.b 1
