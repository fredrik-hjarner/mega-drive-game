; Shamelessly stolen from here:
; https://board.flatassembler.net/topic.php?p=242936#242936
; Adjusted to work with vasm m68k.

macro emit? line&
    ; vasm needs equs to not be prefixed with whitespace.
    ; vasm needs other stuff to be prefixed with whitespace.
    match a= =equ= b, line
    else
        db 20h, 20h, 20h, 20h
    end match
    db `line,13,10
end macro

define MACROS

; The macros to be preprocessed go here
namespace MACROS
    macro calminstruction?.assemble? &line&
        stringify line
        ; TODO: Shoten this code?
        ; vasm stuff usually needs to be prefixed with whitespace.
        emit 1, 20h
        emit 1, 20h
        emit 1, 20h
        emit 1, 20h
        emit lengthof line, line
        emit 1, 13
        emit 1, 10
    end macro

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

    ; faster enter
    calminstruction @enter
        local tmp
        arrange tmp, =push =bp
        assemble tmp
        arrange tmp, =mov =bp, =sp
        assemble tmp
    end calminstruction

    calminstruction @pushall
        local tmp
        arrange tmp, =pushad
        assemble tmp
        arrange tmp, =push =ds
        assemble tmp
        arrange tmp, =push =es
        assemble tmp
    end calminstruction

    calminstruction @popall
        local tmp
        arrange tmp, =pop =es
        assemble tmp
        arrange tmp, =pop =ds
        assemble tmp
        arrange tmp, =popad
        assemble tmp
    end calminstruction

    ; int 3
    ; so that I can do BPINT 3 in dosbox-x debugger.
    calminstruction @breakpoint
        local tmp
        arrange tmp, =int 3h
        assemble tmp
    end calminstruction

    iterate <__a, __b>, \
        a, na, \
        b, nb, \
        c, nc, \
        e, ne, \
        g, ng, \
        l, nl, \
        o, no, \
        p, np, \
        s, ns, \
        z, nz

        calminstruction @if#__a line&
                local tmp
                arrange tmp, =j=__b =@=f
                assemble tmp
                assemble line
                arrange tmp, =@=@:
                assemble tmp
        end calminstruction

        calminstruction @if#__b line&
                local tmp
                arrange tmp, =j=__a =@=f
                assemble tmp
                assemble line
                arrange tmp, =@=@:
                assemble tmp
        end calminstruction

        ; Make visible to the preprocessor
        define @if#__a +@if#__a
        define @if#__b +@if#__b
    end iterate

    ; Make visible to the preprocessor
    ; define bappend +bappend
    define word +word
    define @enter +@enter
    define @pushall +@pushall
    define @popall +@popall
    define @breakpoint +@breakpoint
end namespace

PREPROCESSOR := __FILE__

namespace PREPROCESSOR

        define symlinks include:macro:purge:if:else:end:namespace:__FILE__:PREPROCESSOR
        match include:macro:purge:if:else:end:namespace:__FILE__:PREPROCESSOR, symlinks

                macro preprocess file
                        local empty
                        macro empty.include?! file
                               include file
                        end macro
                        namespace empty
                                macro ? line&
                                        if __FILE__ = PREPROCESSOR
                                                purge ?
                                                line
                                        else
                                                namespace PREPROCESSOR
                                                        match +command, MACROS.line
                                                                command
                                                        else
                                                                emit line
                                                        end match
                                                end namespace
                                        end if
                                end macro
                                include file
                        end namespace
                end macro

        end match

        preprocess source

end namespace    