; Minimal Sega Genesis "Hello World" program
; Just displays a solid blue color on screen

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
    move.w #$2700,sr           ; Disable interrupts
    move.l  #$00FF0000,a7       ; Set up stack pointer

    ; Initialize VDP (Video Display Processor)
    lea     VdpData,a5          ; Load address of VDP initialization data
    move.l  #$C0000000,$C00004  ; Set VDP write register command
    moveq   #24-1,d7            ; 24 registers to write

.vdpInitLoop:
    move.b  (a5)+,d0            ; Get VDP register value
    move.w  d0,$C00004          ; Write to VDP register
    add.w   #$0100,$C00004      ; Next register
    dbra    d7,.vdpInitLoop     ; Loop until all registers initialized

    ; Clear VRAM (Video RAM)
    move.l  #$40000000,$C00004  ; Set VRAM write address to 0
    move.w  #$0000,d0           ; Clear value
    move.w  #$7FFF,d7           ; 32KB of VRAM to clear

.clearVramLoop:
    move.w  d0,$C00000          ; Write clear value to VRAM
    dbra    d7,.clearVramLoop   ; Loop until all VRAM cleared

    ; Set background color to blue
    move.l  #$C0000000,$C00004  ; Set VDP register 0
    move.w  #$8007,$C00004      ; Set VDP register 7 (background color) to blue (7)

    ; Enable display
    move.w  #$8144,$C00004      ; Set VDP register 1 (enable display)

MainLoop:
    bra     MainLoop             ; Loop forever

; VDP initialization values for registers 0-23
VdpData:
    dc.b $04                     ; Reg 0: Disabled HInt, read 8-color mode
    dc.b $44                     ; Reg 1: Disabled display, enabled DMA, disabled VInt
    dc.b $00                     ; Reg 2: Pattern table for Scroll A at VRAM $0000
    dc.b $00                     ; Reg 3: Pattern table for Window at VRAM $0000
    dc.b $00                     ; Reg 4: Pattern table for Scroll B at VRAM $0000
    dc.b $00                     ; Reg 5: Sprite table at VRAM $0000
    dc.b $00                     ; Reg 6: Unused
    dc.b $00                     ; Reg 7: Background color - palette 0, color 0
    dc.b $00                     ; Reg 8: Unused
    dc.b $00                     ; Reg 9: Unused
    dc.b $FF                     ; Reg 10: HInt counter
    dc.b $00                     ; Reg 11: Full-screen scroll
    dc.b $81                     ; Reg 12: No interlace, 40 cell display
    dc.b $00                     ; Reg 13: Horizontal scroll table at VRAM $0000
    dc.b $00                     ; Reg 14: Unused
    dc.b $02                     ; Reg 15: Autoincrement 2
    dc.b $00                     ; Reg 16: Scroll size, 32x32 cell
    dc.b $00                     ; Reg 17: Window horizontal position
    dc.b $00                     ; Reg 18: Window vertical position
    dc.b $FF                     ; Reg 19: DMA length counter
    dc.b $FF                     ; Reg 20: DMA length counter
    dc.b $00                     ; Reg 21: DMA source address
    dc.b $00                     ; Reg 22: DMA source address
    dc.b $00                     ; Reg 23: DMA source address



