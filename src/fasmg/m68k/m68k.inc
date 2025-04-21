include "xxcalm.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; even exists in m68k assemblers it seems so I need it kinda.
macro even
    align 2
end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro calminstruction?.assert_min? value*, min*
        local tmp

        new @done

        ; compute tmp, value
        check value >= min
        @ jyes @done
        ; TODO: I'd like to have a setting that warns or errors, or something.
        err "Error: assert_min"
    @ @done:
end macro

macro calminstruction?.assert_max? value*, max*
        local tmp

        new @done

        ; compute tmp, value
        check value <= max
        @ jyes @done
        ; TODO: I'd like to have a setting that warns or errors, or something.
        err "Error: assert_max"
    @ @done:
end macro

macro calminstruction?.assert_data_reg? value*
        local tmp

        new @done

        ; compute tmp, value
        check value relativeto m68k.data_reg
        @ jyes @done
        ; TODO: I'd like to have a setting that warns or errors, or something.
        err "Error: assert_data_reg"
    @ @done:
end macro

; TODO: Implement.
macro calminstruction?.assert_word_aligned? ea*
    err "assert_word_aligned is not implemented!"
end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "registers.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; PARSE_OPERAND                                                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Define variable/namespace where parse_operand will store its results,
; for example @op1.type
; Use parse_operand by suffixing it will either @op1 or @op2 like this:
;     parse_operand@op1 some_operand_to_parse
; This is just for convenience.
define @op1 @op1
define @op2 @op2

iterate op, @op1,@op2
    namespace op
        ;; Define values in the @op1 and @op2 namespaces. ;;;;;;;;;;;;;;;;;;;;;;

        ; TODO: use these instead:
        ;     Dn  An  (An)  (An)+  ‑(An)  (d,An)  (d,An,Xi)  ABS.W  ABS.L  (d,PC)  (d,PC,Xn)  imm
        ; type:
        ;     'unknown'         (default. may indicate error)
        ;     'dn'              (direct data register addressing)
        ;     'an'              (direct address register addressing)
        ;     '(an)'            (indirect address register addressing)
        ;     'abs.w'           (absolute word addressing)
        ;     'abs.l'           (absolute long addressing)
        ;     'imm'             (immediate addressing)
        ;     'label'           (label. this might be stange, dunno)
        define type

        ; TODO: Comment.
        ; 3 bits. 000b to 111b.
        ; type:
        ;     'unknown'         (default. may indicate error)
        ;     000b              dn
        ;     001b              an
        ;     010b              (an)
        ;     011b              (an)+
        ;     100b              -(an)
        ;     101b              (d,an)
        ;     110b              (d,an,Xn)
        ;     111b              (d,pc)
        ;     111b              (d,pc,Xn)
        ;     111b              abs.w
        ;     111b              abs.l
        ;     111b              imm
        define ea_mode_bits

        ; The number of the register.
        ; 3 bits. 000b to 111b.
        define ea_reg_bits

        ; The number of extension words,
        ; but I changed it to bytes because then I don't have to multiply
        ; by 2 when I output the extension words.
        define ext_bytes

        ; Either 16 or 32 bits i.e. 1 or 2 extension words,
        ; but I changed it to bytes because then I don't have to multiply
        ; by 2 when I output the extension words.
        define ext_bytes_bits

        ; The value of the immediate operand.
        define imm ; TODO: Think about this.

        ; abs_size:
        ;     'unknown'         (default. may indicate error)
        ;     'w'               (absolute word addressing)
        ;     'l'               (absolute long addressing)
        ; define abs_size ; TODO I propbably don't need this?

        ; TODO: Think about this...
        ; define reg_bits

        ; TODO: Probably change name to `parse_effective_address`,
        ; but I am not sure that's a good idea or not because mayube this
        ; could be used for dn, an etc too.
        calminstruction m68k.parse_operand#op operand
                    ; locals
                    local tmp
                    local opstr
                    local maybe_number
                    local maybe_abs

                    ; stringify operand so I can print it to debug.
                    arrange opstr, operand
                    stringify opstr
                    ; display opstr bappend 9

                    ; default values
                    compute type, 'unknown'    ; TODO: Better default value?
                    compute ea_mode_bits, 123d ; TODO: Better default value?
                    compute ea_reg_bits,  123d ; TODO: Better default value?
                    compute ext_bytes, 0       ; TODO: Better default value?
                    compute ext_bytes_bits, 0  ; TODO: Better default value?

            ;; (an) ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            ; check_if_indirect_an:
                    match (an), operand
                    jno check_if_minus_an
                    check an relativeto m68k.address_reg
                    jno check_if_minus_an
                    compute type, '(an)'
                    compute ea_mode_bits, 010b
                    compute ea_reg_bits, an - m68k.address_reg
                    compute ext_bytes, 0
                    jump done
            ; -(an) ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            check_if_minus_an:
                    match -(an), operand
                    jno check_if_plus_an
                    check an relativeto m68k.address_reg
                    jno check_if_plus_an
                    compute type, '-(an)'
                    compute ea_mode_bits, 100b
                    compute ea_reg_bits, an - m68k.address_reg
                    compute ext_bytes, 0
                    jump done
            ; (an)+ ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            check_if_plus_an:
                    match (an)+, operand
                    jno check_if_immediate
                    check an relativeto m68k.address_reg
                    jno check_if_immediate
                    compute type, '(an)+'
                    compute ea_mode_bits, 011b
                    compute ea_reg_bits, an - m68k.address_reg
                    compute ext_bytes, 0
                    compute ext_bytes_bits, 0
                    jump done
            ;; imm ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            ; TODO: Immediate can have either 1 or 2 extension words!
            check_if_immediate:
                    match =# maybe_number, operand
                    jno check_if_abs_w
                ; hash_prefix:
                    check maybe_number eqtype 0
                    jyes skip_immediate_addressing_error
                    err 'immediate_addressing_error' ; TODO: better err message.
                skip_immediate_addressing_error:
                    compute type, 'imm'
                    compute ea_mode_bits, 111b
                    compute ea_reg_bits, 100b
                    compute imm, maybe_number
                    jump done
            ;; abs.w ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            check_if_abs_w:
                    match maybe_abs.=w, operand, ()
                    jno check_if_abs_l
                    check maybe_abs relativeto 0
                    jno check_if_abs_l
                    compute type, 'abs.w'
                    compute ea_mode_bits, 111b
                    compute ea_reg_bits, 000b
                    compute ext_bytes, 2
                    compute ext_bytes_bits, maybe_abs
                    jump done
            ;; abs.l ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            check_if_abs_l:
                    match maybe_abs.=l, operand, ()
                    jno check_if_dn
                    check maybe_abs relativeto 0
                    jno check_if_dn
                    compute type, 'abs.l'
                    compute ea_mode_bits, 111b
                    compute ea_reg_bits, 001b
                    compute ext_bytes, 4
                    compute ext_bytes_bits, maybe_abs
                    jump done
            ;; Check if `dn` (direct data register addressing) ;;;;;;;;;;;;;;;;;
            check_if_dn:
                    check operand relativeto m68k.data_reg
                    jno check_if_an
                    compute type, 'dn'
                    compute ea_mode_bits, 000b
                    compute ea_reg_bits, operand - m68k.data_reg
                    compute ext_bytes, 0
                    jump done
            ;; Check if `an` (direct address register addressing) ;;;;;;;;;;;;;;
            check_if_an:
                    check operand relativeto m68k.address_reg
                    jno unknown
                    compute type, 'an'
                    compute ea_mode_bits, 001b
                    compute ea_reg_bits, operand - m68k.address_reg
                    compute ext_bytes, 0
                    jump done
            ;; label ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            ; TODO: Can labels be both .w and and .l?
            ; TODO: Do I need this or is abs.w and abs.l enough??
            ; label_w:
            ;         match (tmp).=w, operand
            ;         jno done
            ;         ; I have added an is_label property to each label.
            ;         arrange tmp, tmp.=is_label
            ;         check defined tmp
            ;         jno done
            ;         compute type, 'label'
            ;         jump done
            ;; Temporary stuff ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            unknown:
                    err 'Failed to parse operand'
                    ; compute type, 'unknown'
                    ; display 'unknown' bappend 10
                    exit
            ;; Post-processing kind of ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            done:
                    ;; header ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                    display 'op' bappend 9
                    display 'type' bappend 9
                    display 'mode' bappend 9
                    display 'reg' bappend 9
                    display '#ext' bappend 10

                    ;; data ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                    display opstr bappend 9

                    ; log type
                    display type bappend 9

                    ; log ea_mode_bits
                    arrange tmp, ea_mode_bits
                    stringify tmp
                    display tmp bappend 9

                    ; log ea_reg_bits
                    arrange tmp, ea_reg_bits
                    stringify tmp
                    display tmp bappend 9

                    ; log ext_bytes
                    arrange tmp, ext_bytes
                    stringify tmp
                    display tmp bappend 9

                    ; log ext_bytes_bits
                    arrange tmp, ext_bytes_bits
                    stringify tmp
                    display tmp bappend 10

                    exit
        end calminstruction
    end namespace
