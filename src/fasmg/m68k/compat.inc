; even exists in m68k assemblers it seems so I need it kinda.
macro even
    align 2
end macro

; TODO: Dunno what a good name for this is.
; Example:
;     input:  (((l1)  &  $3FFF) <<  16) + (((l1)  &  $C000) >>  14)
;     output: (((l1) and $3FFF) shl 16) + (((l1) and $C000) shr 14)
macro calminstruction?.replace_legacy_operators? expr*
    ;; Replace << with shl ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    next_shl:
        match a? =<=< b?, expr
        jno done_shl
        arrange expr, a =shl b
        jump next_shl
    done_shl:

    ;; Replace >> with shr ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    next_shr:
        match a? =>=> b?, expr
        jno done_shr
        arrange expr, a =shr b
        jump next_shr
    done_shr:

    ;; Replace & with and ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    next_and:
        match a? =& b?, expr
        jno done_and
        arrange expr, a =and b
        jump next_and
    done_and:

    ; Display the results of the transformations
        ; local expr_str
        ; arrange expr_str, expr
        ; stringify expr_str
        ; display expr_str bappend 10
        ; display expr_str bappend 10
        ; display expr_str bappend 10
        ; display expr_str bappend 10
        ; display expr_str bappend 10
        ; display expr_str bappend 10
        ; display expr_str bappend 10
end macro