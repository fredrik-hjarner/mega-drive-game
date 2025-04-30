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
include "m68k.inc"
    endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Test out addressing modes and stuff                                        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    if fasmg
    ; display 10, "- parse_operand -------", 10, 10

    ; parse_operand   #10     ; immediate addressing
    ; parse_operand   #$10    ; immediate addressing

    ; ; parse_operand   10      ; TODO: Not supported for now! Need explicit .w/.l
    ; parse_operand   10.w    ; absolute addressing
    ; parse_operand   (10).w  ; absolute addressing
    ; parse_operand   $10.w   ; absolute addressing
    ; parse_operand   ($10).w ; absolute addressing

    ; parse_operand   10.l    ; absolute addressing
    ; parse_operand   (10).l  ; absolute addressing
    ; parse_operand   $10.l   ; absolute addressing
    ; parse_operand   ($10).l ; absolute addressing

    ; parse_operand   d0      ; direct data register addressing
    ; parse_operand   a0      ; direct address register addressing
    ; parse_operand   sp      ; direct address register addressing
    ; parse_operand   (a0)    ; indirect address register addressing
    ; parse_operand   -(a0)   ; 
    ; parse_operand   (a0)+   ; 
    ; parse_operand   -(a0)+   ; TODO: This should generate error.

    ; parse_operand   $7FFF(a2)  ; 
    ; parse_indirect_displacement   $7FFF(a2)  ; 

    ; parse_reg_list d0
    ; parse_reg_list d0-d1
    parse_reg_list d0/d1

    ; movem.w (a2),d5-a7

    endif

