;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 niladic instructions                                        ;;
;;                                                                            ;;
;; | instruction | implemented | tested | notes                             | ;;
;; |-------------|-------------|--------|-----------------------------------| ;;
;; | illegal     | yes         |        |                                   | ;;
;; | nop         | yes         |        |                                   | ;;
;; | reset       | yes         |        |                                   | ;;
;; | rte         | yes         |        |                                   | ;;
;; | rtr         | yes         |        |                                   | ;;
;; | rts         | yes         |        |                                   | ;;
;; | trapv       | yes         |        |                                   | ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

calminstruction illegal?
    local tmp
    arrange tmp, =dc.=b= =%01001010
    assemble tmp
    arrange tmp, =dc.=b= =%11111100
    assemble tmp
end calminstruction
define illegal +illegal

calminstruction nop?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110001
    assemble tmp
end calminstruction
define nop +nop

calminstruction reset?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110000
    assemble tmp
end calminstruction
define reset +reset

calminstruction rte?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110011
    assemble tmp
end calminstruction
define rte +rte

calminstruction rtr?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110111
    assemble tmp
end calminstruction
define rtr +rtr

calminstruction rts?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110101
    assemble tmp
end calminstruction
define rts +rts

calminstruction trapv?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110110
    assemble tmp
end calminstruction
define trapv +trapv
