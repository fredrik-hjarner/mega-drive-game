;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; CREATE TILES                                                               ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

tile_ram_usage = 0 ; TODO: implement, the log to stdout in end.

set_write_vram vram_tiles_addr

; override `move.l?` to increment `tile_ram_usage`.
macro move.l? line&
    move.l line
    tile_ram_usage = tile_ram_usage + 4
end macro

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
;; PLAYERS - 2x2 SQUARE OUTLINE                                               ;;
;; Tiles ?? - ??                                                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; p for palette
iterate p,  1,2,3,4,5,6,7,8,9,A,B,C
    move.l #0#p#p#p#p#p#p#p#p#h, vdp_data.l
    move.l #0#p#p#p#p#p#p#p#p#h, vdp_data.l
    move.l #0#p#p#0_0_0_0_0_0#h, vdp_data.l
    move.l #0#p#p#0_0_0_0_0_0#h, vdp_data.l
    move.l #0#p#p#0_0_0_0_0_0#h, vdp_data.l
    move.l #0#p#p#0_0_0_0_0_0#h, vdp_data.l
    move.l #0#p#p#0_0_0_0_0_0#h, vdp_data.l
    move.l #0#p#p#0_0_0_0_0_0#h, vdp_data.l

    move.l #0#p#p#0_0_0_0_0_0#h, vdp_data.l
    move.l #0#p#p#0_0_0_0_0_0#h, vdp_data.l
    move.l #0#p#p#0_0_0_0_0_0#h, vdp_data.l
    move.l #0#p#p#0_0_0_0_0_0#h, vdp_data.l
    move.l #0#p#p#0_0_0_0_0_0#h, vdp_data.l
    move.l #0#p#p#0_0_0_0_0_0#h, vdp_data.l
    move.l #0#p#p#p#p#p#p#p#p#h, vdp_data.l
    move.l #0#p#p#p#p#p#p#p#p#h, vdp_data.l

    move.l #0#p#p#p#p#p#p#p#p#h, vdp_data.l
    move.l #0#p#p#p#p#p#p#p#p#h, vdp_data.l
    move.l #0_0_0_0_0_0_0#p#p#h, vdp_data.l
    move.l #0_0_0_0_0_0_0#p#p#h, vdp_data.l
    move.l #0_0_0_0_0_0_0#p#p#h, vdp_data.l
    move.l #0_0_0_0_0_0_0#p#p#h, vdp_data.l
    move.l #0_0_0_0_0_0_0#p#p#h, vdp_data.l
    move.l #0_0_0_0_0_0_0#p#p#h, vdp_data.l

    move.l #0_0_0_0_0_0_0#p#p#h, vdp_data.l
    move.l #0_0_0_0_0_0_0#p#p#h, vdp_data.l
    move.l #0_0_0_0_0_0_0#p#p#h, vdp_data.l
    move.l #0_0_0_0_0_0_0#p#p#h, vdp_data.l
    move.l #0_0_0_0_0_0_0#p#p#h, vdp_data.l
    move.l #0_0_0_0_0_0_0#p#p#h, vdp_data.l
    move.l #0#p#p#p#p#p#p#p#p#h, vdp_data.l
    move.l #0#p#p#p#p#p#p#p#p#h, vdp_data.l
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

; restore `move.l?`
; Observe `?` is needed!
purge move.l?

repeat 1, i:tile_ram_usage
    display "Tiles use ", `i, " bytes of RAM.", 10
end repeat