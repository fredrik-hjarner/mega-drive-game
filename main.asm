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
    ; -----------------------------------------------------------------
    move.w  #$8004, vdp_ctrl        ; Reg 0: Enable H-interrupts, HV counter
    move.w  #$8104, vdp_ctrl        ; Reg 1: Display OFF, V-interrupts OFF
    move.w  #$8230, vdp_ctrl        ; Reg 2: Plane A at VRAM $C000 (bits 13-15)
    move.w  #$833C, vdp_ctrl        ; Reg 3: Window plane at VRAM $F000
    move.w  #$8407, vdp_ctrl        ; Reg 4: Plane B at VRAM $E000
    move.w  #$856C, vdp_ctrl        ; Reg 5: Sprite table at VRAM $D800
    move.w  #$8600, vdp_ctrl        ; Reg 6: Unused
    move.w  #$8700, vdp_ctrl        ; Reg 7: Background color = palette 0, color 0
    move.w  #$8800, vdp_ctrl        ; Reg 8: Unused
    move.w  #$8900, vdp_ctrl        ; Reg 9: Unused
    move.w  #$8AFF, vdp_ctrl        ; Reg 10: H-interrupt timing (every 255 lines)
    move.w  #$8B00, vdp_ctrl        ; Reg 11: Scroll mode = full-screen
    move.w  #$8C81, vdp_ctrl        ; Reg 12: H40 mode (320px), no shadow/highlight
    move.w  #$8D3F, vdp_ctrl        ; Reg 13: Horizontal scroll table at VRAM $FC00
    move.w  #$8E00, vdp_ctrl        ; Reg 14: Unused
    move.w  #$8F02, vdp_ctrl        ; Reg 15: VRAM auto-increment = 2 bytes
    move.w  #$9001, vdp_ctrl        ; Reg 16: 64x32 tilemap size
    ; Set registers 17-23 (Window, DMA related)
    move.w #$9100, vdp_ctrl
    move.w #$9200, vdp_ctrl
    move.w #$93FF, vdp_ctrl
    move.w #$94FF, vdp_ctrl
    move.w #$9500, vdp_ctrl
    move.w #$9600, vdp_ctrl
    move.w #$9700, vdp_ctrl

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
    set_palette_color 7, 0, 0

    ; =================================================================
    ; STEP 4: ENABLE DISPLAY AND SET BACKGROUND
    ; =================================================================
    move.w  #$8707, vdp_ctrl        ; Reg 7: Background color = palette 0, color 7
    move.w  #$8144, vdp_ctrl        ; Reg 1: Display ON, V-interrupts ON

    ; =================================================================
    ; STEP 5: MAIN LOOP (Do nothing forever)
    ; =================================================================
MainLoop:
    bra   MainLoop              ; Infinite loop (real programs would handle VBLANK)