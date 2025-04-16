;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 niladic instructions                                        ;;
;;                                                                            ;;
;; | # | instruction | implemented | tested | notes                         | ;;
;; |---|-------------|-------------|--------|-------------------------------| ;;
;; | 1 | illegal     | yes         | yes    |                               | ;;
;; | 2 | nop         | yes         | yes    |                               | ;;
;; | 3 | reset       | yes         | yes    |                               | ;;
;; | 4 | rte         | yes         | yes    |                               | ;;
;; | 5 | rtr         | yes         | yes    |                               | ;;
;; | 6 | rts         | yes         | yes    |                               | ;;
;; | 7 | trapv       | yes         | yes    |                               | ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Illegal instruction (forces illegal instruction exception)
calminstruction illegal?
    _emit 1, 01001010b
    _emit 1, 11111100b
end calminstruction
define illegal +illegal

; No operation.
calminstruction nop?
    _emit 1, 01001110b
    _emit 1, 01110001b
end calminstruction
define nop +nop

; Reset external devices (??)
calminstruction reset?
    _emit 1, 01001110b
    _emit 1, 01110000b
end calminstruction
define reset +reset

; Return from Exception
calminstruction rte?
    _emit 1, 01001110b
    _emit 1, 01110011b
end calminstruction
define rte +rte

; Return and Restore condition codes
calminstruction rtr?
    _emit 1, 01001110b
    _emit 1, 01110111b
end calminstruction
define rtr +rtr

; Return from Subroutine
calminstruction rts?
    _emit 1, 01001110b
    _emit 1, 01110101b
end calminstruction
define rts +rts

; Trap on overflow
calminstruction trapv?
    _emit 1, 01001110b
    _emit 1, 01110110b
end calminstruction
define trapv +trapv
