;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 monadicinstructions                                        ;;
;;                                                                            ;;
;; | instruction | implemented | tested | notes                             | ;;
;; |-------------|-------------|--------|-----------------------------------| ;;
;; | swap        | yes         |        |                                   | ;;
;; | trap        | yes         | yes    |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Trigger any of the 16 "trap" interrupts.
; arguments:
;     vector: 0000 - 1111
calminstruction trap? vector
    local tmp

    assert_min vector, 0
    assert_max vector, 15

    emit 1, 01001110b
    compute tmp, 01000000b + vector
    emit 1, tmp
end calminstruction
define trap +trap

; Exchange the upper and lower 16-bit words of a data register.
; arguments:
;     dn: data register (d0 - d7)
; TODO: Assert that dn is a data register.
calminstruction swap? dn
    local tmp

    emit 1, 01001000b
    compute tmp, 01000000b + dn
    emit 1, tmp
end calminstruction
define swap +swap