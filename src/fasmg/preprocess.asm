define preprocess_asm

; Shamelessly stolen from here:
; https://board.flatassembler.net/topic.php?p=242936#242936
; Adjusted to work with vasm m68k.

macro emit? line&
    ; vasm needs equs to not be prefixed with whitespace.
    ; vasm needs other stuff to be prefixed with whitespace.
    match a= =equ= b, line
    else match a= =macro, line
    else match a= =rs.b c, line
    else
        db 20h, 20h, 20h, 20h
    end match
    db `line,13,10
end macro

; _assemble emits text to for either clownassembler or fasm68k to assemble.
macro calminstruction?._assemble? &line&
    stringify line
    ; clownassembler stuff usually needs to be prefixed with whitespace.
    emit 1, 20h
    emit 1, 20h
    emit 1, 20h
    emit 1, 20h
    emit lengthof line, line
    emit 1, 13
    emit 1, 10
end macro

; TODO: Maybe I can match to see if it contains equ etc. here like macro above?
macro calminstruction?.assemble_first_column? &line&
    stringify line
    ; In vasm labels need to NOT be prefixed with whitespace.
    emit lengthof line, line
    emit 1, 13
    emit 1, 10
end macro

; These different versions of emit are needed. Couldn't solve it in another way.
; They intend to output text that can later be assembled by either
; clownassembler or fasm68k.
macro calminstruction?._emit_word? number_of_bytes, value
    local _tmp
    compute _tmp, +(value bswap 2) ; convert to number in case it is a string.
    arrange _tmp, _tmp
    stringify _tmp
    emit 9, '    dc.w ' 
    emit lengthof _tmp, _tmp
    emit 1, 10
end macro
macro calminstruction?._emit_str? number_of_bytes, value
    emit 9, '    dc.b ' 
    emit 1, ''''
    emit number_of_bytes, value
    emit 1, ''''
    emit 1, 10
end macro

define MACROS

; The macros to be preprocessed go here
namespace MACROS
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