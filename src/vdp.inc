;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; VDP.INC                                                                    ;;
;;                                                                            ;;
;; TODO: I want to have a word in memory for every vdp register. That the     ;;
;; code could "know" the value of them (since you can't "read" the vdp        ;;
;; registers) and I could for example toggle or set a specific bit on a vdp   ;;
;; register.                                                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; DEFAULT VALUES ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO: Maybe I should store them as words instead and bake in the command part,
;       So I could just send the command without having to construct it.
; TODO: Set _ between all bits, I can format the comments better then.
vdp_register_defaults:
    ; #00h - Mode Register 1
    ;        +------- #5: 0 - left 8 pix not blanked (i.e. normal)
    ;        |            1 - leftmost 8 pix are blanked to bg col
    ;        |   +--- #1: 0 - enable H/V counter
    ;        |   |        1 - freeze H/V counter on lvl 2 interrupt
    ;        |   |
    dc.b 0_0_000100b      ; bits 7, 6 & 3 are always 0
    ;         | | |
    ;         | | +-- #0: 0 - enable display
    ;         | |         1 - disable display
    ;         | +---- #2: 0 - some master system stuff
    ;         |           1 - normal operation
    ;         +------ #4: 0 - disable h-blank interrupts
    ;                     1 - enable h-blank interrupts

    ; #01h - Mode Register 2
    ;    +--------- #7: 0 - 64kB of VRAM
    ;    |              1 - 128kB of VRAM
    ;    | +------- #5: 0 - disable v-blank interrupts
    ;    | |            1 - enable v-blank interrupts
    ;    | | +----- #3: 0 - 224 pixel high (28 tiles) NTSC mode
    ;    | | |          1 - 240 pixel high (30 tiles) PAL mode
    ;    | | |
    dc.b 00000100b      ; bits 1, 0 are always 0
    ;     | | |
    ;     | | +---- #2: 0 - Master System (mode 4) display
    ;     | |           1 - Mega Drive (mode 5) display
    ;     | +------ #4: 0 - disable DMA
    ;     |             1 - enable DMA
    ;     +-------- #6: 0 - disable display
    ;                   1 - enable display

    ; #02h - Plane A Name Table Location
    ; Place it as $2000
    ;      +------- #5: 0 - + 0 to address
    ;      |            1 - + $8000 (32768) to address
    ;      | +----- #3: 0 - + 0 to address
    ;      | |          1 - + $2000 (8192) to address
    ;      | |
    dc.b 00001000b      ; bits 7, 2, 1 & 0 are always 0
    ;     | |
    ;     | +------ #4: 0 - + 0 to address
    ;     |             1 - + $4000 (16384) to address
    ;     +-------- #6: Used for 128kB VRAM.

    ; #03h - Window Name Table Location
    ; Place it at $0000
    ;      +------- #5: 0 - + 0 to address
    ;      |            1 - + $8000 (32768) to address
    ;      | +----- #3: 0 - + 0 to address
    ;      | |          1 - + $2000 (8192) to address
    ;      | | +--- #1: 0 - + 0 to address
    ;      | | |        1 - + $800 (2048) to address
    ;      | | |        note: #1 is ignored in 320 wide mode
    ;      | | |
    dc.b 00000000b      ; bits 7 & 0 are always 0
    ;     | | |
    ;     | | +---- #2: 0 - + 0 to address
    ;     | |           1 - + $1000 (4096) to address
    ;     | +------ #4: 0 - + 0 to address
    ;     |             1 - + $4000 (16384) to address
    ;     +-------- #6: Used for 128kB VRAM.

    ; #04h - Plane B Name Table Location
    ; Place it at $6000
    ;         +---- #2: 0 - + 0 to address
    ;         |         1 - + $8000 (32768) to address
    ;         | +-- #0: 0 - + 0 to address
    ;         | |       1 - + $2000 (8192) to address
    ;         | |
    dc.b 00000011b      ; bits 7, 6, 5 & 4 are always 0
    ;        | |
    ;        | +--- #1: 0 - + 0 to address
    ;        |          1 - + $4000 (16384) to address
    ;        +----- #3: Used for 128kB VRAM.

    ; #05h - Sprite Table Location
    ; Place it at $8000
    ;    +--------- #7: Used for 128kB VRAM.
    ;    |           
    ;    | +------- #5: 0 - + 0 to address
    ;    | |            1 - + $4000 (16384) to address
    ;    | | +----- #3: 0 - + 0 to address
    ;    | | |          1 - + $1000 (4096) to address
    ;    | | | +--- #1: 0 - + 0 to address
    ;    | | | |        1 - + $400 (1024) to address
    ;    | | | |
    dc.b 01000000b
    ;     | | | |
    ;     | | | +-- #0: 0 - + 0 to address
    ;     | | |         1 - + $200 (512) to address
    ;     | | |         Note: #0 is ignored in 320 wide mode
    ;     | | +---- #2: 0 - + 0 to address
    ;     | |           1 - + $800 (2048) to address
    ;     | +------ #4: 0 - + 0 to address
    ;     |             1 - + $2000 (8192) to address
    ;     +-------- #6: 0 - + 0 to address
    ;                   1 - + $8000 (32768) to address

    ; #06h - Bit 16 of sprite table address. Only used with 128kB VRAM.
    dc.b 00000000b

    ; TODO: #07h
    dc.b 00000000b ; No idea what the value should be...

    ; #08h - Master System horizontal scroll register 
    dc.b 00000000b

    ; #09h - Master System vertical scroll register  
    dc.b 00000000b

    ; #0Ah - Horizontal Interrupt Counter
    dc.b 00000000b ; interrupt every 1 scanline(s).

    ; #0Bh - Mode Register 3
    ;        +----- #3: 0 - disable external interrupts
    ;        |          1 - enable external interrupts
    ;        | +--#1-0: 00 - horizontal scroll mode full screen
    ;        | |        01 - invalid
    ;        | |        10 - horizontal scroll mode 8px
    ;        | |        11 - horizontal scroll mode 1px
    ;        | |
    dc.b 00000000b      ; bits 7, 6, 5 & 4 are always 0
    ;         |
    ;         +---- #2: 0 - vertical scroll mode full screen
    ;                   1 - vertical scroll mode 16px

    ; #0Ch - Mode Register 4
    ;    +--------- #7: 0 - 256 pixel (32 tiles) wide mode
    ;    |              1 - 320 pixel (40 tiles) wide mode
    ;    | +------- #5: 0 - 
    ;    | |            1 - replace vsync pixel clock (??)
    ;    | | +----- #3: 0 - disable shadow / highlight
    ;    | | |          1 - enable shadow / highlight
    ;    | | |  +-- #0: 0 - 256 pixel (32 tiles) wide mode
    ;    | | |  |       1 - 320 pixel (40 tiles) wide mode
    ;    | | |  |
    dc.b 10000001b      ; bits 7 & 0 must be the same value
    ;     | | |
    ;     | | +-- #2-1: 00 - no interlace
    ;     | |           01 - interlace
    ;     | |           10 - invalid
    ;     | |           11 - interlace (double resolution)
    ;     | +------ #4: 0 - disable external pixel bus
    ;     |             1 - enable external pixel bus
    ;     +-------- #6: 0 - ??
    ;                   1 - ??

    ; #0Dh - Horizontal Scroll Data Location
    ; Only needs 2 words (4 bytes) when in full screen scroll mode.
    ; Place it at $400
    ;      +------- #5: 0 - + 0 to address
    ;      |            1 - + $8000 (32768) to address
    ;      | +----- #3: 0 - + 0 to address
    ;      | |          1 - + $2000 (8192) to address
    ;      | | +--- #1: 0 - + 0 to address
    ;      | | |        1 - + $800 (2048) to address
    ;      | | |
    dc.b 00000001b
    ;     | | | |
    ;     | | | +-- #0: 0 - + 0 to address
    ;     | | |         1 - + $400 (1024) to address
    ;     | | +---- #2: 0 - + 0 to address
    ;     | |           1 - + $1000 (4096) to address
    ;     | +------ #4: 0 - + 0 to address
    ;     |             1 - + $4000 (16384) to address
    ;     +-------- #6: Used for 128kB VRAM.

    ; #0Eh - Horizontal Scroll Data Location (only relevant if 128kB VRAM)
    dc.b 00000000b     

    ; #0Fh
    dc.b $02 ; Reg 15: VRAM auto-increment = 2 bytes

    ; #10h - Plane Size                   height
    ;      +----- #5-4: 00 - 256 pixels (32 cells)
    ;      |            01 - 512 pixels (64 cells)
    ;      |            10 - invalid
    ;      |            11 - 1024 pixels (128 cells)
    ;      |
    dc.b 00010001b      ; bits 7, 6, 3 & 2 are always 0
    ;          |   width
    ;          +- #1-0: 00 - 256 pixels (32 cells)
    ;                   01 - 512 pixels (64 cells)
    ;                   10 - invalid
    ;                   11 - 1024 pixels (128 cells)

    ; #11h - Window Plane Horizontal Position
    dc.b 00000000b      ; no window
    ; Window Plane Vertical Position
    dc.b 00000000b      ; no window

    ; Commenting out setting these regisers because for some reason the rom
    ; stops working on real hardware when these are set......
    ; TODO: Figure out why.
    ; ; DMA Length Registers $13-$14
    ; set_vdp_register $13, 00000000b
    ; set_vdp_register $14, 00000000b
    ; ; DMA Source Registers $15-$17
    ; set_vdp_register $15, 00000000b
    ; set_vdp_register $16, 00000000b
    ; set_vdp_register $17, 00000000b

    even ; word-align is an instruction would follow.

