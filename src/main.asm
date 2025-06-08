include "listing.inc"

; Set address where stuff allocated with `rs` will be.
; rs will be used to place stuff in RAM and RAM start at $FF0000.
rsset $FF0000

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    include "consts.inc"
    include "macros/macros.inc"
    include "macros/checksum.inc"

; =====================================================================
; HEADER 512 bytes ($200 bytes)
; =====================================================================

    include "vectors.inc"         ; interrupt vectors
    include "meta.inc"            ; ROM metadata (console name, region, etc.)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; DATA                                                                       ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    include "planes/a.inc"
    include "planes/b.inc"
    include "waveforms/waveforms.inc"
    include "waveforms/wf1.inc"

; =====================================================================
; OTHER INCLUDES
; =====================================================================

    include "players.inc"
    include "vdp.inc"
    include "functions.inc"
    include "timers.inc"

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
    move.b  $A10001.l,d0		; Get hardware version.
	andi.b  #$F,d0			    ; Compare.
	beq.b   skip_tmss		    ; If the console has no TMSS, skip the security stuff.
	move.l  #'SEGA',$A14000.l 	; Make the TMSS happy.

    ; Initialize gamepads
    ; init_gampads ; TODO: This does not seem to work.

skip_tmss:

    ; =================================================================
    ; CLEAR "NORMAL" RAM
    ; $FF0000 - $FFFFFF (64kb)
    ; =================================================================
    move.l  #$7FFF, d7             ; Loop counter (64KB / 2 = 32kb)
    movea.l  #$FF0000, a0
.ClearRAM:
    move.w  #$0000, (a0)+          ; Write zero toVRAM 
    dbra.w    d7,.ClearRAM         ; Decrement and branch until done

    ; =================================================================
    ; INIT_VDP
    ; =================================================================

    jsr vdp_init

    ; =================================================================
    ; STEP 2: CLEAR VRAM (Video RAM)
    ; =================================================================
    ; VRAM Write Command: $40000000
    ; This seems to clear all VRAM...
    ; -----------------------------------------------------------------
    move.l  #$40000000, vdp_ctrl.l    ; Start writing at VRAM $0000
    move.w  #$3FFF, d7             ; Loop counter (32,768 words = 64KB VRAM)
.ClearVRAM:
    move.l  #$00000000, vdp_data.l        ; Write zero to VRAM (fill with empty tiles)
    dbra.w    d7,.ClearVRAM         ; Decrement and branch until done

    ; =================================================================
    ; CLEAR VSRAM (Vertical Scroll RAM)
    ; =================================================================

    ; move.l  #$40000000, vdp_ctrl.l    ; Start writing at VRAM $0000
    set_write_vsram $0
    move.w  #20-1, d7             ; Loop counter (80 bytes = 20 longs)
