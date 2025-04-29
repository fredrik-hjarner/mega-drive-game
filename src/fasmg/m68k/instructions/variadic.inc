;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 variadic instructions.                                      ;;
;;                                                                            ;;
;; What I mean with "variadic" are instruction that can take either 1 or 2    ;;
;; operands so they aren't quite monadic or dyadic but rather both at the     ;;
;; same time in a way.                                                        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Seems all of these only allow the immediate operande to be 1-8
; though it seems that 8 will be encoded as zero.
; TODO: Inconsistent, I have instr and instr_bits on other places.
iterate <instr_prefix,  instr>, \
        \ ; Arithmetic Shift
        as,             00b, \
        \ ; Logical Shift
        ls,             01b, \
        \ ; Rotate with Extend
        rox,            10b, \
        \ ; Rotate
        ro,             11b
    iterate <dir_suffix,  dir>, \
            r,            0b, \
            l,            1b
        iterate <size_suffix,  size>, \
                b,             00b, \
                w,             01b, \
                l,             10b

            ; TODO: Comment
            ; TODO: I think this one can only be .w
            ;       Seems manual says if monadic then it shift a word.
            ;       Double-check this. As it is I generate instructions for
            ;       all sizes right now.
            macro calminstruction?.instr_prefix#dir_suffix#_#size_suffix#_monadic? ea*
                call m68k.parse_operand@op1, ea

                ; first byte
                emit 1, 11100000b + instr shl 1 + dir

                ; second byte
                emit 1, 11000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits

                ; <ea> extension words
                ; bswap is needed because famg outputs in little-endian
                emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes
            end macro

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
            macro calminstruction?.instr_prefix#dir_suffix#_#size_suffix#_dyadic? op1*, dn*
                    new @data_reg
                    new @done_dyadic

                    check op1 relativeto m68k.data_reg
                    @ jyes @data_reg
                ; immediate:
                    instr_prefix#dir_suffix#_#size_suffix#_dyadic_imm op1, dn
                    @ jump @done_dyadic
                @ @data_reg:
                    instr_prefix#dir_suffix#_#size_suffix#_dyadic_data_reg op1, dn
                @ @done_dyadic:
            end macro

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
            macro calminstruction?.instr_prefix#dir_suffix#_#size_suffix#_dyadic_data_reg? dn1*, dn2*
                local tmp

                assert_data_reg dn1
                assert_data_reg dn2

                ; 0 1 2 3 4    5    6    7      8  9  10 11 12 13 14 15
                ; 1 1 1 0 Rot1 Rot2 Rot3 D      S1 S2 M  0  0  Dn Dn Dn
                ; D = 0 -> Right shift
                ; D = 1 -> Left shift
                ; S = Size (00 = Byte, 01 = Word, 10 = Long)
                compute tmp, dn1 ; TODO: Is this compute needed?
                ;                                                   Direction
                emit 1, 11100000b + ((tmp - m68k.data_reg) shl 1) + dir

                ;            Size           Imm/Dreg    Instruction
                compute tmp, (size shl 6) + (1 shl 5) + (instr shl 3) + (dn2 - m68k.data_reg)
                emit 1, tmp
            end macro

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
            macro calminstruction?.instr_prefix#dir_suffix#_#size_suffix#_dyadic_imm? imm*, dn*
                    ; jno errz

                    local tmp

                    assert_min imm, 1
                    assert_max imm, 8
                    assert_data_reg dn

                    ; 0 1 2 3 4    5    6    7      8  9  10 11 12 13 14 15
                    ; 1 1 1 0 Rot1 Rot2 Rot3 D      S1 S2 M  0  0  Dn Dn Dn
                    ; D = 0 -> Right shift
                    ; D = 1 -> Left shift
                    ; S = Size (00 = Byte, 01 = Word, 10 = Long)
                    ; 8 is encoded as 0, I think mod with 8 takes care of that.
                    compute tmp, imm mod 8 ; TODO: Is this compute needed?
                    ;                                 Direction
                    emit 1, 11100000b + (tmp shl 1) + dir

                    ;            Size           Imm/Dreg    Instruction
                    compute tmp, (size shl 6) + (0 shl 5) + (instr shl 3) + (dn - m68k.data_reg)
                    emit 1, tmp
                ;     jump ddd
                ; errz:
                ;     err "Error: blow up!!"
                ; ddd:
            end macro

            ; Description:
            ;     Arithmetic Shift Left.
            ;     See the different variants for more documentation.
            calminstruction instr_prefix#dir_suffix#.#size_suffix? op1*, op2
                    match , op2
                    jyes one_operand
                ; two_operands:
                    instr_prefix#dir_suffix#_#size_suffix#_dyadic op1, op2
                    jump done
                one_operand:
                    instr_prefix#dir_suffix#_#size_suffix#_monadic op1
                done:
            end calminstruction

        end iterate ; <size_suffix, size>
    end iterate ; <direction_suffix, direction>
end iterate ; <instr_prefix, instr>