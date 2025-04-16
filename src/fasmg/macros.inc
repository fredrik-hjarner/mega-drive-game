; macro calminstruction?.assemble? &line&
;     stringify line
;     ; TODO: Shoten this code?
;     ; vasm stuff usually needs to be prefixed with whitespace.
;     emit 1, 20h
;     emit 1, 20h
;     emit 1, 20h
;     emit 1, 20h
;     emit lengthof line, line
;     emit 1, 13
;     emit 1, 10
; end macro

; TODO: Name sucks.
; TODO: Maybe I can match to see if it contains equ here like macro above?
macro calminstruction?.assemble2? &line&
    stringify line
    ; In vasm labels need to NOT be prefixed with whitespace.
    emit lengthof line, line
    emit 1, 13
    emit 1, 10
end macro

; curr_var_addr stores where to place the next variable in RAM.
; It is initialized to the start of RAM.
curr_var_addr = $FF0000

; Declares a word variable in RAM.
calminstruction word var_name
    local tmp
    arrange tmp, var_name =equ= curr_var_addr
    assemble2 tmp
    ; increment the address for the next variable
    compute curr_var_addr, curr_var_addr + 2
end calminstruction

; Declares a byte variable in RAM.
calminstruction byte var_name
    local tmp
    arrange tmp, var_name =equ= curr_var_addr
    assemble2 tmp
    ; increment the address for the next variable
    compute curr_var_addr, curr_var_addr + 1
end calminstruction

; arguments:
;     reg_nr: register number: 0-23d
;     value:  value: 8 bits
calminstruction set_vdp_register reg_nr, value
    local set_reg
    local reg
    local res
    local cmd

    compute set_reg, 1 shl 15
    compute reg, reg_nr shl 8
    compute res, set_reg or reg or value
    arrange cmd,=move.=w #res,=vdp_ctrl
    _assemble cmd
end calminstruction

calminstruction meta_version
    local tmp, quote, s_since_2025, m_since_2025

    arrange quote, '

    compute tmp, __time__
    compute s_since_2025, tmp - 1735686000
    compute m_since_2025, s_since_2025 / 60

    arrange tmp, =dc.=b quote=GM m_since_2025 quote
    _assemble tmp
end calminstruction

; bappend
; Util macro for CALM to concatenate strings with shorter syntax.
; Only works when added to preprocess.asm
; Example:
;     calminstruction tester
;         local tmp, tmp2
;         bappend tmp, 13, 10
;         display tmp ; Output: empty line
;         bappend tmp, "a", "b", "c", 13, 10
;         display tmp ; Output: abc
;         compute tmp2, "$"
;         bappend tmp, tmp2, "a", "b", "c", 13, 10
;         display tmp ; Output: $abc
;     end calminstruction
;     tester
; OBSERVE! I managed to make a version of append that works without
; preprocess.asm so I am using that instead.
; macro bappend dest*, strings&
;     emit compute dest, ""
;     iterate string, strings
;         emit compute dest, dest bappend string
;     end iterate
; end macro

; Make visible to the preprocessor
; define bappend +bappend
define word +word
define byte +byte
define set_vdp_register +set_vdp_register
define meta_version +meta_version