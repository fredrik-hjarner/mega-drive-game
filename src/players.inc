create_player_sprites:
    ; Create a hard-coded sprite
        set_write_vram vram_sprites_addr
        ; vertical position
        ; 128 is the first visible row
        ; (1 shl 10 - 1) is the maximum value for a 10-bit number
        ; TODO: This should use `player_y` and not be hard-coded!!!
        move.w #(128 + 8*22) and (1 shl 10 - 1), vdp_data.l

        ; size & next
        ; 5 means 2x2
        move.w #(5 shl 8) or 1, vdp_data.l
        ; tile number
        move.w #16, vdp_data.l
        ; horizontal position
        ; 128 is the first visible column
        ; (1 shl 9 - 1) is the maximum value for a 9-bit number
        ; TODO: This should use `player_x` and not be hard-coded!!!
        move.w #(128 + 8*18) and (1 shl 9 - 1), vdp_data.l

    ; Create another hard-coded sprite
        ; vertical position
        move.w #(128 + 8*2) and (1 shl 10 - 1), vdp_data.l

        ; flips & next
        ; 5 means 2x2
        move.w #(5 shl 8) or 0, vdp_data.l
        ; tile number
        move.w #28, vdp_data.l
        ; horizontal position
        move.w #(128 + 8*18) and (1 shl 9 - 1), vdp_data.l
        rts

iterate <dir,  negative,  dim>, \
        left,  1,         x, \
        right, 0,         x, \
        up,    1,         y, \
        down,  0,         y

    ; does stuff on "key up"
    p1_move_#dir:
            ; if gamepad1_previous_left = 0 and gamepad1_left = 1
            ; then move left
            ; moving left means changing some variable that holds the value of
            ; the player 1 sprite's x position

            tst.b gamepad1_previous_#dir ; test if zero
            beq.s .end ; skip if prev was not pushed

            tst.b gamepad1_#dir ; test if zero
            bne.s .end ; skip if current is pushed
        ; move left/right/up/down
            ; ok so here I want to subtract/add from/to player1_x
            if negative = 1
                subi.w #pixels_per_square, player1_#dim
            else
                addi.w #pixels_per_square, player1_#dim
            end if
            ; and then afterwards put it into vram.
            set_write_vram player1_#dim#_vram_addr
            move.w player1_#dim, vdp_data.l

        .end:
            ; update gamepad1_previous_left/right
            move.b gamepad1_#dir, gamepad1_previous_#dir

            rts

end iterate ; iterate <dir, negative>

;; CONSTANTS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; what to set vram addr to when updating position
player1_x_vram_addr := vram_sprites_addr + 6
player1_y_vram_addr := vram_sprites_addr + 0

player2_x_vram_addr := vram_sprites_addr + 8 + 6
player2_y_vram_addr := vram_sprites_addr + 8 + 0

;; RAM VARIABLES ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Regarding positioning of tiles:
; Sprites can be placed in a 512x512 area, with the visible screen starting at
; the 128,128 position.
; One can store 512 in 9 bits. A word is 16 bits, so 7 bits are left.
; I use 2 of those as subpixels.
; So to get the pixels right-shift 2 bits, i.e. divide by 4.

; sprite positions
; So, `player_x`is located in RAM but will then need to be moved into VRAM,
; because the sprite's position is in VRAM.
; TODO: Somehow I think RAM addresses should be displayed either with dbg prints
;       or in listing.
player1_x       rs.w ; $FF0004 i.e. $4 in RAM because RAM starts at $FF0000
repeat 1, i:player1_x
    display "player1_x: ", `i, 10
end repeat
player1_y       rs.w
player2_x       rs.w
player2_y       rs.w

;
gamepad1_previous_left      rs.b
gamepad1_previous_right     rs.b
gamepad1_previous_up        rs.b
gamepad1_previous_down      rs.b