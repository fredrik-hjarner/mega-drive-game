create_player_sprites:
    ; Create a hard-coded sprite
        set_write_vram vram_sprites_addr
        ; vertical position
        move.w #(128 + 8*24) and (1 shl 10 - 1), vdp_data.l
        ; flips & next
        move.w #0000_0000__0000_0001b, vdp_data.l
        ;                  tile number
        move.w #18, vdp_data.l
        ; horizontal position
        move.w #(128 + 8*19) and (1 shl 9 - 1), vdp_data.l

    ; Create another hard-coded sprite
        ; vertical position
        move.w #(128 + 8*3) and (1 shl 10 - 1), vdp_data.l
        ; flips & next
        move.w #0000_0000__0000_0000b, vdp_data.l
        ;                  tile number
        move.w #20, vdp_data.l
        ; horizontal position
        move.w #(128 + 8*19) and (1 shl 9 - 1), vdp_data.l
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