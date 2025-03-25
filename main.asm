; =====================================================================
; Minimal Sega Genesis "Hello World" program
; Displays a solid red color on screen
; =====================================================================

    include "consts.inc"

; =====================================================================
; VECTORS - Exception Vectors (Required for hardware initialization)
; 64 vectors x 4 (long) = 256d bytes = $100 bytes
; https://web.archive.org/web/20240616180841/https://wiki.megadrive.org/index.php?title=68k_vector_table&t=20170119115405
; =====================================================================
    dc.l    0             ; #0 Initial Stack Address
    dc.l    Start         ; #1 Start of program Code
    dc.l    0             ; #2 Bus error
    dc.l    0             ; #3 Address error
    dc.l    0             ; #4 Illegal instruction
    dc.l    0             ; #5 Division by zero
    dc.l    0             ; #6 CHK exception
    dc.l    0             ; #7 TRAPV exception
    dc.l    0             ; #8 Privilage violation
    dc.l    0             ; #9 TRACE exception
    dc.l    0             ; #10 Line-A emulator
    dc.l    0             ; #11 Line-F emulator
    dc.l    0             ; #12 Reserved (NOT USED)
    dc.l    0             ; #13 Co-processor protocol violation
    dc.l    0             ; #14 Format error
    dc.l    0             ; #15 Uninitialized Interrupt

    ; Reserved (NOT USED)
    dc.l    0,0,0,0,0,0,0,0 ; #16-#23

    dc.l    0             ; #24 Spurious Interrupt
    dc.l    0             ; #25 IRQ Level 1
    dc.l    0             ; #26 IRQ Level 2 (EXT Interrupt)
    dc.l    0             ; #27 IRQ Level 3
    dc.l    0             ; #28 IRQ Level 4 (VDP Horizontal Interrupt)
    dc.l    0             ; #29 IRQ Level 5
    dc.l    0             ; #30 IRQ Level 6 (VDP Vertical Interrupt)
    dc.l    0             ; #31 IRQ Level 7
    dc.l    0             ; #32 TRAP #00 Exception
    dc.l    0             ; #33 TRAP #01 Exception
    dc.l    0             ; #34 TRAP #02 Exception
    dc.l    0             ; #35 TRAP #03 Exception
    dc.l    0             ; #36 TRAP #04 Exception
    dc.l    0             ; #37 TRAP #05 Exception
    dc.l    0             ; #38 TRAP #06 Exception
    dc.l    0             ; #39 TRAP #07 Exception
    dc.l    0             ; #40 TRAP #08 Exception
    dc.l    0             ; #41 TRAP #09 Exception
    dc.l    0             ; #42 TRAP #10 Exception
    dc.l    0             ; #43 TRAP #11 Exception
    dc.l    0             ; #44 TRAP #12 Exception
    dc.l    0             ; #45 TRAP #13 Exception
    dc.l    0             ; #46 TRAP #14 Exception
    dc.l    0             ; #47 TRAP #15 Exception
    dc.l    0             ; #48 (FP) Branch or Set on Unordered Condition
    dc.l    0             ; #49 (FP) Inexact Result
    dc.l    0             ; #50 (FP) Divide by Zero
    dc.l    0             ; #51 (FP) Underflow
    dc.l    0             ; #52 (FP) Operand Error
    dc.l    0             ; #53 (FP) Overflow
    dc.l    0             ; #54 (FP) Signaling NAN
    dc.l    0             ; #55 (FP) Unimplemented Data Type
    dc.l    0             ; #56 MMU Configuration Error
    dc.l    0             ; #57 MMU Illegal Operation Error
    dc.l    0             ; #58 MMU Access Violation Error
    
    ; Reserved (NOT USED)
    dc.l   0,0,0,0,0              ; #59, #60, #61, #62, #63

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
    move.l  #$40000000,vdp_ctrl    ; Start writing at VRAM $0000
    move.w  #$7FFF,d7             ; Loop counter (32,768 words = 64KB VRAM)
.ClearVRAM:
    move.w  #$0000, vdp_data        ; Write zero to VRAM (fill with empty tiles)
    dbra    d7,.ClearVRAM         ; Decrement and branch until done

    ; =================================================================
    ; STEP 3: SET UP COLOR PALETTE (CRAM - Color RAM)
    ; =================================================================
    ; CRAM Write Command: $C0000000 | (address << 1)
    ; Color Format: 0BBB0GGG0RRR0 (3 bits per color component)
    ; -----------------------------------------------------------------
    move.l  #$C0000000,vdp_ctrl    ; Start writing at CRAM $0000
    
    ; Set all colors to black first
    move.w  #$0000, vdp_data        ; Color 0: Black
    move.w  #$0000, vdp_data        ; Color 1: Black
    move.w  #$0000, vdp_data        ; Color 2: Black
    move.w  #$0000, vdp_data        ; Color 3: Black
    move.w  #$0000, vdp_data        ; Color 4: Black
    move.w  #$0000, vdp_data        ; Color 5: Black
    move.w  #$0000, vdp_data        ; Color 6: Black
    ;        bbb-ggg-rrr-
    move.w #%000000001110, vdp_data    ; Color 7: Red

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