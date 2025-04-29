; TODO: Should this file be in a different folder?

; TODO: Comment what this does and why it is needed.
; Supposed to be called
; See where this is used in `parse_operand`.
; This function is needed when extension words are emitted,
; because of "pc relative addressing modes" which causes some headache.
calminstruction emit_ext_words? ext_bytes*, ext_bytes_bits*
         ; TODO: Better name. Is pc where head of instruction is.
        local old_pc
        ; TODO: Better name. If this is the first ext word then it is 2.
        ;       If it is the 2nd ext word then it depends upon how many bytes
        ;       the ext words of the first operand has.
        ;       i.e. old_pc + bytes_into_instruction is the address of
        ;       where exactly this word is (will be emitted).
        local bytes_into_instruction

        ; Take out old $ baked into ext_bytes_bits
        ; TODO: Explain better.
        compute old_pc, 1 scaleof ext_bytes_bits
        check old_pc > 0
        jno skip
        compute bytes_into_instruction, $ - old_pc
        ; bswap is needed because fasmg outputs in little-endian
        emit ext_bytes, (old_pc - bytes_into_instruction - (0 scaleof ext_bytes_bits)) bswap ext_bytes
        jump done
    skip:
        ; bswap is needed because fasmg outputs in little-endian
        ; emit ext_bytes, ext_bytes_bits bswap ext_bytes
        emit ext_bytes, ext_bytes_bits bswap ext_bytes
    done:
end calminstruction