; Shamelessly stolen from here:
; https://board.flatassembler.net/topic.php?p=242936#242936
; Adjusted to work with vasm m68k.

macro emit? line&
    ; vasm needs equs to not be prefixed with whitespace.
    ; vasm needs other stuff to be prefixed with whitespace.
    match a= =equ= b, line
    else match c= =macro, line
    else
        db 20h, 20h, 20h, 20h
    end match
    db `line,13,10
end macro

define MACROS

; The macros to be preprocessed go here
namespace MACROS
    include "format_clownassembler.inc"
    include "macros.inc"
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