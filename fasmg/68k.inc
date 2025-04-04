;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

d0 := 000b
d1 := 001b
d2 := 010b
d3 := 011b
d4 := 100b
d5 := 101b
d6 := 110b
d7 := 111b

a0 := 000b
a1 := 001b
a2 := 010b
a3 := 011b
a4 := 100b
a5 := 101b
a6 := 110b
a7 := 111b

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

; arguments:
;     vector: 0000 - 1111
; TODO: Test.
; TODO: Give error if vector is out of range.
calminstruction trap? vector
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp

    ; second byte
    compute tmp, 01000000b + vector

    arrange tmp, =dc.=b= tmp
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

; arguments:
;     data: 0000_0000 - 1111_1111
;     dn: d0 - d7
; TODO: Test.
; TODO: Give error if data is out of range.
; TODO: Handle # character.
; TODO: Validate that dn is a data register.
calminstruction moveq? data, dn
    local tmp
    compute tmp, 01110000b + dn
    arrange tmp, =dc.=b= tmp
    assemble tmp
    compute tmp, data
    arrange tmp, =dc.=b= tmp
    assemble tmp
end calminstruction

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Make visible to the preprocessor                                           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define illegal +illegal
define trap +trap
define reset +reset
define nop +nop
define rte +rte
define rts +rts
define trapv +trapv
define rtr +rtr
define moveq +moveq
