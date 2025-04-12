    include "consts.inc"
    include "macros.inc"

; =====================================================================
; HEADER 512 bytes ($200 bytes)
; =====================================================================

    include "vectors.inc"         ; interrupt vectors
    include "meta.inc"            ; ROM metadata (console name, region, etc.)

; =====================================================================
; OTHER INCLUDES
; =====================================================================

    include "functions.inc"

; =====================================================================
; PROGRAM START (Code begins at $200 because the ROM header is $200 bytes)
; =====================================================================

Start:
    ; -----------------------------------------------------------------
    ; INITIALIZE SYSTEM
    ; -----------------------------------------------------------------
    move.w  #$2700,sr             ; Disable interrupts (status register)
    movea.l  #$FF0000,sp           ; Set stack pointer to end of work RAM
                                  ; it will wrap down to FFFFFF.
                                  ; TODO: sp is confusing

    ; TMSS (TraceMark Security System)
    move.b  $A10001,d0		; Get hardware version.
	andi.b  #$F,d0			    ; Compare.
	beq.s   skip_tmss		    ; If the console has no TMSS, skip the security stuff.
	move.l  #'SEGA',$A14000 	; Make the TMSS happy.

    ; Initialize gamepads
    ; init_gampads ; TODO: This does not seem to work.

