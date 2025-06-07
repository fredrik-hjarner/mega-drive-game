;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; CREATE TILES                                                               ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

tile_ram_usage = 0 ; TODO: implement, the log to stdout in end.

set_write_vram vram_tiles_addr

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ONE-COLORED SQUARES                                                        ;;
;; Tiles 0 - 15                                                               ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; p for palette
iterate p,  0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
    repeat 8
        ; #0pppppppph
        move.l #0#p#p#p#p#p#p#p#p#h, vdp_data.l ; one row
    end repeat
end iterate

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ONE-COLORED HOLLOW SQUARES                                                 ;;
;; Tiles 16 - 30                                                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; p for palette
iterate p,  1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
    ; Pretty unreadable but this is a bordered square with transparent content.
    move.l #0#p#p#p#p#p#p#p#p#h, vdp_data.l ; row 1
    move.l #0#p#0_0_0_0_0_0#p#h, vdp_data.l ; row 2
    move.l #0#p#0_0_0_0_0_0#p#h, vdp_data.l ; row 3
    move.l #0#p#0_0_0_0_0_0#p#h, vdp_data.l ; row 4
    move.l #0#p#0_0_0_0_0_0#p#h, vdp_data.l ; row 5
    move.l #0#p#0_0_0_0_0_0#p#h, vdp_data.l ; row 6
    move.l #0#p#0_0_0_0_0_0#p#h, vdp_data.l ; row 7
    move.l #0#p#p#p#p#p#p#p#p#h, vdp_data.l ; row 8
end iterate

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ONE-COLORED SMALL SQUARES                                                  ;;
;; Tiles 31 - 45                                                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; p for palette
iterate p,  1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
    ; Pretty unreadable but 1px transparent border around solid color square.
    move.l #0_0_0_0_0_0_0_0_0#h, vdp_data.l ; row 1
    move.l #0_0#p#p#p#p#p#p#0#h, vdp_data.l ; row 2
    move.l #0_0#p#p#p#p#p#p#0#h, vdp_data.l ; row 3
    move.l #0_0#p#p#p#p#p#p#0#h, vdp_data.l ; row 4
    move.l #0_0#p#p#p#p#p#p#0#h, vdp_data.l ; row 5
    move.l #0_0#p#p#p#p#p#p#0#h, vdp_data.l ; row 6
    move.l #0_0#p#p#p#p#p#p#0#h, vdp_data.l ; row 7
    move.l #0_0_0_0_0_0_0_0_0#h, vdp_data.l ; row 8
end iterate

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ONE-COLORED TINY SQUARES                                                  ;;
;; Tiles 46 - 60                                                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; p for palette
iterate p,  1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
    ; Pretty unreadable but 3px transparent border around solid color square.
    move.l #0_0_0_0_0_0_0_0_0#h, vdp_data.l ; row 1
    move.l #0_0_0_0_0_0_0_0_0#h, vdp_data.l ; row 2
    move.l #0_0_0_0_0_0_0_0_0#h, vdp_data.l ; row 3
    move.l #0_0_0_0#p#p#0_0_0#h, vdp_data.l ; row 4
    move.l #0_0_0_0#p#p#0_0_0#h, vdp_data.l ; row 5
    move.l #0_0_0_0_0_0_0_0_0#h, vdp_data.l ; row 6
    move.l #0_0_0_0_0_0_0_0_0#h, vdp_data.l ; row 7
    move.l #0_0_0_0_0_0_0_0_0#h, vdp_data.l ; row 8
end iterate