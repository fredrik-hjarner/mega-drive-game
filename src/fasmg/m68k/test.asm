include "format_fasmg.inc"
include "m68k.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; All niladic instructions.                                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; db "illegal", 0
; TODO: Every instruction must start on a word-aligned address.
illegal
nop
reset
rte
rtr
rts
trapv

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; All monadic instructions.                                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

swap d0
swap d1
swap d2
swap d3
swap d4
swap d5
swap d6
swap d7
swap 8 ; TODO: This should generate error because only d0-d7 are allowed.

; trap -1 ; TODO: This should generate error. 0 is lowest allowed.
trap 0
trap 1
trap 14
trap 15
; trap 16 ; TODO: THis should generate error. 15 is highest allowed.