;; VDP REGISTERS STORED IN MEMORY ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

vdp_reg_ram_addr := __rs
    vdp_reg_mode_1          rs.b ; 00h
    vdp_reg_mode_2          rs.b ; 01h
    vdp_reg_plane_a_loc     rs.b ; 02h
    vdp_reg_window_loc      rs.b ; 03h
    vdp_reg_plane_b_loc     rs.b ; 04h
    vdp_reg_sprite_loc      rs.b ; 05h
    ; vdp_reg_sprite_loc_2  rs.b ; 06h
    vdp_reg_bg_color        rs.b ; 07h
    ; 08h unused - Master System horizontal scroll register 
    ; 09h unused - Master System vertical scroll register
    vdp_reg_h_int_count     rs.b ; 0Ah
    vdp_reg_mode_3          rs.b ; 0Bh
    vdp_reg_mode_4          rs.b ; 0Ch
    vdp_reg_hscroll_loc     rs.b ; 0Dh
    ; vdp_reg_vram_128kb    rs.b ; 0Eh
    vdp_reg_auto_inc_amount rs.b ; 0Fh
    vdp_reg_plane_size      rs.b ; 10h

; TODO: Add the rest too.

;; MACROS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; sync_vdp_register
;     The purpose of this function is to sync what is in memory and push it to
;     the vdp.
; Arguments:
;     reg_nr: the number of the register to sync.
; Side-effects:
;     massacres d0
; TODO: Should I really have this as a macro and not a function??
; calminstruction sync_vdp_register? reg_nr*
;     ; The high order byte always has the highest bit set (indicating "write")
;     ; it is combined with the register number.
;     local   high_order_part
;     compute high_order_part, 1 shl 15 or reg_nr shl 8
;     asm     move.w high_order_part, d0

