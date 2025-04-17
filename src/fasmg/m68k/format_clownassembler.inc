;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; This file contains stuff to make it generate text to clownassembler.       ;;
;; Eventually I want to have my own assembler (famg + a m68k instruction set) ;;
;; but that will take a while, so in the meantime I can have to "mix" where   ;;
;; fasmg runs as a preprocessor and tha passes it's ouput to clownassembler.  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; variant of assemble so that one can switch between clownassembler mode and
; fasmg stand-alone mode sort of.
; _assemble emits to clownassembler
; To generate binary directly, use assemble
macro calminstruction?._assemble? &line&
    stringify line
    ; TODO: Shorten this code?
    ; clownassembler stuff usually needs to be prefixed with whitespace.
    emit 1, 20h
    emit 1, 20h
    emit 1, 20h
    emit 1, 20h
    emit lengthof line, line
    emit 1, 13
    emit 1, 10
end macro
; _assemble equ assemble ; Uncomment to generate binary directly.

; variant of emit so that one can switch between clownassembler mode and
; fasmg stand-alone mode sort of.
; _emit emits to clownassembler
; To generate binary directly, use emit
; Only handles 1 byte but that will probably suffice.
macro calminstruction?._emit? number_of_bytes, value
        new @string
        new @done

        local tmp
        compute tmp, value
        check tmp eqtype ''
        @ jyes @string
    ; not_string:
        arrange tmp, =dc.=b= tmp
        _assemble tmp
        @ jump @done
    @ @string:
        arrange tmp, =dc.=b= value
        _assemble tmp
    @ @done:
end macro
; _emit equ emit ; Uncomment to generate binary directly.