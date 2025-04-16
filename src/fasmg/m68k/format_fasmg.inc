;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; I have some override to make development simpler then I have 2 include     ;;
;; files depending upong what I want the output to be.                        ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro calminstruction?._assemble? &line&
    assemble line
end macro
; _assemble equ assemble ; Uncomment to generate binary directly.

; variant of emit so that one can switch between clownassembler mode and
; fasmg stand-alone mode sort of.
; _emit emits to clownassembler
; To generate binary directly, use emit
; Only handles 1 byte but that will probably suffice.
macro calminstruction?._emit? &line&
    emit line
end macro
; _emit equ emit ; Uncomment to generate binary directly.