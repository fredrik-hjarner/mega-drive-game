; set fasmg to
;     1 if assembling with fasmg
;     0 if assembling with vasm or clownassembler
; Comment out endif macro if assembling with
; vasm or clownassembler.
fasmg equ 1
; fasmg equ 0
; TODO: Maybe I should have this as a compatability macro?
macro endif!
    end if
end macro

    if fasmg
include "format_fasmg.inc"
include "m68k.inc"
    endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Test out addressing modes and stuff                                        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    if fasmg
    ; display 10, "- parse_operand -------", 10, 10

    parse_operand   #10     ; immediate addressing
    parse_operand   #$10    ; immediate addressing

    ; parse_operand   10      ; TODO: Not supported for now! Need explicit .w/.l
    parse_operand   10.w    ; absolute addressing
    parse_operand   (10).w  ; absolute addressing
    parse_operand   $10.w   ; absolute addressing
    parse_operand   ($10).w ; absolute addressing

    parse_operand   10.l    ; absolute addressing
    parse_operand   (10).l  ; absolute addressing
    parse_operand   $10.l   ; absolute addressing
    parse_operand   ($10).l ; absolute addressing

    parse_operand   d0      ; direct data register addressing
    parse_operand   a0      ; direct address register addressing
    parse_operand   sp      ; direct address register addressing
    parse_operand   (a0)    ; indirect address register addressing
    parse_operand   -(a0)   ; 
    parse_operand   (a0)+   ; 
    ; parse_operand   -(a0)+   ; TODO: This should generate error.
    endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Data declaration stuff                                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; display 10, "- dc ------------------", 10, 10

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

    ; display 10, "- niladic -------------", 10, 10

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

l1:

    dc.b 0,'negx',0

    ; dn
    negx.b d0
    negx.b d1
    negx.w d0
    negx.w d1
    negx.l d0
    negx.l d1

    ; (an)
    negx.b (a0)
    negx.b (a1)
    negx.w (a0)
    negx.w (a1)
    negx.l (a0)
    negx.l (a1)

    dc.b 0,0,'clr',0

    ; dn
    clr.b d0
    clr.b d1
    clr.w d0
    clr.w d1
    clr.l d0
    clr.l d1

    ; (an)
    clr.b (a0)
    clr.b (a1)
    clr.w (a0)
    clr.w (a1)
    clr.l (a0)
    clr.l (a1)

    dc.b 0,0,'tst',0

    ; dn
    tst.b d0
    tst.b d1
    tst.w d0
    tst.w d1
    tst.l d0
    tst.l d1

    ; (an)
    tst.b (a0)
    tst.b (a1)
    tst.w (a0)
    tst.w (a1)
    tst.l (a0)
    tst.l (a1)

    dc.b 0,0,'bcc.b',0
 
    bhi.b l1
    bls.b l1
    bcc.b l1
    bcs.b l1
    bne.b l1
    beq.b l1
    bvc.b l1
    bvs.b l1
    bpl.b l1
    bmi.b l1
    bge.b l1
    blt.b l1
    bgt.b l1
    ble.b l1

    dc.b 0,0,'bcc.w',0

    bhi.w l1
    bls.w l1
    bcc.w l1
    bcs.w l1
    bne.w l1
    beq.w l1
    bvc.w l1
    bvs.w l1
    bpl.w l1
    bmi.w l1
    bge.w l1
    blt.w l1
    bgt.w l1
    ble.w l1


    ; display 10, "- bra.b ---------------", 10, 10

    ; bra.b #$12 ; TODO: This generates error on vasm and clownassembler.
    ; bra.b $12  ; TODO: So uhm is this allowed??
    ; TODO: hm... should it be l1 or l1.[bwl] ?? Think about it and decide!
    bra.b l1
    ; bra.b (l1).b ; clown and vasm does not allow!
    ; bra.b (l1).w ; clown and vasm does not allow!
    ; bra.b (l1).l ; clown does not allow but vasm does!

    ; display 10, "- bra.w ---------------", 10, 10

    ; bra.w #$1234 ; TODO: This generates error on vasm and clownassembler.
    ; bra.w $0123 ; TODO: So uhm is this allowed??
    bra.w l1
    ; bra.w (l1).b ; clown and vasm does not allow!
    ; bra.w (l1).w ; clown and vasm does not allow!
    ; bra.w (l1).l ; clown does not allow but vasm does!

    ; display 10, "- ext.w ---------------", 10, 10

    ext.w d0
    ext.w d1
    ext.w d2
    ext.w d3
    ext.w d4
    ext.w d5
    ext.w d6
    ext.w d7
    ; ext.w 8 ; TODO: This should generate error because only d0-d7 are allowed.

    ; display 10, "- ext.l ---------------", 10, 10

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

    ; jmp ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; display 10, "- jmp -----------------", 10, 10
    dc.b 0,0,'jmp',0

    ; Dn  An  (An)  (An)+  ‑(An)  (d,An)  (d,An,Xi) 
	;          ✓                    ✓         ✓ 
    ; ABS.W  ABS.L  (d,PC)  (d,PC,Xn)  imm
    ;   ✓     ✓       ✓        ✓
    ; TODO: Fix the jmp:s, something seems off...
    jmp (l1).w
    jmp l1.w
    jmp (l1).l
    jmp l1.l
    jmp 10.w
    jmp $10.w
    jmp 10.l
    jmp $10.l

    dc.b 0,0,'jsr',0

    jsr (l1).w
    jsr l1.w
    jsr (l1).l
    jsr l1.l
    jsr 10.w
    jsr $10.w
    jsr 10.l
    jsr $10.l


    ; display 10, "- trap ----------------", 10, 10

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

;; WITH I SUFFIX ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    dc.b 0,0,'ori',0

    ori.b  #1, d0
    ori.w  #1, d0
    ori.l  #1, d0

    ori.l  #1, 1.w
    ori.l  #1, 1.l

    ori.l  #1, l1.w
    ori.l  #1, l1.l

    dc.b 0,'andi',0

    andi.b #1, d0

    dc.b 0,'subi',0

    subi.b #1, d0

    dc.b 0,'addi',0

    addi.b #1, d0

    dc.b 0,'eori',0

    eori.b #1, d0

    dc.b 0,'cmpi',0

    cmpi.b #1, d0

;; ADDQ ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; display 10, "- addq----------------", 10, 10

    dc.b 0,'addq',0

    addq.b #1, d0
    addq.w #1, d0
    addq.l #1, d0

    addq.b #8, d0
    addq.w #8, d0
    addq.l #8, d0

;; SUBQ ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; display 10, "- subq----------------", 10, 10

    dc.b 0,'subq',0

    subq.b #1, d0
    subq.w #1, d0
    subq.l #1, d0

    subq.b #8, d0
    subq.w #8, d0
    subq.l #8, d0

;; MOVEQ ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

;; BUGS / REGRESSIONS TESTS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; cmpi.w #(16<<2), color_index.l
    ; addi.w #-1, hscroll_amount.l
    ; dbra d7,.ClearRAM
    ; movea.l #$FF0000, a0