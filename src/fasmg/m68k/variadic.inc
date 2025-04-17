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
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

iterate <dir_suffix,  dir>, \
        r,            0b, \
        l,            1b
    iterate <size_suffix,  size>, \
            b,             00b, \
            w,             01b, \
            l,             10b

        ; TODO: Comment
        macro calminstruction?.as#dir_suffix#_#size_suffix#_monadic? ea*
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
        macro calminstruction?.as#dir_suffix#_#size_suffix#_dyadic? op1*, dn*
                new @data_reg
                new @done_dyadic

                check op1 relativeto m68k.data_reg
                @ jyes @data_reg
            ; immediate:
                as#dir_suffix#_#size_suffix#_dyadic_imm op1, dn
                @ jump @done_dyadic
            @ @data_reg:
                as#dir_suffix#_#size_suffix#_dyadic_data_reg op1, dn
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
        macro calminstruction?.as#dir_suffix#_#size_suffix#_dyadic_data_reg? dn1*, dn2*
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

                ;            Size           Imm/Dreg
                compute tmp, (size shl 6) + (1 shl 5) + (dn2 - m68k.data_reg)
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
        macro calminstruction?.as#dir_suffix#_#size_suffix#_dyadic_imm? imm*, dn*
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
                emit 1, 11100000b + (tmp shl 1) + dir

                ;            Size           Imm/Dreg
                compute tmp, (size shl 6) + (0 shl 5) + (dn - m68k.data_reg)
                emit 1, tmp
        end macro

        ; Description:
        ;     Arithmetic Shift Left.
        ;     See the different variants for more documentation.
        calminstruction as#dir_suffix#.#size_suffix? op1*, op2
                match , op2
                jyes one_operand
            ; two_operands:
                as#dir_suffix#_#size_suffix#_dyadic op1, op2
                jump done
            one_operand:
                as#dir_suffix#_#size_suffix#_monadic op1
            done:
        end calminstruction

        ; Make visible to the preprocessor
        define as#dir_suffix#.#size_suffix +as#dir_suffix#.#size_suffix
    end iterate ; <size_suffix, size>
end iterate ; <direction_suffix, direction>