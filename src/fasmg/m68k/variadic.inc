;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 variadic instructions.                                      ;;
;;                                                                            ;;
;; What I mean with "variadic" are instruction that can take either 1 or 2    ;;
;; operands so they aren't quite monadic or dyadic but rather both at the     ;;
;; same time in a way.                                                        ;;
;;                                                                            ;;
;; | # | instruction | implemented | tested | notes                         | ;;
;; |---|-------------|-------------|--------|-------------------------------| ;;
;; |   | asl.b       | ~           | ~      | only dyadic version done      | ;;
;; |   | asl.l       | ~           | ~      | only dyadic version done      | ;;
;; |   | asl.w       | ~           | ~      | only dyadic version done      | ;;
;; |   | asr.b       | ~           | ~      | only dyadic version done      | ;;
;; |   | asr.l       | ~           | ~      | only dyadic version done      | ;;
;; |   | asr.w       | ~           | ~      | only dyadic version done      | ;;
;; |   |             |             |        |                               | ;;
;; |   | lsl.b       | ~           |        | only dyadic version done      | ;;
;; |   | lsl.l       | ~           |        | only dyadic version done      | ;;
;; |   | lsl.w       | ~           |        | only dyadic version done      | ;;
;; |   | lsr.b       | ~           |        | only dyadic version done      | ;;
;; |   | lsr.l       | ~           |        | only dyadic version done      | ;;
;; |   | lsr.w       | ~           |        | only dyadic version done      | ;;
;; |   |             |             |        |                               | ;;
;; |   | roxl.b      | ~           |        | only dyadic version done      | ;;
;; |   | roxl.l      | ~           |        | only dyadic version done      | ;;
;; |   | roxl.w      | ~           |        | only dyadic version done      | ;;
;; |   | roxr.b      | ~           |        | only dyadic version done      | ;;
;; |   | roxr.l      | ~           |        | only dyadic version done      | ;;
;; |   | roxr.w      | ~           |        | only dyadic version done      | ;;
;; |   |             |             |        |                               | ;;
;; |   | rol.b       | ~           |        | only dyadic version done      | ;;
;; |   | rol.l       | ~           |        | only dyadic version done      | ;;
;; |   | rol.w       | ~           |        | only dyadic version done      | ;;
;; |   | ror.b       | ~           |        | only dyadic version done      | ;;
;; |   | ror.l       | ~           |        | only dyadic version done      | ;;
;; |   | ror.w       | ~           |        | only dyadic version done      | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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
            macro calminstruction?.instr_prefix#dir_suffix#_#size_suffix#_monadic? ea*
                ; TODO: Update/improve error message
                err "monadic version of asl.b is not implemented!"
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
                    ; transform dn, m68k ; TODO: Only for preprocess.inc!!
            
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
                ; transform dn1, m68k ; TODO: Only for preprocess.inc!!
                ; transform dn2, m68k ; TODO: Only for preprocess.inc!!

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
                _emit 1, 11100000b + ((tmp - m68k.data_reg) shl 1) + dir

                ;            Size           Imm/Dreg    Instruction
                compute tmp, (size shl 6) + (1 shl 5) + (instr shl 3) + (dn2 - m68k.data_reg)
                _emit 1, tmp
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
                    transform dn, m68k ; TODO: Only for preprocess.inc!!
                    ; jno errz

                    local tmp

                    assert_min imm, 0
                    assert_max imm, 7
                    assert_data_reg dn

                    ; 0 1 2 3 4    5    6    7      8  9  10 11 12 13 14 15
                    ; 1 1 1 0 Rot1 Rot2 Rot3 D      S1 S2 M  0  0  Dn Dn Dn
                    ; D = 0 -> Right shift
                    ; D = 1 -> Left shift
                    ; S = Size (00 = Byte, 01 = Word, 10 = Long)
                    compute tmp, imm ; TODO: Is this compute needed?
                    ;                                 Direction
                    _emit 1, 11100000b + (tmp shl 1) + dir

                    ;            Size           Imm/Dreg    Instruction
                    compute tmp, (size shl 6) + (0 shl 5) + (instr shl 3) + (dn - m68k.data_reg)
                    _emit 1, tmp
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

            ; Make visible to the preprocessor
            define instr_prefix#dir_suffix#.#size_suffix +instr_prefix#dir_suffix#.#size_suffix
        end iterate ; <size_suffix, size>
    end iterate ; <direction_suffix, direction>
end iterate ; <instr_prefix, instr>