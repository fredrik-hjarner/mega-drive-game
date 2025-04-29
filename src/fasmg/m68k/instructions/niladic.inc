;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 niladic instructions                                        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Illegal instruction (forces illegal instruction exception)
calminstruction illegal?
    emit 1, 01001010b
    emit 1, 11111100b
end calminstruction

; No operation.
calminstruction nop?
    emit 1, 01001110b
    emit 1, 01110001b
end calminstruction

; Reset external devices (??)
calminstruction reset?
    emit 1, 01001110b
    emit 1, 01110000b
end calminstruction

; Return from Exception
calminstruction rte?
    emit 1, 01001110b
    emit 1, 01110011b
end calminstruction

; Return and Restore condition codes
calminstruction rtr?
    emit 1, 01001110b
    emit 1, 01110111b
end calminstruction

; Return from Subroutine
calminstruction rts?
    emit 1, 01001110b
    emit 1, 01110101b
end calminstruction

; Trap on overflow
calminstruction trapv?
    emit 1, 01001110b
    emit 1, 01110110b
end calminstruction
