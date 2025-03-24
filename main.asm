; Minimal Sega Genesis "Hello World" program
; Displays a solid blue color on screen

; ROM Header - Required for the Genesis to recognize the ROM
    dc.l   $00000000              ; Initial stack pointer value
    dc.l   $00000200              ; Start of program
    dc.l   $00000008              ; Bus error
    dc.l   $0000000A              ; Address error
    dc.l   $0000000C              ; Illegal instruction
    dc.l   $0000000E              ; Division by zero
    dc.l   $00000010              ; CHK instruction
    dc.l   $00000012              ; TRAPV instruction
    dc.l   $00000014              ; Privilege violation
    dc.l   $00000016              ; TRACE exception
    dc.l   $00000018              ; Line-A emulator
    dc.l   $0000001A              ; Line-F emulator
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
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
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)
    dc.l   $0000001C              ; Unused (reserved)

    dc.b "SEGA GENESIS    "      ; Console name
    dc.b "(C)SEGA 2025.MAR"      ; Copyright/date
    dc.b "HELLO WORLD DEMO                                 " ; Domestic name
    dc.b "HELLO WORLD DEMO                                 " ; International name
    dc.b "GM XXXXXXXX-XX"        ; Version number
    dc.w $0000                   ; Checksum
    dc.b "J               "      ; I/O support
    dc.l $00000000               ; ROM start address
    dc.l $00100000               ; ROM end address
    dc.l $00FF0000               ; Start of RAM
    dc.l $00FFFFFF               ; End of RAM
    dc.l $00000000               ; SRAM enabled
    dc.l $00000000               ; Unused
    dc.l $00000000               ; Unused
    dc.l $00000000               ; Unused
    dc.b "                                        "         ; Notes
    dc.b "JUE             "      ; Country codes

; Program start at $00000200
    org     $00000200

Start:
    ; Initialize the system
    move.w #$2700,sr             ; Disable interrupts
    move.l #$00FF0000,a7         ; Set up stack pointer

    ; --------------------------------------------------
    ; STEP 1: Set up VDP registers in a simplified way
    ; --------------------------------------------------
    
    ; Set register 0: Normal operation
    move.w #$8004,$C00004
    
    ; Set register 1: Display disabled initially
    move.w #$8104,$C00004
    
    ; Set registers 2-6 (mapping in VRAM)
    move.w #$8230,$C00004
    move.w #$833C,$C00004
    move.w #$8407,$C00004
    move.w #$856C,$C00004
    move.w #$8600,$C00004
    
    ; Set register 7: Background color = palette 0, color 0 initially
    move.w #$8700,$C00004
    
    ; Set registers 8-9 (unused)
    move.w #$8800,$C00004
    move.w #$8900,$C00004
    
    ; Set register 10: H-Int counter
    move.w #$8AFF,$C00004
    
    ; Set register 11: Scroll mode
    move.w #$8B00,$C00004
    
    ; Set register 12: No interlace, 40 cell display
    move.w #$8C81,$C00004
    
    ; Set register 13: Horizontal scroll table
    move.w #$8D3F,$C00004
    
    ; Set register 14 (unused)
    move.w #$8E00,$C00004
    
    ; Set register 15: Autoincrement by 2
    move.w #$8F02,$C00004
    
    ; Set register 16: Scroll size - 64x32 cell
    move.w #$9001,$C00004
    
    ; Set registers 17-23 (Window, DMA related)
    move.w #$9100,$C00004
    move.w #$9200,$C00004
    move.w #$93FF,$C00004
    move.w #$94FF,$C00004
    move.w #$9500,$C00004
    move.w #$9600,$C00004
    move.w #$9700,$C00004
    
    ; --------------------------------------------------
    ; STEP 2: Clear VRAM
    ; --------------------------------------------------
    
    ; Set up VRAM write at address 0
    ; VRAM Write command format: $40000000 + (address << 1)
    move.l #$40000000,$C00004
    
    ; Clear all 32KB of VRAM
    move.w #$7FFF,d7
.clearVRAM:
    move.w #$0000,$C00000
    dbra d7,.clearVRAM
    
    ; --------------------------------------------------
    ; STEP 3: Set up color palette (CRAM)
    ; --------------------------------------------------
    
    ; Set up CRAM write at address 0
    ; CRAM Write command format: $C0000000 + (address << 1)
    move.l #$C0000000,$C00004
    
    ; Write colors for palette 0
    move.w #$0000,$C00000    ; Color 0: Black
    move.w #$0000,$C00000    ; Color 1: Black
    move.w #$0000,$C00000    ; Color 2: Black
    move.w #$0000,$C00000    ; Color 3: Black
    move.w #$0000,$C00000    ; Color 4: Black
    move.w #$0000,$C00000    ; Color 5: Black
    move.w #$0000,$C00000    ; Color 6: Black
    move.w #$000F,$C00000    ; Color 7: Blue (00 00 0F = 0000 0000 0000 1111)
    
    ; --------------------------------------------------
    ; STEP 4: Set background color and enable display
    ; --------------------------------------------------
    
    ; Set register 7 to use palette 0, color 7 as background
    move.w #$8707,$C00004
    
    ; Enable display (register 1 = $44: display enabled)
    move.w #$8144,$C00004
    
    ; --------------------------------------------------
    ; STEP 5: Main loop
    ; --------------------------------------------------
    
MainLoop:
    bra MainLoop