;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 monadicinstructions                                         ;;
;;                                                                            ;;
;; | instruction | implemented | tested | notes                             | ;;
;; |-------------|-------------|--------|-----------------------------------| ;;
;; | bra.b       |             |        |                                   | ;;
;; | bra.w       |             |        |                                   | ;;
;; | bsr.b       |             |        |                                   | ;;
;; | bsr.w       |             |        |                                   | ;;
;; | ext.l       | yes         | yes    |                                   | ;;
;; | ext.w       | yes         | yes    |                                   | ;;
;; | jmp         |             |        |                                   | ;;
;; | swap        | yes         | yes    |                                   | ;;
;; | trap        | yes         | yes    |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;   bra.w <label> | <literal>
;   bra.b <label> | <literal>
;   bsr.w <label> | <literal>
;   bsr.b <label> | <literal>
;
; TODO: What exactly does label and literal mean in this context?
iterate <instr,  first_byte>, \
        \ ; Branch
        bra,     01100000b, \
        \ ; Branch Subroutine
        bsr,     01100001b

        ; TODO: Check if fits in a byte. Maybe do that in parse_operand?
        ; Also, check if displacement is a valid displacement.
        ; 0 is not allowed for .b I think.
        ; TODO: How will this be able to work with both label and literals???
        calminstruction? instr.b? label*
                local pc

                ; call m68k.parse_operand@op1, label

                compute pc, $ + 2

                _emit 1, first_byte

                ; Assume label is $10 and address is $20
                ; $10 - $20 = $10
                _emit 1, label - pc
        end calminstruction
        ; define instr.b +instr.b

        ; TODO: Check if fits in a word. Maybe do that in parse_operand?
        ;' Warn if fits in a byte.
        ; TODO: How will this be able to work with both label and literals???
        calminstruction? instr.w? label*
            local pc

            ; call m68k.parse_operand@op1, label

            compute pc, $ + 2

            _emit 1, first_byte
            _emit 1, 0 ; second byte being zero
            ; bswap is needed because famg outputs in little-endian :'/
            _emit 2, (label - pc) bswap 2
        end calminstruction
        ; define instr.w +instr.w

end iterate ; <instr, first_byte>

; Syntax: ext.w dn
;
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

; Syntax: ext.l dn
;
calminstruction ext.l? dn*
    local tmp

    call m68k.parse_operand@op1, dn

    assert_data_reg dn

    _emit 1, 01001000b
    ;            1S000000b ; S = 0-> .w, S = 1-> .l
    compute tmp, 11000000b + (dn - m68k.data_reg) ; TODO: Move this into emit!
    _emit 1, tmp
end calminstruction
define ext.l +ext.l

; Syntax: jmp <ea>
;
; TODO: Restrict to valid addressing modes for jmp.
calminstruction jmp? ea*
    local tmp

    call m68k.parse_operand@op1, ea

    _emit 1, 01001110b
    _emit 1, 11000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits
    ; bswap is needed because famg outputs in little-endian :'/
    _emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes
end calminstruction
define jmp +jmp

; Syntax: swap dn
;
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

; Syntax: trap #<vector>
;
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