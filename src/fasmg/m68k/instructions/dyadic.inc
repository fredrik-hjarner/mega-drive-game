;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 dyadic instructions                                         ;;
;;                                                                            ;;
;; | # | instruction | implemented | tested | notes                         | ;;
;; |---|-------------|-------------|--------|-------------------------------| ;;
;; |   | movem.[wl]  |             |        |                               | ;;
;; |   | or          | ~           | ~      |                               | ;;
;; |   | move        |             |        | split move into it's variants | ;;
;; |   |             |             |        |                               | ;;
;; |   | dbcc.w      | ~           | ~      |                               | ;;
;; |   | movea       | ~           | ~      |                               | ;;
;; |   | lea         | ~           | ~      |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   | ori.[bwl]   | ~           | ~      |                               | ;;
;; |   | andi.[bwl]  | ~           | ~      |                               | ;;
;; |   | subi.[bwl]  | ~           | ~      |                               | ;;
;; |   | addi.[bwl]  | ~           | ~      |                               | ;;
;; |   | eori.[bwl]  | ~           | ~      |                               | ;;
;; |   | cmpi.[bwl]  | ~           | ~      |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   | addq.[bwl]  | ~           | ~      |                               | ;;
;; |   | subq.[bwl]  | ~           | ~      |                               | ;;
;; |   |             |             |        |                               | ;;
;; |   | moveq       | ~           | ~      |                               | ;;
;; |   |             |             |        |                               | ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Placeholders for not yet implemented instructions ;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro movep.l line&
end macro
macro movep.w line&
end macro

macro link.w line&
end macro

macro chk.w line&
end macro




;sbcd
;sub
;subx
;suba
;eor
;cmpm
;cmp
;cmpa

macro abcd.b line&
end macro

macro exg.l line&
end macro

macro and.b line&
end macro
macro and.w line&
end macro
macro and.l line&
end macro

macro add.b line&
end macro
macro add.w line&
end macro
macro add.l line&
end macro

macro addx.b line&
end macro
macro addx.w line&
end macro
macro addx.l line&
end macro

macro adda.w line&
end macro
macro adda.l line&
end macro

;; DIVU, DIVS, MULU, MULS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     divs <ea>,dn
;     divu <ea>,dn
;     muls <ea>,dn
;     mulu <ea>,dn
iterate <instr,  first_byte>, \
        divu,    10000000b, \
        divs,    10000001b, \
        mulu,    11000000b, \
        muls,    11000001b

        calminstruction instr.w? ea*, dn*
            call m68k.parse_operand@op1, ea
            call m68k.parse_operand@op2, dn

            ; first byte
            emit 1, first_byte + (0 scaleof dn) shl 1

            ; second byte
            emit 1, 11000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits

            ; <ea> extension words
            ; bswap is needed because famg outputs in little-endian :'/
            emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes
        end calminstruction

end iterate ; <instr, first_byte>

