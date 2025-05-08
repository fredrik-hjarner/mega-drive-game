;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Wrapper for fasm68k                                                        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "fasmg/macros.inc"

macro calminstruction?._emit? line&
    emit line
end macro

macro calminstruction?._assemble? line&
    assemble line
end macro

include "main.asm"