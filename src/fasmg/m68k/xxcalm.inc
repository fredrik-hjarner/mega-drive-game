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