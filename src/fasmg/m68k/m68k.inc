include "xxcalm.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro calminstruction?.assert_min? value, min
        local tmp

        new @done

        ; compute tmp, value
        check value >= min
        @ jyes @done
        ; TODO: I'd like to have a setting that warns or errors, or something.
        err "Error: assert_min"
    @ @done:
end macro

macro calminstruction?.assert_max? value, max
        local tmp

        new @done

        ; compute tmp, value
        check value <= max
        @ jyes @done
        ; TODO: I'd like to have a setting that warns or errors, or something.
        err "Error: assert_max"
    @ @done:
end macro

macro calminstruction?.assert_data_reg? value
        local tmp

        new @done

        ; compute tmp, value
        check value relativeto m68k.data_reg
        @ jyes @done
        ; TODO: I'd like to have a setting that warns or errors, or something.
        err "Error: assert_data_reg"
    @ @done:
end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define m68k m68k

element m68k.data_reg
d0? := m68k.data_reg + 000b
d1? := m68k.data_reg + 001b
d2? := m68k.data_reg + 010b
d3? := m68k.data_reg + 011b
d4? := m68k.data_reg + 100b
d5? := m68k.data_reg + 101b
d6? := m68k.data_reg + 110b
d7? := m68k.data_reg + 111b

element m68k.address_reg
a0? := m68k.address_reg + 000b
a1? := m68k.address_reg + 001b
a2? := m68k.address_reg + 010b
a3? := m68k.address_reg + 011b
a4? := m68k.address_reg + 100b
a5? := m68k.address_reg + 101b
a6? := m68k.address_reg + 110b
a7? := m68k.address_reg + 111b

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 68000 instruction set implemented in fasmg                                 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "niladic.inc"
include "monadic.inc"
include "dyadic.inc"