.ClearVSRAM:
    move.l  #$00000000, vdp_data.l        ; Write zero to VRAM (fill with empty tiles)
    dbra.w    d7,.ClearVSRAM         ; Decrement and branch until done

    ; =================================================================
    ; STEP 3: SET UP COLOR PALETTE (CRAM - Color RAM)
    ; =================================================================
    ; CRAM Write Command: $C0000000 | (address << 1)
    ; Color Format: 0BBB0GGG0RRR0 (3 bits per color component)
    ; VDP supports 4 palettes with 16 colors each.
    ; -----------------------------------------------------------------
    move.l  #$C0000000, vdp_ctrl.l    ; Start writing at CRAM $0000
    
    ; Most awesome palette you've ever seen!
    set_palette_color 0, 0, 0 ; 0  transparent (black)
    set_palette_color 7, 1, 1 ; 1  bright red
    set_palette_color 7, 7, 0 ; 2  bright yellow
    set_palette_color 1, 7, 1 ; 3  bright green
    set_palette_color 0, 6, 6 ; 4  bright teal
    set_palette_color 1, 1, 7 ; 5  bright blue
    set_palette_color 5, 0, 5 ; 6  bright purple
    set_palette_color 5, 0, 0 ; 7  dark red
    set_palette_color 3, 3, 0 ; 8  dark yellow
    set_palette_color 0, 5, 0 ; 9  dark green
    set_palette_color 0, 3, 3 ; 10 dark teal
    set_palette_color 0, 0, 5 ; 11 dark blue
    set_palette_color 3, 0, 3 ; 12 dark purple
    set_palette_color 0, 0, 0 ; 13 black
    set_palette_color 4, 4, 4 ; 14 gray
    set_palette_color 7, 7, 7 ; 15 white

    ; =================================================================
    ; CREATE TILES
    ; =================================================================

    include "tiles/tiles.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; TRYIN' SOME STUFF                                                          ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; PLANE A
        set_write_vram vram_plane_a_addr
        ; observe I need to subtract 1.
        ;     The reason is that `dbra` will loop until -1 NOT until 0.
        ; So if d1 was 0, it would still loop 1 time (and not 0 times).
        move.w  #(plane_a_end-plane_a_start)/2-1, d1
        movea.l #plane_a_start, a0
        .loop:
            move.w (a0)+, vdp_data.l
            dbra.w d1, .loop            ; Decrement d1 and loop until -1

    ; PLANE B
        set_write_vram vram_plane_b_addr
        move.w  #(plane_b_end-plane_b_start)/2-1, d1
        movea.l #plane_b_start, a0
        .loop2:
            move.w (a0)+, vdp_data.l
            dbra.w d1, .loop2            ; Decrement d1 and loop until -1

    jsr create_player_sprites

    ; =================================================================
    ; STEP 4: ENABLE DISPLAY AND SET BACKGROUND
    ; =================================================================
    set_vdp_register 7, $00        ; Reg 7: Background color = palette 0, color 0

    ; Mode Register 1
    ;                       +------- #5: 0 - left 8 pix not blanked (i.e. normal)
    ;                       |            1 - leftmost 8 pix are blanked to bg col
    ;                       |   +--- #1: 0 - enable H/V counter
    ;                       |   |        1 - freeze H/V counter on lvl 2 interrupt
    ;                       |   |
    ; set_vdp_register $00, 00000100b      ; bits 7, 6 & 3 are always 0
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


    move.w    #$2300, sr		; Enable interrupts.

;; Init RAM variables
    jsr init_ram_variables.l

    ; =================================================================
    ; STEP 5: MAIN LOOP (Do nothing forever)
    ; =================================================================
MainLoop:
        bra.b   MainLoop              ; Infinite loop

vblank:
        ; Save registers we'll modify
        movem.l d1-d2,-(sp)

        ; place inputs into variables gamepad1_up, gamepad1_down, etc.
        jsr gamepads_get_input.l

        jsr update_color.l

        ; jsr update_vscroll.l
        ; jsr update_hscroll.l ; TODO: disabled so I can try 1px hscrolling.

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; WAVEFORM STUFF                                                         ;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

        plane_rows_to_animate = 64

        move.l #wf1.data, a0
        move.b #plane_rows_to_animate, d1 ; rows_to_animate (i.e. plane_end_row - plane_start_row)
        move.w wf1.current_offset, d5 ; start row/index in waveform
        move.b #75, d6
        jsr apply_waveform.l
        ; advance offset
        addq.w #1, wf1.current_offset.l

        ; if reach end then restart waveform
        cmp.w #wf1.size-plane_rows_to_animate, wf1.current_offset.l
        bne .not_reached_end
        move.w #0, wf1.current_offset.l
    .not_reached_end:

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; END OF WAVEFORM STUFF                                                  ;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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
; TODO: How does alignment and data work now again? Does data need
; to always be word-aligned?
; =================================================================

; rs address is set to $FF0000 with rsset at the start of the file

color_index     rs.w
hscroll_amount  rs.w
vscroll_amount  rs.w

gamepad1_up     rs.b
gamepad1_down   rs.b
gamepad1_left   rs.b
gamepad1_right  rs.b
gamepad1_b      rs.b
gamepad1_c      rs.b
gamepad1_a      rs.b
gamepad1_start  rs.b

gamepad2_up     rs.b
gamepad2_down   rs.b
gamepad2_left   rs.b
gamepad2_right  rs.b
gamepad2_b      rs.b
gamepad2_c      rs.b
gamepad2_a      rs.b
gamepad2_start  rs.b

;; PAD ROM ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; fill up to even bytes.
; even bytes needed to calculate checksum.
cnop 0, 2

; pad to even 128kb
; cnop 0, 1024 * 128

end_of_rom: