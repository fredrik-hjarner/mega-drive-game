include "../xxcalm.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; variant of emit so that one can switch between clownassembler mode and
; fasmg stand-alone mode sort of.
; _emit emits to clownassembler
; To generate binary directly, use emit
; Only handles 1 byte but that will probably suffice.
macro calminstruction?._emit? number_of_bytes, value
    local tmp
    compute tmp, value
    arrange tmp, =dc.=b= tmp
    assemble tmp
end macro
; _emit equ emit ; Uncomment to generate binary directly.

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

include "niladic.inc"
include "monoadic.inc"

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
define moveq +moveq
