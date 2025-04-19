;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 monadicinstructions                                         ;;
;;                                                                            ;;
;; | instruction | implemented | tested | notes                             | ;;
;; |-------------|-------------|--------|-----------------------------------| ;;
;; | ext.l       | yes         | yes    |                                   | ;;
;; | ext.w       | yes         | yes    |                                   | ;;
;; | jmp         | ~           |        |                                   | ;;
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

    call m68k.parse_operand@op1, dn

    assert_data_reg dn

    emit 1, 01001000b
    ;            1S000000b ; S = 0-> .w, S = 1-> .l
    compute tmp, 10000000b + (dn - m68k.data_reg) ; TODO: Move this into emit!
    emit 1, tmp
end calminstruction
define ext.w +ext.w

calminstruction ext.l? dn*
    local tmp

    call m68k.parse_operand@op1, dn

    assert_data_reg dn

    emit 1, 01001000b
    ;            1S000000b ; S = 0-> .w, S = 1-> .l
    compute tmp, 11000000b + (dn - m68k.data_reg) ; TODO: Move this into emit!
    emit 1, tmp
end calminstruction
define ext.l +ext.l

; TODO: Restrict to valid addressing modes for jmp.
calminstruction jmp? ea*
    local tmp

    call m68k.parse_operand@op1, ea

    emit 1, 01001110b
    emit 1, 11000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits
end calminstruction
define jmp +jmp

; Exchange the upper and lower 16-bit words of a data register.
; arguments:
;     dn: data register (d0 - d7)
; TODO: Assert that dn is a data register
;       with `relativeto` or whatever one is supposed to use.
calminstruction swap? dn*
    local tmp

    call m68k.parse_operand@op1, dn

    assert_data_reg dn

    emit 1, 01001000b
    compute tmp, 01000000b + (dn - m68k.data_reg) ; TODO: Move this into emit!
    emit 1, tmp
end calminstruction
define swap +swap

; Trigger any of the 16 "trap" interrupts.
; arguments:
;     vector: 0000 - 1111
calminstruction trap? vector*
        local tmp

        call m68k.parse_operand@op1, vector

        check @op1.type eq 'imm'
        jyes skip_error
        ; TODO: I should prolly have a better way to display error messages
        ; Some more general error handling stuff.
        display @op1.type bappend 13 bappend 10
        display @op1.type
        err 'trap only accepts immediate values'
    skip_error:

        assert_min vector, 0
        assert_max vector, 15

        emit 1, 01001110b
        compute tmp, 01000000b + vector ; TODO: Move this into emit!
        emit 1, tmp
end calminstruction
define trap +trap