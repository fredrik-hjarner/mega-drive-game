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
    move.l  #$FF0000,sp           ; Set stack pointer to end of work RAM
                                  ; it will wrap down to FFFFFF.
                                  ; TODO: sp is confusing

    ; TMSS (TraceMark Security System)
    move.b  $A10001,d0		; Get hardware version.
	andi.b  #$F,d0			    ; Compare.
	beq.s   skip_tmss		    ; If the console has no TMSS, skip the security stuff.
	move.l  #'SEGA',$A14000 	; Make the TMSS happy.
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
    set_vdp_register $01, 00001100b      ; bits 1, 0 are always 0
    ;                      | | |
    ;                      | | +---- #2: 0 - Master System (mode 4) display
    ;                      | |           1 - Mega Drive (mode 5) display
    ;                      | +------ #4: 0 - disable DMA
    ;                      |             1 - enable DMA
    ;                      +-------- #6: 0 - disable display
    ;                                    1 - enable display

    ; Plane A Name Table Location
    ; Place it as $0
    ;                       +------- #5: 0 - + 0 to address
    ;                       |            1 - + $8000 (32768) to address
    ;                       | +----- #3: 0 - + 0 to address
    ;                       | |          1 - + $2000 (8192) to address
    ;                       | |
    set_vdp_register $02, 00000000b      ; bits 7, 2, 1 & 0 are always 0
    ;                      | |
    ;                      | +------ #4: 0 - + 0 to address
    ;                      |             1 - + $4000 (16384) to address
    ;                      +-------- #6: Used for 128kB VRAM.

    ; Window Name Table Location
    ; Place it at $2000
    ;                       +------- #5: 0 - + 0 to address
    ;                       |            1 - + $8000 (32768) to address
    ;                       | +----- #3: 0 - + 0 to address
    ;                       | |          1 - + $2000 (8192) to address
    ;                       | | +--- #1: 0 - + 0 to address
    ;                       | | |        1 - + $800 (2048) to address
    ;                       | | |        note: #1 is ignored in 320 wide mode
    ;                       | | |
    set_vdp_register $03, 00001000b      ; bits 7 & 0 are always 0
    ;                      | | |
    ;                      | | +---- #2: 0 - + 0 to address
    ;                      | |           1 - + $1000 (4096) to address
    ;                      | |
    ;                      | +------ #4: 0 - + 0 to address
    ;                      |             1 - + $4000 (16384) to address
    ;                      +-------- #6: Used for 128kB VRAM.

    ; Plane B Name Table Location
    ; Place it at $4000
    ;                          +---- #2: 0 - + 0 to address
    ;                          |         1 - + $8000 (32768) to address
    ;                          | +-- #0: 0 - + 0 to address
    ;                          | |       1 - + $2000 (8192) to address
    ;                          | |
    set_vdp_register $04, 00000010b      ; bits 7, 6, 5 & 4 are always 0
    ;                         | |
    ;                         | +--- #1: 0 - + 0 to address
    ;                         |          1 - + $4000 (16384) to address
    ;                         +----- #3: Used for 128kB VRAM.

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

    set_vdp_register $0F, $02 ; Reg 15: VRAM auto-increment = 2 bytes

    ; Plane Size
    ;                       +----- #5-4: 00 - 256 pixels (32 cells)
    ;                       |            01 - 512 pixels (64 cells)
    ;                       |            10 - invalid
    ;                       |            11 - 1024 pixels (128 cells)
    ;                       |
    set_vdp_register $10, 00000000b      ; bits 7, 6, 3 & 2 are always 0
    ;                           |
    ;                           +- #1-0: 00 - 256 pixels (32 cells)
    ;                                    01 - 512 pixels (64 cells)
    ;                                    10 - invalid
    ;                                    11 - 1024 pixels (128 cells)

    ; Window Plane Horizontal Position
    set_vdp_register $11, 00000000b      ; no window
    ; Window Plane Horizontal Position
    set_vdp_register $12, 00000000b      ; no window

    ; =================================================================
    ; STEP 2: CLEAR VRAM (Video RAM)
    ; =================================================================
    ; VRAM Write Command: $40000000 | (address << 1)
    ; -----------------------------------------------------------------
    move.l  #$40000000, vdp_ctrl    ; Start writing at VRAM $0000
    move.w  #$7FFF, d7             ; Loop counter (32,768 words = 64KB VRAM)
.ClearVRAM:
    move.w  #$0000, vdp_data        ; Write zero to VRAM (fill with empty tiles)
    dbra    d7,.ClearVRAM         ; Decrement and branch until done

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
    ; STEP 4: ENABLE DISPLAY AND SET BACKGROUND
    ; =================================================================
    set_vdp_register 7, $07        ; Reg 7: Background color = palette 0, color 7

    ; Mode Register 1
    ;                       +------- #5: 0 - left 8 pix not blanked (i.e. normal)
    ;                       |            1 - leftmost 8 pix are blanked to bg col
    ;                       |   +--- #1: 0 - enable H/V counter
    ;                       |   |        1 - freeze H/V counter on lvl 2 interrupt
    ;                       |   |
    set_vdp_register $00, 00010100b      ; bits 7, 6 & 3 are always 0
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
    set_vdp_register $01, 00101100b      ; bits 1, 0 are always 0
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
    bra   MainLoop              ; Infinite loop (real programs would handle VBLANK)

hblank:
    rte

vblank:
        ; Save registers we'll modify
        movem.l d1-d2,-(sp)
        add.w #1, color_index
        cmpi.w #(16<<2), color_index
        bne.s .done
        move.w #0, color_index
    .done:
        move.w color_index, d1
        ; right shift d1 to get the color index
        lsr.w #2, d1
        jsr set_bg_color
        ; Restore registers
        movem.l (sp)+,d1-d2
        rte


; =================================================================
; ERROR HANDLERS
; =================================================================

int2_bus_error:
    nop
    nop
    bra int2_bus_error

int3_address_error:
    nop
    nop
    nop
    bra int3_address_error

int4_illegal_instruction:
    nop
    nop
    nop
    nop
    bra int4_illegal_instruction

error:
    nop
    bra error

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