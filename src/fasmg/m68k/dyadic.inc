;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 niladic instructions                                        ;;
;;                                                                            ;;
;; | # | instruction | implemented | tested | notes                         | ;;
;; |---|-------------|-------------|--------|-------------------------------| ;;
;; |   | asl.b       |             |        |                               | ;;            |             |        |                                   | ;;
;; |   | asl.l       |             |        |                               | ;;            |             |        |                                   | ;;
;; |   | asl.w       |             |        |                               | ;;  
;; |   | moveq       | yes         | yes    |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Description:
;     Shift the contents of a memory location by number of bits specified in
;     the `rotation` operand.
; Arguments:
;     rotation:
;         - either a data register
;         - or an immediate value 000 - 111
;     dn: The data register that gets shifted: d0 - d7
; TODO:
;     Remember there is also a monadic version of this instruction!!!
calminstruction asl.b? rotation, dn
    err "asl.b is not implemented!"
end calminstruction
define asl.b +asl.b

; Description:
;     Move the literal to a data register. The literal data is an
;     eight-bit signed value (-128 to +127). The literal is sign-extended
;     to 32 bits to cover the whole of the data register.
; Arguments:
;     data: 0000_0000 - 1111_1111
;     dn: d0 - d7
; TODO: Test.
; TODO: Give error if data is out of range.
; TODO: Handle # character.
; TODO: Validate that dn is a data register.
; TODO: Figure out how to work with signed numbers so it works with
;       whatever formats you can use in normal m68k assemblers
;       I assume 1111_1111b and -1d are should both be allowed?!
calminstruction moveq? data, dn
    local tmp
    ; 0 1 2 3 4  5  6  7
    ; 0 1 1 1 dn dn dn 0
    compute tmp, 01110000b + (dn shl 1) 
    emit 1, tmp
    compute tmp, data
    emit 1, tmp
end calminstruction
define moveq +moveq