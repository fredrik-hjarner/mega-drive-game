;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; VDP.INC                                                                    ;;
;;                                                                            ;;
;; TODO: I want to have a word in memory for every vdp register. That the     ;;
;; code could "know" the value of them (since you can't "read" the vdp        ;;
;; registers) and I could for example toggle or set a specific bit on a vdp   ;;
;; register.                                                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; VDP REGISTERS STORED IN MEMORY ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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
calminstruction sync_vdp_register? reg_nr*
    ; The high order byte always has the highest bit set (indicating "write")
    ; it is combined with the register number.
    local   high_order_part
    compute high_order_part, 1 shl 15 or reg_nr shl 8
    asm     move.w high_order_part, d0

    ; The low order byte is the "data" and that's what we want to take from
    ; RAM.
    local   reg_ram_addr
    compute reg_ram_addr, vdp_reg_mode_1 + reg_nr
    asm     move.b (reg_ram_addr).l, d0

    ; sync it to the vdp
    asm     move.w d0, vdp_ctrl.l
end calminstruction

;; FUNCTIONS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