;     ; The low order byte is the "data" and that's what we want to take from
;     ; RAM.
;     local   reg_ram_addr
;     compute reg_ram_addr, vdp_reg_mode_1 + reg_nr
;     asm     move.b (reg_ram_addr).l, d0

;     ; sync it to the vdp
;     asm     move.w d0, vdp_ctrl.l
; end calminstruction

;; FUNCTIONS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; sync_vdp_register
;     The purpose of this function is to sync what is in memory and push it to
;     the vdp.
; Arguments:
;     d0.b: the number of the register to sync.
; Side-effects:
;     massacres d1
;     massacres a0
; TODO: Perhaps this could be a bit faster if the location of the vdp registers
;       was permanently stored in an address register.
vdp_sync_register:
    ;; construct command part ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    moveq #1000_0000b, d1    ; set highest bit (indicating "write")
    or.b d0, d1             ; add register number
    lsl.w #8, d1            ; command need to be higher order byte

    ;; construct data part ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; TODO: Test with .w. I think that should generate an error since the
    ; RAM addresses are so high up in memory that a .w will not do (except for
    ; the top 32kb or am I thinking wrong?)
    ; setup a0 so we can grab the data part.
    movea.l #vdp_reg_ram_addr, a0
    
    ; The low order byte is the register number and that's what we need from RAM
    ext.w d0    ; input was d0.b, but we need a word, so extend it to d0.w
    ; So now we can grab the byte of data from memory and combine it into d1
    move.b (a0, d0.w), d1

    ;; sync to vdp ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    move.w d1, vdp_ctrl.l
    rts

; Init the vdp registers in normal RAM with the default values from ROM.
vdp_init:
    ; Don't sync every register because some of them I don't know good values
    ; for.
    iterate reg_nr,     $0, $1, $2, $3, $4, $5, $6, \
                        $8, $9, $A, $B, $C, $D, $E, $F, $10, $11, $12

        ; move from ROM to RAM
        move.b  vdp_register_defaults+reg_nr, vdp_reg_ram_addr+reg_nr

        ; now sync to vdp from RAM
        move.b  #reg_nr, d0
        jsr     vdp_sync_register

    end iterate
    rts