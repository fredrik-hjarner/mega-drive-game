;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 monadicinstructions                                         ;;
;;                                                                            ;;
;; | instruction | implemented | tested | notes                             | ;;
;; |-------------|-------------|--------|-----------------------------------| ;;
;; | ext.l       | yes         | yes    |                                   | ;;
;; | ext.w       | yes         | yes    |                                   | ;;
;; | swap        | yes         | yes    |                                   | ;;
;; | trap        | yes         | yes    |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Description:
;     Sign-extend a data register.
;     .w extends from byte to word
;     .l extends from word to long
; Arguments:
;     dn: data register (d0 - d7)
; TODO: Assert that dn is a data register
;       with `relativeto` or whatever one is supposed to use.
calminstruction ext.w? dn*
    local tmp

    assert_data_reg dn

    emit 1, 01001000b
    ;            1S000000b ; S = 0-> .w, S = 1-> .l
    compute tmp, 10000000b + (dn - m68k.data_reg)
    emit 1, tmp
end calminstruction
define ext.w +ext.w

calminstruction ext.l? dn*
    local tmp

    assert_data_reg dn

    emit 1, 01001000b
    ;            1S000000b ; S = 0-> .w, S = 1-> .l
    compute tmp, 11000000b + (dn - m68k.data_reg)
    emit 1, tmp
end calminstruction
define ext.l +ext.l

; Exchange the upper and lower 16-bit words of a data register.
; arguments:
;     dn: data register (d0 - d7)
; TODO: Assert that dn is a data register
;       with `relativeto` or whatever one is supposed to use.
calminstruction swap? dn*
    local tmp

    assert_data_reg dn

    emit 1, 01001000b
    compute tmp, 01000000b + (dn - m68k.data_reg)
    emit 1, tmp
end calminstruction
define swap +swap

; Trigger any of the 16 "trap" interrupts.
; arguments:
;     vector: 0000 - 1111
calminstruction trap? vector*
    local tmp

    assert_min vector, 0
    assert_max vector, 15

    emit 1, 01001110b
    compute tmp, 01000000b + vector
    emit 1, tmp
end calminstruction
define trap +trap