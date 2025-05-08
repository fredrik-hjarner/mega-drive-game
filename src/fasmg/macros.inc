; INIT
; this command can be used to give an initial numeric value to local variable
; at the time when the CALM instruction is defined
calminstruction calminstruction?.init? var*, val:0
	compute val, val
	publish var, val
end calminstruction


; Unique labels in CALM with `new` and `@`.
; From https://board.flatassembler.net/topic.php?p=234192#234192
; Example:
;     macro calminstruction?.dispsymbol? sym
;             new empty
;             new cont
;             match , sym
;             @ jyes empty
;             display '<not empty>'
;             @ jump cont
;         @ empty:
;             display '<empty>'
;         @ cont:
;     end macro
;     calminstruction test arg1
;             dispsymbol arg1
;     end calminstruction
define ___loc? ___loc?
calminstruction calminstruction?.new? name*
        local   new, i
        init    i, 0
        compute i, i+1
        arrange new, name#i
        arrange name, ___loc.name
        publish name, new
end calminstruction
calminstruction calminstruction?.@? statement&
        transform statement, ___loc
        assemble statement
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
    arrange cmd,=move.=w #res,=vdp_ctrl.=l
    _assemble cmd
end calminstruction

calminstruction meta_version
        local tmp, quote, s_since_2025, m_since_2025

        arrange quote, '

        compute tmp, __time__
        compute s_since_2025, tmp - 1735686000
        compute m_since_2025, s_since_2025 / 60
        check defined preprocess_asm
        jyes preprocess_asm
    ; normal case
        arrange tmp, =GM m_since_2025
        stringify tmp
        _emit lengthof tmp, tmp
        exit
    preprocess_asm:
        arrange tmp, =dc.=b quote=GM m_since_2025 quote
        _assemble tmp
end calminstruction

; TODO: Explain exactly what this does and how it is intended to be used.
; arguments:
;     r: 0-7
;     g: 0-7
;     b: 0-7
; TODO: The name kinda sucks.
; TODO: This would be better as an inline fasmg macro.
calminstruction set_palette_color? r, g, b
    local tmp
    ; bbb0 ggg0 rrr0
    compute tmp, (b shl 9) or (g shl 5) or (r shl 1)
    arrange tmp, =move.=w= =#tmp,=vdp_data.=l
    _assemble tmp
end calminstruction
define set_palette_color +set_palette_color

; arguments:
;     addr: address: $0000-$FFFF
; https://segaretro.org/Sega_Mega_Drive/VDP_general_usage
calminstruction set_write_vram? addr
    local tmp
    ; TODO: compute does not work here because it can't work in preprocess.asm.
    ; compute tmp, $40000000 + ((addr and $3FFF) shl 16)+((addr and $C000) shr 14)
    arrange tmp, =move.=l= =#$40000000+(((addr)&$3FFF)<<16)+(((addr)&$C000)>>14),=vdp_ctrl.=l
    _assemble tmp
end calminstruction
define set_write_vram +set_write_vram

; arguments:
;     addr: address: $00-$FF
; https://segaretro.org/Sega_Mega_Drive/VDP_general_usage
calminstruction set_write_vsram? addr
    local tmp
    ; TODO: compute does not work here because it can't work in preprocess.asm.
    ; compute tmp, $40000010+((addr)<<16)
    arrange tmp, =move.=l= =#$40000010+((addr)<<16),=vdp_ctrl.=l
    _assemble tmp
end calminstruction
define set_write_vsram +set_write_vsram

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
define set_vdp_register +set_vdp_register
define meta_version +meta_version