end iterate

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Data declaration stuff                                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO:
;     Test constraints maybe?
calminstruction dc.b? tail&
        local head, tail, length, last_argument
        compute last_argument, 0
    next:
        match head=,tail, tail
        jyes at_least_two_arguments
    ; last argument:
        match head, tail
        compute last_argument, 1
    at_least_two_arguments:
        ; compute tmp, value ; TODO: Is this needed?
        check head eqtype ''
        jyes string
        _emit 1, head
        jump maybe_next
    string:
        compute length, lengthof head
        _emit length, head
    maybe_next:
        check last_argument = 0
        jyes next
end calminstruction
; define dc.b +dc.b

; TODO:
;     Test constraints maybe?
calminstruction dc.w? tail&
        local head, tail, last_argument
        compute last_argument, 0
    next:
        match head=,tail, tail
        jyes at_least_two_arguments
    ; last argument:
        match head, tail
        compute last_argument, 1
    at_least_two_arguments:
        ; bswap is needed because famg outputs in little-endian :'/
        compute head, head bswap 2
        _emit 2, head
    maybe_next:
        check last_argument = 0
        jyes next
end calminstruction
; define dc.w +dc.w

; TODO:
;     Test constraints maybe?
calminstruction dc.l? tail&
        local head, tail, last_argument
        compute last_argument, 0
    next:
        match head=,tail, tail
        jyes at_least_two_arguments
    ; last argument:
        match head, tail
        compute last_argument, 1
    at_least_two_arguments:
        ; bswap is needed because famg outputs in little-endian :'/
        compute head, head bswap 4
        _emit 4, head
    maybe_next:
        check last_argument = 0
        jyes next
end calminstruction
; define dc.l +dc.l

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Decorate or mark labels                                                    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Define is_label on the label so I can identify what is and isn't a label.
; TODO: Can this interceptor be make with CALM?
; struc (label) ? line&
;     define label.is_label
;     . line
; end struc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 68000 instruction set implemented in fasmg                                 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "niladic.inc"
include "monadic.inc"
include "dyadic.inc"
include "variadic.inc"

;; Just a test instruction to test all the addressing modes and stuff ;;;;;;;;;;

calminstruction parse_operand? op
    call m68k.parse_operand@op1, op
end calminstruction