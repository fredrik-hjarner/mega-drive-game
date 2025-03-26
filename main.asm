; =====================================================================
; Minimal Sega Genesis "Hello World" program
; Displays a solid red color on screen
; =====================================================================

    include "consts.inc"
    include "macros.inc"

; =====================================================================
; HEADER 512 bytes ($200 bytes)
; =====================================================================

    include "vectors.inc"         ; interrupt vectors
    include "meta.inc"            ; ROM metadata (console name, region, etc.)

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
                                  ; TODO: sp is confusing.

    ; =================================================================
    ; STEP 1: CONFIGURE VDP REGISTERS (Video Display Processor)
    ; =================================================================
    ; VDP Control Port: $C00004 (write registers by ORing register# with $8000)
    ; https://segaretro.org/Sega_Mega_Drive/VDP_general_usage
    ; -----------------------------------------------------------------
    set_vdp_register 0, 4        ; Reg 0: Enable H-interrupts, HV counter
    set_vdp_register 1, 4        ; Reg 1: Display OFF, V-interrupts OFF
    set_vdp_register 2, $30        ; Reg 2: Plane A at VRAM $C000 (bits 13-15)
    set_vdp_register 3, $3C        ; Reg 3: Window plane at VRAM $F000
    set_vdp_register 4, $07        ; Reg 4: Plane B at VRAM $E000
    set_vdp_register 5, $6C        ; Reg 5: Sprite table at VRAM $D800
    set_vdp_register 6, $00        ; Reg 6: Unused
    set_vdp_register 7, $00        ; Reg 7: Background color = palette 0, color 0
    set_vdp_register 8, $00        ; Reg 8: Unused (Master System stuff)
    set_vdp_register 9, $00        ; Reg 9: Unused (Master System stuff)
    set_vdp_register 10, $FF        ; Reg 10: H-interrupt timing (every 255 lines)
    set_vdp_register 11, $00        ; Reg 11: Scroll mode = full-screen
    set_vdp_register 12, $81        ; Reg 12: H40 mode (320px), no shadow/highlight
    set_vdp_register 13, $3F        ; Reg 13: Horizontal scroll table at VRAM $FC00
    set_vdp_register 14, $00        ; Reg 14: Unused
    set_vdp_register 15, $02        ; Reg 15: VRAM auto-increment = 2 bytes
    set_vdp_register 16, $01        ; Reg 16: 64x32 tilemap size
    ; Set registers 17-23 (Window, DMA related)
    set_vdp_register 17, $00
    set_vdp_register 18, $00
    set_vdp_register 19, $FF
    set_vdp_register 20, $FF
    set_vdp_register 21, $00
    set_vdp_register 22, $00
    set_vdp_register 23, $00

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
    ; -----------------------------------------------------------------
    move.l  #$C0000000, vdp_ctrl    ; Start writing at CRAM $0000
    
    ; Set all colors to black first
    set_palette_color 0, 0, 0        ; Color 0: Black
    set_palette_color 0, 0, 0        ; Color 1: Black
    set_palette_color 0, 0, 0        ; Color 2: Black
    set_palette_color 0, 0, 0        ; Color 3: Black
    set_palette_color 0, 0, 0        ; Color 4: Black
    set_palette_color 0, 0, 0        ; Color 5: Black
    set_palette_color 0, 0, 0        ; Color 6: Black
    set_palette_color 7, 0, 0        ; Color 7: Red

    ; =================================================================
    ; STEP 4: ENABLE DISPLAY AND SET BACKGROUND
    ; =================================================================
    set_vdp_register 7, $07        ; Reg 7: Background color = palette 0, color 7
    set_vdp_register 1, $44        ; Reg 1: Display ON, V-interrupts ON 

    ; =================================================================
    ; STEP 5: MAIN LOOP (Do nothing forever)
    ; =================================================================
MainLoop:
    bra   MainLoop              ; Infinite loop (real programs would handle VBLANK)