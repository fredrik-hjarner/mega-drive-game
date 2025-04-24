;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 monadicinstructions                                         ;;
;;                                                                            ;;
;; | instruction | implemented | tested | notes                             | ;;
;; |-------------|-------------|--------|-----------------------------------| ;;
;; | negx.[bwl]  | ~           | ~      |                                   | ;;
;; | clr.[bwl]   | ~           | ~      |                                   | ;;
;; | neg.[bwl]   | ~           |        |                                   | ;;
;; | not.[bwl]   | ~           |        |                                   | ;;
;; | tst.[bwl]   | ~           | ~      |                                   | ;;
;; |             |             |        |                                   | ;;
;; | bcc.[bw]    | ~           | ~      |                                   | ;;
;; | bra.b       | ~           |        |                                   | ;;
;; | bra.w       | ~           |        |                                   | ;;
;; | bsr.b       | ~           |        |                                   | ;;
;; | bsr.w       | ~           |        |                                   | ;;
;; | ext.l       | ~           | ~      |                                   | ;;
;; | ext.w       | ~           | ~      |                                   | ;;
;; | jmp         | ~           |        |                                   | ;;
;; | jsr         | ~           |        |                                   | ;;
;; | swap        | ~           | ~      |                                   | ;;
;; | trap        | ~           | ~      |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Placeholders for not yet implemented instructions ;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro nbcd.b line&
end macro

macro pea.l line&
end macro

macro tas.b line&
end macro

macro unlk line&
end macro

macro stop line&
end macro

; TODO: all scc instructions

;; SCC ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     scc.b <ea>
; Aliases:
;     hs = cc
;     lo = cs
iterate <cc,  cc_bits>, \
        t,      0000b, \
        f,      0001b, \
        hi,     0010b, \
        ls,     0011b, \
        cc,     0100b, \
        \ ; Alias for cc
        hs,     0100b, \
        cs,     0101b, \
        \ ; Alias for cs
        lo,     0101b, \
        ne,     0110b, \
        eq,     0111b, \
        vc,     1000b, \
        vs,     1001b, \
        pl,     1010b, \
        mi,     1011b, \
        ge,     1100b, \
        lt,     1101b, \
        gt,     1110b, \
        le,     1111b

        calminstruction s#cc.b? ea*
                call m68k.parse_operand@op1, ea

                ; first byte
                emit 1, 01010000b + cc_bits

                ; second byte
                emit 1, 11000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits

                ; <ea> extension words
                ; bswap is needed because famg outputs in little-endian :'/
                emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes
        end calminstruction

end iterate ; <cc, cc_bits>

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     negx <ea>
;     clr  <ea>
;     neg  <ea>
;     not  <ea>
;     tst  <ea>
; Addressing modes:
;     Dn  An  (An)  (An)+  ‑(An)  (d,An)  (d,An,Xi) 
;      ✓       ✓     ✓       ✓      ✓         ✓ 
;     ABS.W  ABS.L  (d,PC)  (d,PC,Xn)  imm
;       ✓     ✓                 
; TODO: Double-check addressing modes for all instructions.
;     tst also supports (d,PC)  (d,PC,Xn) modes
; TODO: Restrict to valid addressing modes for the instructions.
iterate <instr,  first_byte>, \
        \ ; 
        negx,    01000000b, \
        \ ; Clear
        clr,     01000010b, \
        \ ; 
        neg,     01000100b, \
        \ ; 
        not,     01000110b, \
        \ ; 
        tst,     01001010b
    iterate <size,  size_bits>, \
            b,      00b, \
            w,      01b, \
            l,      10b
    
            calminstruction instr.size? ea*
                ; local tmp

                call m68k.parse_operand@op1, ea

                emit 1, first_byte
                emit 1, size_bits shl 6 + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits
                ; bswap is needed because famg outputs in little-endian :'/
                emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes
            end calminstruction

    end iterate ; <size, size_bits>
end iterate ; <instr, first_byte>

