create_player_sprites:
    ; Create a hard-coded sprite
        set_write_vram vram_sprites_addr
        ; vertical position
        ; 128 is the first visible row
        ; (1 shl 10 - 1) is the maximum value for a 10-bit number
        move.w #(128 + 8*22) and (1 shl 10 - 1), vdp_data.l

        ; size & next
        ; 5 means 2x2
        move.w #(5 shl 8) or 1, vdp_data.l
        ; tile number
        move.w #16, vdp_data.l
        ; horizontal position
        ; 128 is the first visible column
        ; (1 shl 9 - 1) is the maximum value for a 9-bit number
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

;; RAM VARIABLES ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Regarding positioning of tiles:
; Sprites can be placed in a 512x512 area, with the visible screen starting at
; the 128,128 position.
; One can store 512 in 9 bits. A word is 16 bits, so 7 bits are left.
; I use 2 of those as subpixels.
; So to get the pixels right-shift 2 bits, i.e. divide by 4.

; sprite positions
player1_x       rs.w
player1_y       rs.w
player2_x       rs.w
player2_y       rs.w