skip_tmss:

    ; =================================================================
    ; STEP 1: CONFIGURE VDP REGISTERS (Video Display Processor)
    ; =================================================================
    ; VDP Control Port: $C00004 (write registers by ORing register# with $8000)
    ; https://segaretro.org/Sega_Mega_Drive/VDP_general_usage
    ; https://segaretro.org/Sega_Mega_Drive/VDP_registers
    ; https://wiki.megadrive.org/index.php?title=VDP_Registers
    ; -----------------------------------------------------------------

    ; Mode Register 1
    ;                       +------- #5: 0 - left 8 pix not blanked (i.e. normal)
    ;                       |            1 - leftmost 8 pix are blanked to bg col
    ;                       |   +--- #1: 0 - enable H/V counter
    ;                       |   |        1 - freeze H/V counter on lvl 2 interrupt
    ;                       |   |
    set_vdp_register $00, 00000101b      ; bits 7, 6 & 3 are always 0
    ;                        | | |
    ;                        | | +-- #0: 0 - enable display
    ;                        | |         1 - disable display
    ;                        | +---- #2: 0 - some master system stuff
    ;                        |           1 - normal operation
    ;                        +------ #4: 0 - disable h-blank interrupts
    ;                                    1 - enable h-blank interrupts

    ; Mode Register 2
    ;                     +--------- #7: 0 - 64kB of VRAM
    ;                     |              1 - 128kB of VRAM
    ;                     | +------- #5: 0 - disable v-blank interrupts
    ;                     | |            1 - enable v-blank interrupts
    ;                     | | +----- #3: 0 - 224 pixel (28 cell) NTSC mode
    ;                     | | |          1 - 240 pixel (30 cell) PAL mode
    ;                     | | |
    set_vdp_register $01, 00000100b      ; bits 1, 0 are always 0
    ;                      | | |
    ;                      | | +---- #2: 0 - Master System (mode 4) display
    ;                      | |           1 - Mega Drive (mode 5) display
    ;                      | +------ #4: 0 - disable DMA
    ;                      |             1 - enable DMA
    ;                      +-------- #6: 0 - disable display
    ;                                    1 - enable display

    ; Plane A Name Table Location
    ; Place it as $2000
    ;                       +------- #5: 0 - + 0 to address
    ;                       |            1 - + $8000 (32768) to address
    ;                       | +----- #3: 0 - + 0 to address
    ;                       | |          1 - + $2000 (8192) to address
    ;                       | |
    set_vdp_register $02, 00001000b      ; bits 7, 2, 1 & 0 are always 0
    ;                      | |
    ;                      | +------ #4: 0 - + 0 to address
    ;                      |             1 - + $4000 (16384) to address
    ;                      +-------- #6: Used for 128kB VRAM.

    ; Window Name Table Location
    ; Place it at $4000
    ;                       +------- #5: 0 - + 0 to address
    ;                       |            1 - + $8000 (32768) to address
    ;                       | +----- #3: 0 - + 0 to address
    ;                       | |          1 - + $2000 (8192) to address
    ;                       | | +--- #1: 0 - + 0 to address
    ;                       | | |        1 - + $800 (2048) to address
    ;                       | | |        note: #1 is ignored in 320 wide mode
    ;                       | | |
    set_vdp_register $03, 00010000b      ; bits 7 & 0 are always 0
    ;                      | | |
    ;                      | | +---- #2: 0 - + 0 to address
    ;                      | |           1 - + $1000 (4096) to address
    ;                      | +------ #4: 0 - + 0 to address
    ;                      |             1 - + $4000 (16384) to address
    ;                      +-------- #6: Used for 128kB VRAM.

    ; Plane B Name Table Location
    ; Place it at $6000
    ;                          +---- #2: 0 - + 0 to address
    ;                          |         1 - + $8000 (32768) to address
    ;                          | +-- #0: 0 - + 0 to address
    ;                          | |       1 - + $2000 (8192) to address
    ;                          | |
    set_vdp_register $04, 00000011b      ; bits 7, 6, 5 & 4 are always 0
    ;                         | |
    ;                         | +--- #1: 0 - + 0 to address
    ;                         |          1 - + $4000 (16384) to address
    ;                         +----- #3: Used for 128kB VRAM.

    ; Sprite Table Location
    ; Place it at $8000
    ;                     +--------- #7: Used for 128kB VRAM.
    ;                     |           
    ;                     | +------- #5: 0 - + 0 to address
    ;                     | |            1 - + $4000 (16384) to address
    ;                     | | +----- #3: 0 - + 0 to address
    ;                     | | |          1 - + $1000 (4096) to address
    ;                     | | | +--- #1: 0 - + 0 to address
    ;                     | | | |        1 - + $400 (1024) to address
    ;                     | | | |
    set_vdp_register $05, 01000000b
    ;                      | | | |
    ;                      | | | +-- #0: 0 - + 0 to address
    ;                      | | |         1 - + $200 (512) to address
    ;                      | | |         Note: #0 is ignored in 320 wide mode
    ;                      | | +---- #2: 0 - + 0 to address
    ;                      | |           1 - + $800 (2048) to address
    ;                      | +------ #4: 0 - + 0 to address
    ;                      |             1 - + $2000 (8192) to address
    ;                      +-------- #6: 0 - + 0 to address
    ;                                    1 - + $8000 (32768) to address

    ; Bit 16 of sprite table address. Only used with 128kB VRAM.
    set_vdp_register $06, 00000000b

    ; TODO: 7

    ; Master System horizontal scroll register 
    set_vdp_register $08, 00000000b

    ; Master System vertical scroll register  
    set_vdp_register $09, 00000000b

    ; Horizontal Interrupt Counter
    set_vdp_register $0A, 00000000b ; interrupt every 1 scanline(s).

    ; Mode Register 3
    ;                         +----- #3: 0 - disable external interrupts
    ;                         |          1 - enable external interrupts
    ;                         | +--#1-0: 00 - horizontal scroll mode full screen
    ;                         | |        01 - invalid
    ;                         | |        10 - horizontal scroll mode 8px
    ;                         | |        11 - horizontal scroll mode 1px
    ;                         | |
    set_vdp_register $0B, 00000000b      ; bits 7, 6, 5 & 4 are always 0
    ;                          |
    ;                          +---- #2: 0 - vertical scroll mode full screen
    ;                                    1 - vertical scroll mode 16px

    ; Mode Register 4
    ;                     +--------- #7: 0 - 256 pixel (32 cell) wide mode
    ;                     |              1 - 320 pixel (40 cell) wide mode
    ;                     | +------- #5: 0 - 
    ;                     | |            1 - replace vsync pixel clock (??)
    ;                     | | +----- #3: 0 - disable shadow / highlight
    ;                     | | |          1 - enable shadow / highlight
    ;                     | | |  +-- #0: 0 - 256 pixel (32 cell) wide mode
    ;                     | | |  |       1 - 320 pixel (40 cell) wide mode
    ;                     | | |  |
    set_vdp_register $0C, 10000001b      ; bits 7 & 0 must be the same value
    ;                      | | |
    ;                      | | +-- #2-1: 00 - no interlace
    ;                      | |           01 - interlace
    ;                      | |           10 - invalid
    ;                      | |           11 - interlace (double resolution)
    ;                      | +------ #4: 0 - disable external pixel bus
    ;                      |             1 - enable external pixel bus
    ;                      +-------- #6: 0 - ??
    ;                                    1 - ??

    ; Horizontal Scroll Data Location
    ; Only needs 2 words (4 bytes) when in full screen scroll mode.
    ; Place it at $400
    ;                       +------- #5: 0 - + 0 to address
    ;                       |            1 - + $8000 (32768) to address
    ;                       | +----- #3: 0 - + 0 to address
    ;                       | |          1 - + $2000 (8192) to address
    ;                       | | +--- #1: 0 - + 0 to address
    ;                       | | |        1 - + $800 (2048) to address
    ;                       | | |
    set_vdp_register $0D, 00000001b
    ;                      | | | |
    ;                      | | | +-- #0: 0 - + 0 to address
    ;                      | | |         1 - + $400 (1024) to address
    ;                      | | +---- #2: 0 - + 0 to address
    ;                      | |           1 - + $1000 (4096) to address
    ;                      | +------ #4: 0 - + 0 to address
    ;                      |             1 - + $4000 (16384) to address
    ;                      +-------- #6: Used for 128kB VRAM.

    ; Horizontal Scroll Data Location (this reg only has stuff for 128kB VRAM)
    set_vdp_register $0E, 00000000b     

    set_vdp_register $0F, $02 ; Reg 15: VRAM auto-increment = 2 bytes

    ; Plane Size                   height
    ;                       +----- #5-4: 00 - 256 pixels (32 cells)
    ;                       |            01 - 512 pixels (64 cells)
    ;                       |            10 - invalid
    ;                       |            11 - 1024 pixels (128 cells)
    ;                       |
    set_vdp_register $10, 00000000b      ; bits 7, 6, 3 & 2 are always 0
    ;                           |   width
    ;                           +- #1-0: 00 - 256 pixels (32 cells)
    ;                                    01 - 512 pixels (64 cells)
    ;                                    10 - invalid
    ;                                    11 - 1024 pixels (128 cells)

    ; Window Plane Horizontal Position
    set_vdp_register $11, 00000000b      ; no window
    ; Window Plane Vertical Position
    set_vdp_register $12, 00000000b      ; no window

    ; DMA Length Registers $13-$14
    set_vdp_register $13, 00000000b
    set_vdp_register $14, 00000000b

    ; DMA Source Registers $15-$17
    set_vdp_register $15, 00000000b
    set_vdp_register $16, 00000000b
    set_vdp_register $17, 00000000b

    ; =================================================================
    ; STEP 2: CLEAR VRAM (Video RAM)
    ; =================================================================
    ; VRAM Write Command: $40000000
    ; This seems to clear all VRAM...
    ; -----------------------------------------------------------------
    move.l  #$40000000, vdp_ctrl    ; Start writing at VRAM $0000
    move.w  #$3FFF, d7             ; Loop counter (32,768 words = 64KB VRAM)
.ClearVRAM:
    move.l  #$00000000, vdp_data        ; Write zero to VRAM (fill with empty tiles)
    dbra    d7,.ClearVRAM         ; Decrement and branch until done

    ; =================================================================
    ; CLEAR "NORMAL" RAM
    ; $FF0000 - $FFFFFF (64kb)
    ; =================================================================
    move.l  #$7FFF, d7             ; Loop counter (64KB / 2 = 32kb)
    movea.l  #$FF0000, a0
.ClearRAM:
    move.w  #$0000, (a0)+          ; Write zero toVRAM 
    dbra    d7,.ClearRAM         ; Decrement and branch until done

    ; =================================================================
    ; STEP 3: SET UP COLOR PALETTE (CRAM - Color RAM)
    ; =================================================================
    ; CRAM Write Command: $C0000000 | (address << 1)
    ; Color Format: 0BBB0GGG0RRR0 (3 bits per color component)
    ; VDP supports 4 palettes with 16 colors each.
    ; -----------------------------------------------------------------
    move.l  #$C0000000, vdp_ctrl    ; Start writing at CRAM $0000
    
    ; Set some colors
    set_palette_color 0, 0, 0        ; Color 0
    set_palette_color 1, 0, 0        ; Color 1
    set_palette_color 2, 0, 0        ; Color 2
    set_palette_color 3, 0, 0        ; Color 3
    set_palette_color 4, 0, 0        ; Color 4
    set_palette_color 5, 0, 0        ; Color 5
    set_palette_color 6, 0, 0        ; Color 6
    set_palette_color 7, 0, 0        ; Color 7
    set_palette_color 7, 0, 1        ; Color 8
    set_palette_color 7, 0, 2        ; Color 9
    set_palette_color 7, 0, 3        ; Color 10
    set_palette_color 7, 0, 4        ; Color 11
    set_palette_color 7, 0, 5        ; Color 12
    set_palette_color 7, 0, 6        ; Color 13
    set_palette_color 7, 0, 7        ; Color 14
    set_palette_color 7, 1, 7        ; Color 15


    ; =================================================================
    ; CREATE TILES
    ; =================================================================

    move.l  #$40000000, vdp_ctrl    ; Start writing at VRAM $0000

    ; Tile $0
    move.l #$10000000, vdp_data ; row 1
    move.l #$11000000, vdp_data ; row 2
    move.l #$11100000, vdp_data ; row 3
    move.l #$11110000, vdp_data ; row 4
    move.l #$11111000, vdp_data ; row 5
    move.l #$11111100, vdp_data ; row 6
    move.l #$11111110, vdp_data ; row 7
    move.l #$11111111, vdp_data ; row 8

    ; =================================================================
    ; STEP 4: ENABLE DISPLAY AND SET BACKGROUND
    ; =================================================================
    set_vdp_register 7, $07        ; Reg 7: Background color = palette 0, color 7

    ; Mode Register 1
    ;                       +------- #5: 0 - left 8 pix not blanked (i.e. normal)
    ;                       |            1 - leftmost 8 pix are blanked to bg col
    ;                       |   +--- #1: 0 - enable H/V counter
    ;                       |   |        1 - freeze H/V counter on lvl 2 interrupt
    ;                       |   |
    set_vdp_register $00, 00000101b      ; bits 7, 6 & 3 are always 0
    ;                        | | |
    ;                        | | +-- #0: 0 - enable display
    ;                        | |         1 - disable display
    ;                        | +---- #2: 0 - some master system stuff
    ;                        |           1 - normal operation
    ;                        +------ #4: 0 - disable h-blank interrupts
    ;                                    1 - enable h-blank interrupts

    ; Mode Register 2
    ;                     +--------- #7: 0 - 64kB of VRAM
    ;                     |              1 - 128kB of VRAM
    ;                     | +------- #5: 0 - disable v-blank interrupts
    ;                     | |            1 - enable v-blank interrupts
    ;                     | | +----- #3: 0 - 224 pixel (28 cell) NTSC mode
    ;                     | | |          1 - 240 pixel (30 cell) PAL mode
    ;                     | | |
    set_vdp_register $01, 01100100b      ; bits 1, 0 are always 0
    ;                      | | |
    ;                      | | +---- #2: 0 - Master System (mode 4) display
    ;                      | |           1 - Mega Drive (mode 5) display
    ;                      | +------ #4: 0 - disable DMA
    ;                      |             1 - enable DMA
    ;                      +-------- #6: 0 - disable display
    ;                                    1 - enable display


    move    #$2300, sr		; Enable interrupts.

    ; =================================================================
    ; STEP 5: MAIN LOOP (Do nothing forever)
    ; =================================================================
MainLoop:
    bra.b   MainLoop              ; Infinite loop (real programs would handle VBLANK)

hblank:
    rte

vblank:
        ; Save registers we'll modify
        movem.l d1-d2,-(sp)

        gamepads_get_input

        ; if not a then skip
        tst.b gamepad1_a
        beq.b .skip

        addq.w #1, color_index
        cmpi.w #(16<<2), color_index
        blo.s .done
        move.w #0, color_index
    .done:
        move.w color_index, d1
        ; right shift d1 to get the color index
        lsr.w #2, d1
        jsr (set_bg_color).w

    ; now also scroll plane A and plane B
        set_write_vram vdp_hscroll_addr
        move.w d1, vdp_data
        move.w d1, vdp_data

    .skip:

        ; Restore registers
        movem.l (sp)+,d1-d2
        rte


; =================================================================
; ERROR HANDLERS
; =================================================================

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

; =================================================================
; VARIABLES
; RAM starts at $FF0000
; TODO: I should probably clear RAM at startup?
; TODO: Using equs at hard-coded addresses is the only methods I've
; found to declare RAM variables. It seems dumb though.
; TODO: How does alignment and data work now again? Does data need
; to always be word-aligned?
; =================================================================

word color_index

byte gamepad1_up
byte gamepad1_down
byte gamepad1_left
byte gamepad1_right
byte gamepad1_b
byte gamepad1_c
byte gamepad1_a
byte gamepad1_start

byte gamepad2_up
byte gamepad2_down
byte gamepad2_left
byte gamepad2_right
byte gamepad2_b
byte gamepad2_c
byte gamepad2_a
byte gamepad2_start