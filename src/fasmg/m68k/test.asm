include "format_fasmg.inc"
include "m68k.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Data declaration stuff                                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; TODO: Test edge cases.
    dc.b 0
    dc.b 1
    dc.b 2
    dc.b 3
    dc.b 4
    dc.b $FE
    dc.b $FF
    ; dc.b "" ; TODO: Not allowed by clownassembler. I allow it in fasmg though.
    dc.b "a"
    dc.b "ab"
    dc.b "abcd"
    dc.b 0, 1, 2, 3, 4

    dc.w 0
    dc.w 1
    dc.w 2
    dc.w $FF
    dc.w $FFFF
    dc.w $1234
    dc.w 0, 1, 2, 3, 4

    dc.l 0
    dc.l 1
    dc.l 2
    dc.l $FF
    dc.l $FFFF
    dc.l $1234
    dc.l $FFFFFFFF
    dc.l $12345678
    dc.l 0, 1, 2, 3, 4

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; All niladic instructions.                                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; word-align
    even

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
    ; trap 0 ; Generates error. trap only accepts immediates.
    trap #0
    trap #1
    trap #14
    trap #15
    ; trap 16 ; TODO: This should generate error. 15 is highest allowed.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; All dyadic instructions.                                                   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    moveq #0, d0
    moveq #0, d1
    moveq #0, d2
    moveq #0, d3
    moveq #0, d4
    moveq #0, d5
    moveq #0, d6
    moveq #0, d7

    moveq #0, d0
    moveq #1, d0
    moveq #2, d0
    moveq #3, d0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; All variadic instructions.                                                 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; ASL.B ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; TODO: Seems 0 is interpreted as 8, which makes sense,
    ; since a shift of 0 does not make sense.
    ; So I wonder if I should allow to input #8 and have it "wrap" or something.
    asl.b #8, d0
    asl.b #8, d1
    asl.b #8, d2
    asl.b #8, d3
    asl.b #8, d4
    asl.b #8, d5
    asl.b #8, d6

    asl.b d0, d0
    asl.b d1, d0
    asl.b d2, d0
    asl.b d3, d0
    asl.b d4, d0
    asl.b d5, d0
    asl.b d6, d0
    asl.b d7, d0

    asl.b #8, d0
    asl.b #1, d0
    asl.b #2, d0
    asl.b #3, d0
    asl.b #4, d0
    asl.b #5, d0
    asl.b #6, d0
    asl.b #7, d0

;; ASL.W ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    asl.w #8, d0
    asl.w #8, d1
    asl.w #8, d2
    asl.w #8, d3
    asl.w #8, d4
    asl.w #8, d5
    asl.w #8, d6

    asl.w d0, d0
    asl.w d1, d0
    asl.w d2, d0
    asl.w d3, d0
    asl.w d4, d0
    asl.w d5, d0
    asl.w d6, d0
    asl.w d7, d0

    asl.w #8, d0
    asl.w #1, d0
    asl.w #2, d0
    asl.w #3, d0
    asl.w #4, d0
    asl.w #5, d0
    asl.w #6, d0
    asl.w #7, d0

;; ASL.L ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    asl.l #8, d1
    asl.l #8, d2
    asl.l #8, d3
    asl.l #8, d4
    asl.l #8, d5
    asl.l #8, d6

    asl.l d0, d0
    asl.l d1, d0
    asl.l d2, d0
    asl.l d3, d0
    asl.l d4, d0
    asl.l d5, d0
    asl.l d6, d0
    asl.l d7, d0

    asl.l #8, d0
    asl.l #1, d0
    asl.l #2, d0
    asl.l #3, d0
    asl.l #4, d0
    asl.l #5, d0
    asl.l #6, d0
    asl.l #7, d0

;; ASR.B ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; TODO: Seems 0 is interpreted as 8, which makes sense,
    ; since a shift of 0 does not make sense.
    ; So I wonder if I should allow to input #8 and have it "wrap" or something.
    asr.b #8, d0
    asr.b #8, d1
    asr.b #8, d2
    asr.b #8, d3
    asr.b #8, d4
    asr.b #8, d5
    asr.b #8, d6

    asr.b d0, d0
    asr.b d1, d0
    asr.b d2, d0
    asr.b d3, d0
    asr.b d4, d0
    asr.b d5, d0
    asr.b d6, d0
    asr.b d7, d0

    asr.b #8, d0
    asr.b #1, d0
    asr.b #2, d0
    asr.b #3, d0
    asr.b #4, d0
    asr.b #5, d0
    asr.b #6, d0
    asr.b #7, d0

;; ASR.W ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    asr.w #8, d0
    asr.w #8, d1
    asr.w #8, d2
    asr.w #8, d3
    asr.w #8, d4
    asr.w #8, d5
    asr.w #8, d6

    asr.w d0, d0
    asr.w d1, d0
    asr.w d2, d0
    asr.w d3, d0
    asr.w d4, d0
    asr.w d5, d0
    asr.w d6, d0
    asr.w d7, d0

    asr.w #8, d0
    asr.w #1, d0
    asr.w #2, d0
    asr.w #3, d0
    asr.w #4, d0
    asr.w #5, d0
    asr.w #6, d0
    asr.w #7, d0

;; ASR.L ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    asr.l #8, d1
    asr.l #8, d2
    asr.l #8, d3
    asr.l #8, d4
    asr.l #8, d5
    asr.l #8, d6

    asr.l d0, d0
    asr.l d1, d0
    asr.l d2, d0
    asr.l d3, d0
    asr.l d4, d0
    asr.l d5, d0
    asr.l d6, d0
    asr.l d7, d0

    asr.l #8, d0
    asr.l #1, d0
    asr.l #2, d0
    asr.l #3, d0
    asr.l #4, d0
    asr.l #5, d0
    asr.l #6, d0
    asr.l #7, d0