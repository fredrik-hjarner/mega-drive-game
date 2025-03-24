; =====================================================================
; Minimal Sega Genesis "Hello World" program
; Displays a solid blue color on screen
; =====================================================================

; =====================================================================
; ROM HEADER - Exception Vectors (Required for hardware initialization)
; =====================================================================
    dc.l   $00000000              ; Initial stack pointer (set to zero = use default)
    dc.l   $00000200              ; Start of program execution (code begins at $200)
    dc.l   $00000008              ; Bus error handler
    dc.l   $0000000A              ; Address error handler
    dc.l   $0000000C              ; Illegal instruction handler
    dc.l   $0000000E              ; Division by zero handler
    dc.l   $00000010              ; CHK instruction handler
    dc.l   $00000012              ; TRAPV instruction handler
    dc.l   $00000014              ; Privilege violation handler
    dc.l   $00000016              ; TRACE exception handler
    dc.l   $00000018              ; Line-A emulator
    dc.l   $0000001A              ; Line-F emulator
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $00000018              ; Spurious exception
    dc.l   $0000001C              ; IRQ level 1
    dc.l   $0000001C              ; IRQ level 2
    dc.l   $0000001C              ; IRQ level 3
    dc.l   $0000001C              ; IRQ level 4
    dc.l   $0000001C              ; IRQ level 5
    dc.l   $0000001C              ; IRQ level 6
    dc.l   $0000001C              ; IRQ level 7
    dc.l   $0000001C              ; TRAP #00 exception
    dc.l   $0000001C              ; TRAP #01 exception
    dc.l   $0000001C              ; TRAP #02 exception
    dc.l   $0000001C              ; TRAP #03 exception
    dc.l   $0000001C              ; TRAP #04 exception
    dc.l   $0000001C              ; TRAP #05 exception
    dc.l   $0000001C              ; TRAP #06 exception
    dc.l   $0000001C              ; TRAP #07 exception
    dc.l   $0000001C              ; TRAP #08 exception
    dc.l   $0000001C              ; TRAP #09 exception
    dc.l   $0000001C              ; TRAP #10 exception
    dc.l   $0000001C              ; TRAP #11 exception
    dc.l   $0000001C              ; TRAP #12 exception
    dc.l   $0000001C              ; TRAP #13 exception
    dc.l   $0000001C              ; TRAP #14 exception
    dc.l   $0000001C              ; TRAP #15 exception
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)
    dc.l   $0000001C              ; (reserved)

    include "header.inc"          ; Sega ROM metadata (console name, region, etc.)

; =====================================================================
; PROGRAM START (Code begins at $200 as specified in second vector)
; =====================================================================
    org     $00000200             ; Assemble code starting at $200

Start:
    ; -----------------------------------------------------------------
    ; INITIALIZE SYSTEM
    ; -----------------------------------------------------------------
    move.w  #$2700,sr             ; Disable interrupts (status register)
    move.l  #$00FF0000,a7         ; Set stack pointer to end of work RAM

    ; =================================================================
    ; STEP 1: CONFIGURE VDP REGISTERS (Video Display Processor)
    ; =================================================================
    ; VDP Control Port: $C00004 (write registers by ORing register# with $8000)
    ; -----------------------------------------------------------------
    move.w  #$8004,$C00004        ; Reg 0: Enable H-interrupts, HV counter
    move.w  #$8104,$C00004        ; Reg 1: Display OFF, V-interrupts OFF
    move.w  #$8230,$C00004        ; Reg 2: Plane A at VRAM $C000 (bits 13-15)
    move.w  #$833C,$C00004        ; Reg 3: Window plane at VRAM $F000
    move.w  #$8407,$C00004        ; Reg 4: Plane B at VRAM $E000
    move.w  #$856C,$C00004        ; Reg 5: Sprite table at VRAM $D800
    move.w  #$8600,$C00004        ; Reg 6: Unused
    move.w  #$8700,$C00004        ; Reg 7: Background color = palette 0, color 0
    move.w  #$8800,$C00004        ; Reg 8: Unused
    move.w  #$8900,$C00004        ; Reg 9: Unused
    move.w  #$8AFF,$C00004        ; Reg 10: H-interrupt timing (every 255 lines)
    move.w  #$8B00,$C00004        ; Reg 11: Scroll mode = full-screen
    move.w  #$8C81,$C00004        ; Reg 12: H40 mode (320px), no shadow/highlight
    move.w  #$8D3F,$C00004        ; Reg 13: Horizontal scroll table at VRAM $FC00
    move.w  #$8E00,$C00004        ; Reg 14: Unused
    move.w  #$8F02,$C00004        ; Reg 15: VRAM auto-increment = 2 bytes
    move.w  #$9001,$C00004        ; Reg 16: 64x32 tilemap size
    ; Set registers 17-23 (Window, DMA related)
    move.w #$9100,$C00004
    move.w #$9200,$C00004
    move.w #$93FF,$C00004
    move.w #$94FF,$C00004
    move.w #$9500,$C00004
    move.w #$9600,$C00004
    move.w #$9700,$C00004

    ; =================================================================
    ; STEP 2: CLEAR VRAM (Video RAM)
    ; =================================================================
    ; VRAM Write Command: $40000000 | (address << 1)
    ; -----------------------------------------------------------------
    move.l  #$40000000,$C00004    ; Start writing at VRAM $0000
    move.w  #$7FFF,d7             ; Loop counter (32,768 words = 64KB VRAM)
.ClearVRAM:
    move.w  #$0000,$C00000        ; Write zero to VRAM (fill with empty tiles)
    dbra    d7,.ClearVRAM         ; Decrement and branch until done

    ; =================================================================
    ; STEP 3: SET UP COLOR PALETTE (CRAM - Color RAM)
    ; =================================================================
    ; CRAM Write Command: $C0000000 | (address << 1)
    ; Color Format: 0BBB0GGG0RRR0 (3 bits per color component)
    ; -----------------------------------------------------------------
    move.l  #$C0000000,$C00004    ; Start writing at CRAM $0000
    
    ; Set all colors to black first
    move.w  #$0000,$C00000        ; Color 0: Black
    move.w  #$0000,$C00000        ; Color 1: Black
    move.w  #$0000,$C00000        ; Color 2: Black
    move.w  #$0000,$C00000        ; Color 3: Black
    move.w  #$0000,$C00000        ; Color 4: Black
    move.w  #$0000,$C00000        ; Color 5: Black
    move.w  #$0000,$C00000        ; Color 6: Black
    ;        bbb-ggg-rrr-
    move.w #%000000001110,$C00000    ; Color 7: Red

    ; =================================================================
    ; STEP 4: ENABLE DISPLAY AND SET BACKGROUND
    ; =================================================================
    move.w  #$8707,$C00004        ; Reg 7: Background color = palette 0, color 7
    move.w  #$8144,$C00004        ; Reg 1: Display ON, V-interrupts ON

    ; =================================================================
    ; STEP 5: MAIN LOOP (Do nothing forever)
    ; =================================================================
MainLoop:
    bra   MainLoop              ; Infinite loop (real programs would handle VBLANK)