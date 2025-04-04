;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 68000 instruction set implemented in fasmg                                 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

calminstruction illegal?
    local tmp
    arrange tmp, =dc.=b= =%01001010
    assemble tmp
    arrange tmp, =dc.=b= =%11111100
    assemble tmp
end calminstruction

calminstruction reset?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110000
    assemble tmp
end calminstruction

calminstruction nop?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110001
    assemble tmp
end calminstruction

calminstruction rte?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110011
    assemble tmp
end calminstruction

calminstruction rts?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110101
    assemble tmp
end calminstruction

calminstruction trapv?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110110
    assemble tmp
end calminstruction

calminstruction rtr?
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp
    arrange tmp, =dc.=b= =%01110111
    assemble tmp
end calminstruction

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Make visible to the preprocessor                                           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define illegal +illegal
define reset +reset
define nop +nop
define rte +rte
define rts +rts
define trapv +trapv
define rtr +rtr