;; BTST BCHG BCLR BSET ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     btst.[bl] dn,<ea>
;     btst.[bl] #<data>,<ea>
; Syntax:
;     bchg.[bl] dn,<ea>
;     bchg.[bl] #<data>,<ea>
; Syntax:
;     bclr.[bl] dn,<ea>
;     bclr.[bl] #<data>,<ea>
; Syntax:
;     bset.[bl] dn,<ea>
;     bset.[bl] #<data>,<ea>
; TODO: When looking at: http://goldencrystal.free.fr/M68kOpcodes-v2.3.pdf
;       I don't see how size .b/.l is encoded...??
iterate <instr,  instr_bits>, \
        btst,    00b, \
        bchg,    01b, \
        bclr,    10b, \
        bset,    11b
    ; TODO: I think the size_in_bytes is strange.
    ;       What even does .b and .l mean for these specific instructions?
    ;       I really need to figure this out, is it that the addressing mode
    ;       bits are changed, that seems reasonable? I require explicit .[bwl]
    ;       but maybe another assembler when .[bwl] is not input on <ea> it will
    ;       take the size from the instruction suffix.. yea that must be it.
    iterate <size, size_in_bytes>, \
             b,    2, \
             l,    2

        calminstruction instr.size? op1*, ea*
                local op1_bits
                local op1_type_bit
                local bit_index
                local bit_index_size

                ; Init default values
                compute op1_bits, 0 ; This is the value when op1 is imm
                compute op1_type_bit, 1000b ; This is the value when op1 is imm
                compute bit_index, 0
                compute bit_index_size, size_in_bytes ; This is the value when op1 is imm

                call m68k.parse_operand@op1, op1
                call m68k.parse_operand@op2, ea

                ; TODO: If I do compute and result is a boolean is that 0/1 then?
                ;       because if that's the case I could use that in places for
                ;       sure, it would sort of be like a ternary op in fasmg.
                ;   If type was a token instead of a value, the I suppose I
                ;   could use transform too, i.e. transform the type to 1 or 0.
                check @op1.type = 'dn'
            ; op1_is_dn
                jno op1_is_imm ; TODO: I mean I have not validated that though...
                ; compute op1_bits, (op1 - m68k.data_reg) shl 1
                compute op1_bits, (0 scaleof op1) shl 1 ; TODO: This is nicer?
                compute op1_type_bit, 1
                compute bit_index_size, 0
                jump emit_bytes
            op1_is_imm:
                compute bit_index, 0
            emit_bytes:

                ; first byte
                emit 1, op1_bits + op1_type_bit

                ; second byte
                emit 1, instr_bits shl 6 + @op2.ea_mode_bits shl 3 +  @op2.ea_reg_bits

                ; bit index
                ; bswap is needed because famg outputs in little-endian :'/
                emit bit_index_size, bit_index bswap bit_index_size

                ; <ea> extension words
                ; bswap is needed because famg outputs in little-endian :'/
                emit @op2.ext_bytes, @op2.ext_bytes_bits bswap @op2.ext_bytes
        end calminstruction

    end iterate ; <size, size_in_bytes>
end iterate ; <instr, instr_bits>

;; MOVEM ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

