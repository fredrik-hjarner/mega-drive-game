include "format_fasmg.inc"
include "m68k.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; All niladic instructions.                                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

ext.w d0
ext.w d1
ext.w d2
ext.w d3
ext.w d4
ext.w d5
ext.w d6
ext.w d7
; ext.w 8 ; TODO: This should generate error because only d0-d7 are allowed.

ext.l d0
ext.l d1
ext.l d2
ext.l d3
ext.l d4
ext.l d5
ext.l d6
ext.l d7
; ext.l 8 ; TODO: This should generate error because only d0-d7 are allowed.

swap d0
swap d1
swap d2
swap d3
swap d4
swap d5
swap d6
swap d7
; swap 8 ; TODO: This should generate error because only d0-d7 are allowed.

; trap -1 ; TODO: This should generate error. 0 is lowest allowed.
trap 0
trap 1
trap 14
trap 15
; trap 16 ; TODO: This should generate error. 15 is highest allowed.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; All dyadic instructions.                                                   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

moveq 0, d0
moveq 0, d1
moveq 0, d2
moveq 0, d3
moveq 0, d4
moveq 0, d5
moveq 0, d6
moveq 0, d7

moveq 0, d0
moveq 1, d0
moveq 2, d0
moveq 3, d0

