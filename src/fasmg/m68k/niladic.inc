;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 niladic instructions                                        ;;
;;                                                                            ;;
;; | # | instruction | implemented | tested | notes                         | ;;
;; |---|-------------|-------------|--------|-------------------------------| ;;
;; | 1 | illegal     | yes         |        |                               | ;;
;; | 2 | nop         | yes         |        |                               | ;;
;; | 3 | reset       | yes         |        |                               | ;;
;; | 4 | rte         | yes         |        |                               | ;;
;; | 5 | rtr         | yes         |        |                               | ;;
;; | 6 | rts         | yes         |        |                               | ;;
;; | 7 | trapv       | yes         |        |                               | ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Illegal instruction (forces illegal instruction exception)
calminstruction illegal?
    local tmp
    arrange tmp, =dc.=b= =%01001010
    assemble tmp
    arrange tmp, =dc.=b= =%11111100
    assemble tmp
end calminstruction
define illegal +illegal

; No operation.
calminstruction nop?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110001
    assemble tmp
end calminstruction
define nop +nop

; Reset external devices (??)
calminstruction reset?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110000
    assemble tmp
end calminstruction
define reset +reset

; Return from Exception
calminstruction rte?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110011
    assemble tmp
end calminstruction
define rte +rte

; Return and Restore condition codes
calminstruction rtr?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110111
    assemble tmp
end calminstruction
define rtr +rtr

; Return from Subroutine
calminstruction rts?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110101
    assemble tmp
end calminstruction
define rts +rts

; Trap on overflow
calminstruction trapv?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110110
    assemble tmp
end calminstruction
define trapv +trapv