iterate <size,  size_bits>, \
        w,      0b, \
        l,      1b

        ; Syntax:
        ;     movem.[wl] <ea>,<register list>
        ;     movem.[wl] <register list>,<ea>
        calminstruction movem.size? op1*, op2*
                    display 10 bappend 'movem:' bappend 10

                    local direction
                    local bit_mask
                    local ea_mode_bits
                    local ea_reg_bits
                    local ext_bytes
                    local ext_bytes_bits

            ; Init default values
                    ; 0 means <register list> to <ea>
                    ; 1 means <ea>,<register list>
                    ; compute direction, 0
                    ; compute bit_mask, 0

                    call m68k.parse_reg_list@reg_list1, op1
                    call m68k.parse_reg_list@reg_list2, op2


            ; Figure out direction
                    check @reg_list1.is_reg_list = 1
                    jyes reglist_to_ea
            ; ea_to_reglist:
                    call m68k.parse_operand@op1, op1
                    compute direction, 1
                    ; TODO: Instead of doing all these twice for the 2 cases
                    ;       can I not `arrange ea, @op1 or something??
                    compute ea_mode_bits, @op1.ea_mode_bits
                    compute ea_reg_bits, @op1.ea_reg_bits
                    compute ext_bytes, @op1.ext_bytes
                    compute ext_bytes_bits, @op1.ext_bytes_bits
                    compute bit_mask, @reg_list2.mask_word
                    ; check if reverse mask should be used
                    check @op1.type = '-(an)'
                    jno skip_reverse1
                ; reverse:
                    compute bit_mask, @reg_list2.mask_word_reverse
                skip_reverse1: ; TODO: just jump to emit_bytes instead?
                    jump emit_bytes
            reglist_to_ea:
                    call m68k.parse_operand@op2, op2
                    compute direction, 0
                    compute ea_mode_bits, @op2.ea_mode_bits
                    compute ea_reg_bits, @op2.ea_reg_bits
                    compute ext_bytes, @op2.ext_bytes
                    compute ext_bytes_bits, @op2.ext_bytes_bits
                    compute bit_mask, @reg_list1.mask_word
                    ; check if reverse mask should be used
                    check @op2.type = '-(an)'
                    jno skip_reverse2
                ; reverse:
                    compute bit_mask, @reg_list1.mask_word_reverse
                skip_reverse2: ; TODO: just jump to emit_bytes instead?
            emit_bytes:

                    ; first byte
                    emit 1, 01001000b + direction shl 2

                    ; second byte
                    emit 1, 10000000b + size_bits shl 6 + ea_mode_bits shl 3 + ea_reg_bits

                    ; register list bit mask
                    ; bswap is needed because famg outputs in little-endian :'/
                    emit 2, bit_mask bswap 2

                    ; <ea> extension words
                    ; bswap is needed because famg outputs in little-endian :'/
                    ; emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes
                    emit ext_bytes, ext_bytes_bits bswap ext_bytes




            ;     local _size

            ;     ; TODO: I am not sure why I have to do this to get the call to work.
            ;     arrange _size, =size

            ;     call m68k.parse_operand@op1, op1, _size
            ;     call m68k.parse_operand@op2, op2, _size

            ;     ; TODO: This is a sloppy check, do a more complete check in the
            ;     ; future.
            ;     ; TODO: Is there anything such as ternary in fasmg? 
            ;     ; @op1.type = 'dn' ? 1 : 0
            ;     check @op2.type = 'dn'
            ;     jno dn_to_ea
            ; ; ea_to_dn:
            ;     ; first byte
            ;     emit 1, 10000000b + @op2.ea_reg_bits shl 1

            ;     ; second byte
            ;     emit 1, size_bits shl 6 + @op1.ea_mode_bits shl 3 +  @op1.ea_reg_bits

            ;     ; extension words
            ;     ; bswap is needed because famg outputs in little-endian :'/
            ;     emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes

            ;     exit
            ; dn_to_ea:
            ;     ; first byte
            ;     emit 1, 10000001b + @op1.ea_reg_bits shl 1

            ;     ; second byte
            ;     emit 1, size_bits shl 6 + @op2.ea_mode_bits shl 3 +  @op2.ea_reg_bits

            ;     ; extension words
            ;     ; bswap is needed because famg outputs in little-endian :'/
            ;     emit @op2.ext_bytes, @op2.ext_bytes_bits bswap @op2.ext_bytes
        end calminstruction

end iterate ; <size, size_bits>

iterate <size,  size_bits>, \
        b,      00b, \
        w,      01b, \
        l,      10b

        ; Syntax:
        ;     or.[bwl] <ea>,dn
        ;     or.[bwl] dn,<ea>
        calminstruction or.size? op1*, op2*
                display 10 bappend 'or:' bappend 10

                local _size

                ; TODO: I am not sure why I have to do this to get the call to work.
                arrange _size, =size

                call m68k.parse_operand@op1, op1, _size
                call m68k.parse_operand@op2, op2, _size

                ; TODO: This is a sloppy check, do a more complete check in the
                ; future.
                ; TODO: Is there anything such as ternary in fasmg? 
                ; @op1.type = 'dn' ? 1 : 0
                check @op2.type = 'dn'
                jno dn_to_ea
            ; ea_to_dn:
                ; first byte
                emit 1, 10000000b + @op2.ea_reg_bits shl 1

                ; second byte
                emit 1, size_bits shl 6 + @op1.ea_mode_bits shl 3 +  @op1.ea_reg_bits

                ; extension words
                ; bswap is needed because famg outputs in little-endian :'/
                emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes

                exit
            dn_to_ea:
                ; first byte
                emit 1, 10000001b + @op1.ea_reg_bits shl 1

                ; second byte
                emit 1, size_bits shl 6 + @op2.ea_mode_bits shl 3 +  @op2.ea_reg_bits

                ; extension words
                ; bswap is needed because famg outputs in little-endian :'/
                emit @op2.ext_bytes, @op2.ext_bytes_bits bswap @op2.ext_bytes
        end calminstruction

end iterate ; <size, size_bits>

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; START MOVE INSTRUCTIONS                                                    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro calminstruction?.move_macro? op1*, op2*, size*
        display 10 bappend 'move.l:' bappend 10

        local _size

        ; TODO: I am not sure why I have to do this to get the `call` to work...
        arrange _size, =size

        call m68k.parse_operand@op1, op1, _size
        call m68k.parse_operand@op2, op2, _size

        ; TODO: This checks could be more complete.
        check @op1.type = 'sr'
        jyes sr_to_ea
        check @op2.type = 'ccr'
        jyes ea_to_ccr
        check @op2.type = 'sr'
        jyes ea_to_sr
        check @op1.type = 'usp'
        jyes usp_to_an
        check @op2.type = 'usp'
        jyes an_to_usp
        jump ea_to_ea

    sr_to_ea:
        display 'sr_to_ea' bappend 10
        jump done
    ea_to_ccr:
        display 'ea_to_ccr' bappend 10
        jump done
    ea_to_sr:
        call move_ea_to_sr, _size
        jump done
    usp_to_an:
        display 'usp_to_an' bappend 10
        jump done
    an_to_usp:
        display 'an_to_usp' bappend 10
        jump done
    ea_to_ea:
        call move_ea_to_ea, _size
        jump done
    done:
end macro

; TODO: move.[bwl] prolly should use `macro calminstruction?.` extensions that
; can be in the .[bwl] variants reused
; Syntax:
;     move.w     sr,   <ea>
;     move.w     <ea>, ccr
;     move.w     <ea>, sr
;     move.l     usp,  an
;     move.l     an,   usp
;     move.[bwl] <ea1>, <ea2>
calminstruction move.b? op1*, op2*
        move_macro op1, op2, b
end calminstruction
calminstruction move.w? op1*, op2*
        move_macro op1, op2, w
end calminstruction
calminstruction move.l? op1*, op2*
        move_macro op1, op2, l
end calminstruction

; TODO: Comment
; For move_ea_to_ea specifically!
define m68k.move_size_bits
define m68k.move_size_bits.b 01b
define m68k.move_size_bits.w 11b
define m68k.move_size_bits.l 10b

; Supposed to be call:ed.
; Assume that ea1 and ea2 has already been parsed with `parse_operand` and are
; available on @op1 and @op2.
calminstruction move_ea_to_ea size*
        ; display 'ea_to_ea' bappend 10

        local size_bits

        arrange size_bits, size
        transform size_bits, m68k.move_size_bits
        jyes skip_size_error
        err "size error" ; TODO: Better error message
    skip_size_error:
        ; emit 1st and 2nd byte in one go
        ; bswap is needed because famg outputs in little-endian :'/
        emit 2, (size_bits shl 12 + @op2.ea_reg_bits shl 9 + @op2.ea_mode_bits shl 6 + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits) bswap 2

        ; op1 extension words
        emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes

        ; op2 extension words
        emit @op2.ext_bytes, @op2.ext_bytes_bits bswap @op2.ext_bytes
end calminstruction

; Supposed to be call:ed.
; Assume that op1 and op2 has already been parsed with `parse_operand` and are
; available on @op1 and @op2.
; TODO: Warn/error when .b and .l, only .w allowed, & restrict addressing modes.
calminstruction move_ea_to_sr size*
        ; display 'ea_to_sr' bappend 10

        ; first byte
        emit 1, 01000110b

        ; second byte
        emit 1, 11000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits 

        ; op1 extension words
        ; bswap is needed because famg outputs in little-endian :'/
        ; TODO: This specific part is duplicated many times so should have macro
        ;       maybe called `emit_extension_word@op1/op2`
        ;       though that does not seem to save much space...
        emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes
end calminstruction

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; END MOVE INSTRUCTIONS                                                      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;   dbcc.w Dn,<label>
;
; TODO: What exactly does label and literal mean in this context?
; TODO: Add the different aliases for the conditions.
; Aliases:
;     ra = f
;     hs = cc
;     lo = cs
iterate <cc,  cc_bits>, \
        \ ; True
        t,      0000b, \
        \ ; False
        f,      0001b, \
        \ ; Alias for f
        ra,     0001b, \
        \ ; 
        hi,     0010b, \
        \ ; 
        ls,     0011b, \
        \ ; 
        cc,     0100b, \
        \ ; Alias for cc
        hs,     0100b, \
        \ ; 
        cs,     0101b, \
        \ ; Alias for cs
        lo,     0101b, \
        \ ; 
        ne,     0110b, \
        \ ; 
        eq,     0111b, \
        \ ; 
        vc,     1000b, \
        \ ; 
        vs,     1001b, \
        \ ; 
        pl,     1010b, \
        \ ; 
        mi,     1011b, \
        \ ; 
        ge,     1100b, \
        \ ; 
        lt,     1101b, \
        \ ; 
        gt,     1110b, \
        \ ; 
        le,     1111b

        ; TODO: Check if displacement fits a in word.
        ; Maybe do that in parse_operand?
        ; Also, check if displacement is a valid displacement.
        ; 0 is not allowed for .b I think.
        calminstruction? db#cc.w? dn*, label*
            local pc

            call m68k.parse_operand@op1, dn
            ; call m68k.parse_operand@op2, label

            compute pc, $ + 2

            ; first byte
            emit 1, 01010000b + cc_bits

            ; second byte
            emit 1, 11001000b + @op1.ea_reg_bits

            ; immediate word
            ; bswap is needed because famg outputs in little-endian :'/
            emit 2, (label - pc) bswap 2
        end calminstruction

end iterate ; <cc, cc_bits>

; TODO: Comment
; Syntax:
;     movea.[wl] <ea>,an
iterate <size,  size_bits>, \
        w,      11b, \
        l,      10b

        calminstruction movea.size? ea*, an*
            display 10 bappend 'movea:' bappend 10

            local tmp
            arrange tmp, =size

            call m68k.parse_operand@op1, ea, tmp
            call m68k.parse_operand@op2, an

            ; first byte
            emit 1, size_bits shl 4 + @op2.ea_reg_bits shl 1

            ; second byte
            emit 1, 01000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits
                        
            ; extension words
            ; bswap is needed because famg outputs in little-endian :'/
            ; TODO: So, seems the number of extension words depend upon .w,.l
            ;       IN THE SPECIFIC CASE OF IMMEDITE OPERANDS this complicated
            ;       the implementation of parse_operands a bit.
            emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes
        end calminstruction

end iterate ; <size, size_bits>

; TODO: Comment
calminstruction lea.l? ea*, an*
    display 10 bappend 'lea:' bappend 10

    call m68k.parse_operand@op1, ea
    call m68k.parse_operand@op2, an

    ; first byte
    emit 1, 01000001b + @op2.ea_reg_bits shl 1

    ; second byte
    emit 1, 11000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits
                
    ; extension words
    ; bswap is needed because famg outputs in little-endian :'/
    emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes
end calminstruction

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     ori.[bwl]  #<data>,<ea>
;     andi.[bwl] #<data>,<ea>
;     subi.[bwl] #<data>,<ea>
;     addi.[bwl] #<data>,<ea>
;     eori.[bwl] #<data>,<ea>
;     cmpi.[bwl] #<data>,<ea>
; Addressing modes:
;     Dn  An  (An)  (An)+  ‑(An)  (d,An)  (d,An,Xi) 
;      ✓       ✓     ✓       ✓      ✓         ✓ 
;     ABS.W  ABS.L  (d,PC)  (d,PC,Xn)  imm
;       ✓     ✓           
; TODO: Double check addressing modes for each instruction.
iterate <instr,  first_byte>, \
        \ ; Or Immediate
        ori,     00000000b, \
        \ ; And Immediate
        andi,    00000010b, \
        \ ; Subtract Immediate
        subi,    00000100b, \
        \ ; Add Immediate
        addi,    00000110b, \
        \ ; Exclusive Or Immediate
        eori,    00001010b, \
        \ ; Compare Immediate
        cmpi,    00001100b,
    ; TODO: Can I remove the imm_bytes now and use the stuff from
    ; parse_operand instread?
    iterate <size,  size_bits,  imm_bytes>, \
            b,      00b,        2, \
            w,      01b,        2, \
            l,      10b,        4

            calminstruction instr.size? imm*, ea*
                local tmp

                call m68k.parse_operand@op1, imm
                call m68k.parse_operand@op2, ea

                ; TODO: Assert that imm is within bounds.
                ; assert_min imm, 1
                ; assert_max imm, 8

                ; first byte
                emit 1, first_byte

                ; second byte
                emit 1, size_bits shl 6 + @op2.ea_mode_bits shl 3 + @op2.ea_reg_bits
                
                ; immediate bytes
                ; bswap is needed because famg outputs in little-endian :'/
                emit imm_bytes, @op1.imm bswap imm_bytes

                ; extension words
                ; bswap is needed because famg outputs in little-endian :'/
                emit @op2.ext_bytes, @op2.ext_bytes_bits bswap @op2.ext_bytes
            end calminstruction

    end iterate ; <size, size_bits>
end iterate ; <instr, first_byte>

; Syntax:
;     addq #<data>,<ea>
;     subq #<data>,<ea>
; Addressing modes:
;     Dn  An  (An)  (An)+  ‑(An)  (d,An)  (d,An,Xi) 
;      ✓   ✓   ✓     ✓       ✓      ✓         ✓ 
;     ABS.W  ABS.L  (d,PC)  (d,PC,Xn)  imm
;       ✓     ✓                 
; TODO: Restrict to valid addressing modes for the instructions.
; Valid imm range: 1-8 (8 is encoded as 000b i.e. 0).
iterate <instr,  first_byte>, \
        \ ; Add Quick
        addq,    01010000b, \
        \ ; Subtract Quick
        subq,    01010001b
    iterate <size,  size_bits>, \
            b,      00b, \
            w,      01b, \
            l,      10b

            calminstruction instr.size? imm*, ea*
                local tmp

                call m68k.parse_operand@op1, imm
                call m68k.parse_operand@op2, ea

                assert_min imm, 1
                assert_max imm, 8

                ; first byte
                ; 8 is encoded as 000b
                compute tmp, imm mod 8 ; TODO: Is this compute needed?
                emit 1, first_byte + tmp shl 1

                ; second byte
                emit 1, size_bits shl 6 + @op2.ea_mode_bits shl 3 + @op2.ea_reg_bits
                
                ; extension words
                ; bswap is needed because famg outputs in little-endian :'/
                emit @op2.ext_bytes, @op2.ext_bytes_bits bswap @op2.ext_bytes
            end calminstruction

    end iterate ; <size, size_bits>
end iterate ; <instr, first_byte>

; Description:
;     Move the literal to a data register. The literal data is an
;     eight-bit signed value (-128 to +127). The literal is sign-extended
;     to 32 bits to cover the whole of the data register.
; Arguments:
;     data: 0000_0000 - 1111_1111
;     dn: d0 - d7
; TODO: Test.
; TODO: Give error if data is out of range.
; TODO: Handle # character.
; TODO: Validate that dn is a data register.
; TODO: Figure out how to work with signed numbers so it works with
;       whatever formats you can use in normal m68k assemblers
;       I assume 1111_1111b and -1d are should both be allowed?!
calminstruction moveq.l? data*, dn*
    local tmp

    call m68k.parse_operand@op1, data
    call m68k.parse_operand@op2, dn

    assert_data_reg dn

    ; 0 1 2 3 4  5  6  7
    ; 0 1 1 1 dn dn dn 0
    compute tmp, 01110000b + ((dn - m68k.data_reg) shl 1) 
    emit 1, tmp
    compute tmp, data
    emit 1, tmp
end calminstruction