; Syntax:
;   bcc.b <label>
;   bcc.w <label>
;
; TODO: What exactly does label and literal mean in this context?
; TODO: Add the different aliases for the conditions.
; Aliases:
;     hs = cc
;     lo = cs
iterate <cc,  cc_bits>, \
        \ ; 
        hi,     0010b, \
        \ ; 
        ls,     0011b, \
        \ ; 
        cc,     0100b, \
        \ ; Alias for cc
        hs,     0100b, \
        \ ; 
        cs,     0101b, \
        \ ; Alias for cs
        lo,     0101b, \
        \ ; 
        ne,     0110b, \
        \ ; 
        eq,     0111b, \
        \ ; 
        vc,     1000b, \
        \ ; 
        vs,     1001b, \
        \ ; 
        pl,     1010b, \
        \ ; 
        mi,     1011b, \
        \ ; 
        ge,     1100b, \
        \ ; 
        lt,     1101b, \
        \ ; 
        gt,     1110b, \
        \ ; 
        le,     1111b

        ; TODO: Check if fits in a byte. Maybe do that in parse_operand?
        ; Also, check if displacement is a valid displacement.
        ; 0 is not allowed for .b I think.
        ; TODO: How will this be able to work with both label and literals???
        calminstruction? b#cc.b? label*
            local pc
            local label_val

            ; call m68k.parse_operand@op1, label

            compute pc, $ + 2
            compute label_val, label

            emit 1, 01100000b + cc_bits

            ; Assume label is $10 and address is $20
            ; $10 - $20 = $10
            emit 1, label_val - pc
        end calminstruction

        ; TODO: Check if fits in a word. Maybe do that in parse_operand?
        ;' Warn if fits in a byte.
        ; TODO: How will this be able to work with both label and literals???
        calminstruction? b#cc.w? label*
            local pc
            local label_val

            ; call m68k.parse_operand@op1, label

            compute pc, $ + 2
            compute label_val, label

            emit 1, 01100000b + cc_bits
            emit 1, 0 ; second byte being zero
            ; bswap is needed because famg outputs in little-endian :'/
            emit 2, (label_val - pc) bswap 2
        end calminstruction

        ; alias for .b
        ; TODO: Not sure if this should be here or in alias .inc file.
        macro b#cc.s? line&
            b#cc.b line
        end macro

end iterate ; <cc, cc_bits>

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
                local label_val

                ; call m68k.parse_operand@op1, label

                compute pc, $ + 2
                compute label_val, label

                emit 1, first_byte

                ; Assume label is $10 and address is $20
                ; $10 - $20 = $10
                emit 1, label_val - pc
        end calminstruction

        ; TODO: Check if fits in a word. Maybe do that in parse_operand?
        ;' Warn if fits in a byte.
        ; TODO: How will this be able to work with both label and literals???
        calminstruction? instr.w? label*
            local pc
            local label_val

            ; call m68k.parse_operand@op1, label

            compute pc, $ + 2
            compute label_val, label

            emit 1, first_byte
            emit 1, 0 ; second byte being zero
            ; bswap is needed because famg outputs in little-endian :'/
            emit 2, (label_val - pc) bswap 2
        end calminstruction

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

; Syntax: ext.l dn
;
calminstruction ext.l? dn*
    local tmp

    call m68k.parse_operand@op1, dn

    assert_data_reg dn

    emit 1, 01001000b
    ;            1S000000b ; S = 0-> .w, S = 1-> .l
    compute tmp, 11000000b + (dn - m68k.data_reg) ; TODO: Move this into emit!
    emit 1, tmp
end calminstruction

; Syntax:
;     jmp <ea>
;     jsr <ea>
; Addressing modes:
;     Dn  An  (An)  (An)+  ‑(An)  (d,An)  (d,An,Xi) 
;              ✓                    ✓         ✓ 
;     ABS.W  ABS.L  (d,PC)  (d,PC,Xn)  imm
;       ✓     ✓       ✓        ✓
; TODO: Restrict to valid addressing modes for jmp/jsr.
iterate <instr,  second_byte>, \
        \ ; Jump
        jmp,     11000000b, \
        \ ; Jump Subroutine
        jsr,     10000000b

        calminstruction instr? ea*
            local tmp

            call m68k.parse_operand@op1, ea

            emit 1, 01001110b
            emit 1, second_byte + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits
            ; bswap is needed because famg outputs in little-endian :'/
            emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes
        end calminstruction

end iterate ; <instr, second_byte>

; Syntax: swap dn
;
; Exchange the upper and lower 16-bit words of a data register.
; arguments:
;     dn: data register (d0 - d7)
; TODO: Assert that dn is a data register
;       with `relativeto` or whatever one is supposed to use.
calminstruction swap.w? dn*
    local tmp

    call m68k.parse_operand@op1, dn

    assert_data_reg dn

    emit 1, 01001000b
    compute tmp, 01000000b + (dn - m68k.data_reg) ; TODO: Move this into emit!
    emit 1, tmp
end calminstruction

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