;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 monoadicinstructions                                        ;;
;;                                                                            ;;
;; | instruction | implemented | tested | notes                             | ;;
;; |-------------|-------------|--------|-----------------------------------| ;;
;; | clr         |             |        |                                   | ;;
;; | neg         |             |        |                                   | ;;
;; | negx        |             |        |                                   | ;;
;; | not         |             |        |                                   | ;;
;; | trap        | yes         |        |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;; |             |             |        |                                   | ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; arguments:
;     vector: 0000 - 1111
; TODO: Test.
; TODO: Give error if vector is out of range.
calminstruction trap? vector
    local tmp
    arrange tmp, =dc.=b= =%01001110
    assemble tmp

    ; second byte
    compute tmp, 01000000b + vector

    arrange tmp, =dc.=b= tmp
    assemble tmp
end calminstruction
define trap +trap