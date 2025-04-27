; Supposed to be called
; Side-effects:
;     xxcalm.ret - 0 if false
;                  1 if true
calminstruction m68k.is_one_token? source_text*
    local a
    local b

    ; check_zero_tokens:
        match ,source_text
        jno check_more_than_one
        ; display "zero tokens" bappend 10 bappend 10
        compute xxcalm.ret, 0
        exit
    check_more_than_one:
        match a b,source_text
        jno is_one_token
        ; display "more than one tokens" bappend 10 bappend 10
        compute xxcalm.ret, 0
        exit
    is_one_token:
        ; display "one token" bappend 10 bappend 10
        compute xxcalm.ret, 1
end calminstruction

; Some temporary vars where return values are stored
; TODO: Think if there is a better cleaner way of doing this.
namespace m68k
    define ret_imm
    define ret_reg
end namespace

; Supposed to be callable.
; Side-effects:
;     m68k.ret_imm
;     m68k.ret_reg
;     xxcalm.ret - 0 if false
;                  1 if true
calminstruction m68k.parse_indirect_displacement operand*
        local tmp1
        local tmp2

        match tmp1(tmp2), operand
        jyes next
        ; display 'matched tmp1(tmp2)' bappend 10
        jump nope
    next:
        call m68k.is_one_token, tmp1
        jyup next2
        ; display 'tmp1 is one token' bappend 10
        jump nope
    next2:
        call m68k.is_one_token, tmp2
        jyup next3
        ; display 'tmp2 is one token' bappend 10
        jump nope
    next3:
        check tmp1 eqtype 0 & tmp2 relativeto m68k.address_reg
        jno nope
        compute xxcalm.ret, 1
        ; display 10 bappend "INDIRECT_DISPLACEMENT" bappend 10 bappend 10
        ; TODO: What would the different be if I used `publish` here?
        arrange m68k.ret_imm, tmp1
        arrange m68k.ret_reg, tmp2
        exit
    nope:
        compute xxcalm.ret, 0
end calminstruction
