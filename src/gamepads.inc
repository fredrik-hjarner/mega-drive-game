; https://plutiedev.com/controllers
; TODO: Store in a word instead and use bit masks.
gamepads_get_input:
    iterate n,  1,2
            move.b #$40, gamepad#n#_ctrl.l

            ; TODO: Wouldn't movea work here as well??
            ; Why or why not??
            lea.l  gamepad#n#_data.l, a0
            
            ; set bit 6 (TH) to 1 to get first group of buttons
            move.b  #$40, (a0)  ; Do 1st step
            nop                 ; D-pad, B and C
            nop
            move.b  (a0), d0
            ; not.b d0 ; invert so pressed = 1 instead of 0
            ; d0 will now contain
            ; Bit5 	Bit4 	Bit3 	Bit2 	Bit1 	Bit0
            ; C 	B 	    Right 	Left 	Down 	Up
        ; Up
            btst.l #0, d0
            seq.b gamepad#n#_up.l
        ; Down
            btst.l #1, d0
            seq.b gamepad#n#_down.l
        ; Left
            btst.l #2, d0
            seq.b gamepad#n#_left.l
        ; Right
            btst.l #3, d0
            seq.b gamepad#n#_right.l
        ; B
            btst.l #4, d0
            seq.b gamepad#n#_b.l
        ; C
            btst.l #5, d0
            seq.b gamepad#n#_c.l
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        ;; 2nd set of buttons                                                 ;;
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            move.b  #$00, (a0)
            nop
            nop
            move.b  (a0), d0
            ; not.b d0 ; invert so pressed = 1 instead of 0
            ; d0 will now contain
            ; Bit5   Bit4
            ; Start  A
        ; A
            btst.l #4, d0
            seq.b gamepad#n#_a.l
        ; Start
            btst.l #5, d0
            seq.b gamepad#n#_start.l
    end iterate
    rts

;; RAM VARIABLES ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

gamepad1_up     rs.b
gamepad1_down   rs.b
gamepad1_left   rs.b
gamepad1_right  rs.b
gamepad1_b      rs.b
gamepad1_c      rs.b
gamepad1_a      rs.b
gamepad1_start  rs.b

gamepad2_up     rs.b
gamepad2_down   rs.b
gamepad2_left   rs.b
gamepad2_right  rs.b
gamepad2_b      rs.b
gamepad2_c      rs.b
gamepad2_a      rs.b
gamepad2_start  rs.b