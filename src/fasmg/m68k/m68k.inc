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
include "monadic.inc"
include "dyadic.inc"