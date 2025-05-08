;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Wrapper for fasm68k                                                        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "fasmg/macros.inc"

macro calminstruction?._emit_word? line&
    emit line
end macro

macro calminstruction?._emit_str? line&
    emit line
end macro

macro calminstruction?._assemble? line&
    assemble line
end macro

include "main.asm"