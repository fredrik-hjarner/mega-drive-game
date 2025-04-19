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
        ;     Dn 	An 	(An) 	(An)+ 	‑(An) 	(d,An) 	(d,An,Xi) 	ABS.W 	ABS.L 	(d,PC) 	(d,PC,Xn) 	imm
        ; type:
        ;     'unknown'         (default. may indicate error)
        ;     'dn'              (direct data register addressing)
        ;     'an'              (direct address register addressing)
        ;     '(an)'            (indirect address register addressing)
        ;     'abs'             (absolute addressing)
        ;     'imm'             (immediate addressing)
        define type

        ; abs_size:
        ;     'unknown'         (default. may indicate error)
        ;     'w'               (absolute word addressing)
        ;     'l'               (absolute long addressing)
        define abs_size

        calminstruction m68k.parse_operand#op operand
                    ; locals
                    local opstr
                    local maybe_number

                    ; stringify operand so I can print it to debug.
                    arrange opstr, operand
                    stringify opstr
                    display opstr bappend 9

                    ; default values
                    compute type, 'unknown'


            ;; Check if operand is an immediate value;;;;;;;;;;;;;;;;;;;;;;;;;;;
                    match =# maybe_number, operand
                    jno check_if_absolute
            ; hash_prefix:
                    ; display 'hash prefix' bappend 10
                    check maybe_number eqtype 0
                    jyes skip_immediate_addressing_error
                    err 'immediate_addressing_error' ; TODO: better err message.
                skip_immediate_addressing_error:
                    compute type, 'imm'
                    display 'imm' bappend 10
                    exit
            ;; Check if absolute addressing ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            check_if_absolute:
                    ; display 'no hash prefix' bappend 10
                    check operand relativeto 0
                    jno check_if_dn
                    compute type, 'abs'
                    display 'abs' bappend 10
                    exit
            ;; Check if `dn` (direct data register addressing) ;;;;;;;;;;;;;;;;;
            check_if_dn:
                    check operand relativeto m68k.data_reg
                    jno check_if_an
                    compute type, 'dn'
                    display 'dn' bappend 10
                    exit
            ;; Check if `an` (direct address register addressing) ;;;;;;;;;;;;;;
            check_if_an:
                    check operand relativeto m68k.address_reg
                    jno unknown
                    compute type, 'an'
                    display 'an' bappend 10
                    exit
            ;; Check if `(an)` (indirect address register addressing) ;;;;;;;;;;
            check_if_indirect_an:


            ;; Temporary stuff ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            unknown:
                    compute type, 'unknown'
                    display 'unknown' bappend 10
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
;; 68000 instruction set implemented in fasmg                                 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "niladic.inc"
include "monadic.inc"
include "dyadic.inc"
include "variadic.inc"

;; Just an test instruction to test all the addressing modes and stuff ;;;;;;;;;

calminstruction parse_operand? op
    call m68k.parse_operand@op1, op
end calminstruction