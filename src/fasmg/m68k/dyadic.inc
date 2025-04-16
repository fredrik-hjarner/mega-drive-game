;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 niladic instructions                                        ;;
;;                                                                            ;;
;; | # | instruction | implemented | tested | notes                         | ;;
;; |---|-------------|-------------|--------|-------------------------------| ;;
;; |   | moveq       | yes         |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   |             |             |        |                               | ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; arguments:
;     data: 0000_0000 - 1111_1111
;     dn: d0 - d7
; TODO: Test.
; TODO: Give error if data is out of range.
; TODO: Handle # character.
; TODO: Validate that dn is a data register.
calminstruction moveq? data, dn
    ; local tmp
    ; compute tmp, 01110000b + dn
    ; arrange tmp, =dc.=b= tmp
    ; _assemble tmp
    ; compute tmp, data
    ; arrange tmp, =dc.=b= tmp
    ; _assemble tmp

    ;;;;;;;;;;;;;;;;;;;;;;;;;

    local tmp
    compute tmp, 01110000b + dn
    emit 1, tmp
    compute tmp, data
    emit 1, tmp
end calminstruction
define moveq +moveq