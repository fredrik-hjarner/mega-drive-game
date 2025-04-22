;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 niladic instructions                                        ;;
;;                                                                            ;;
;; | # | instruction | implemented | tested | notes                         | ;;
;; |---|-------------|-------------|--------|-------------------------------| ;;
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

;; Some placeholders ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro move.b line&
end macro
macro move.w line&
end macro

macro or.b line&
end macro
macro or.w line&
end macro
macro or.l line&
end macro

macro movem.l line&
end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; END MOVE INSTRUCTIONS                                                      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO: move.[bwl] prolly should use `macro calminstruction?.` extensions that
; can be in the .[bwl] variants reused
; Syntax:
;     move.w     sr,   <ea>
;     move.w     <ea>, ccr
;     move.w     <ea>, sr
;     move.l     usp,  an
;     move.l     an,   usp
;     move.[bwl] <ea1>, <ea2>
calminstruction move.l? op1*, op2*
        display 10 bappend 'move.l:' bappend 10

        local size

        ; TODO: I am not sure why I have to do this to get the `call` to work...
        arrange size, =l

        call m68k.parse_operand@op1, op1, size
        call m68k.parse_operand@op2, op2, size

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
        display 'ea_to_sr' bappend 10
        jump done
    usp_to_an:
        display 'usp_to_an' bappend 10
        jump done
    an_to_usp:
        display 'an_to_usp' bappend 10
        jump done
    ea_to_ea:
        call move_ea_to_ea, size
        jump done
    done:
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
        _emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes

        ; op2 extension words
        _emit @op2.ext_bytes, @op2.ext_bytes_bits bswap @op2.ext_bytes
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
            _emit 1, 01010000b + cc_bits

            ; second byte
            _emit 1, 11001000b + @op1.ea_reg_bits

            ; immediate word
            ; bswap is needed because famg outputs in little-endian :'/
            _emit 2, (label - pc) bswap 2
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
            _emit 1, size_bits shl 4 + @op2.ea_reg_bits shl 1

            ; second byte
            _emit 1, 01000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits
                        
            ; extension words
            ; bswap is needed because famg outputs in little-endian :'/
            ; TODO: So, seems the number of extension words depend upon .w,.l
            ;       IN THE SPECIFIC CASE OF IMMEDITE OPERANDS this complicated
            ;       the implementation of parse_operands a bit.
            _emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes
        end calminstruction

end iterate ; <size, size_bits>

; TODO: Comment
calminstruction lea.l? ea*, an*
    display 10 bappend 'lea:' bappend 10

    call m68k.parse_operand@op1, ea
    call m68k.parse_operand@op2, an

    ; first byte
    _emit 1, 01000001b + @op2.ea_reg_bits shl 1

    ; second byte
    emit 1, 11000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits
                
    ; extension words
    ; bswap is needed because famg outputs in little-endian :'/
    _emit @op1.ext_bytes, @op1.ext_bytes_bits bswap @op1.ext_bytes
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
                _emit 1, first_byte

                ; second byte
                _emit 1, size_bits shl 6 + @op2.ea_mode_bits shl 3 + @op2.ea_reg_bits
                
                ; immediate bytes
                ; bswap is needed because famg outputs in little-endian :'/
                _emit imm_bytes, @op1.imm bswap imm_bytes

                ; extension words
                ; bswap is needed because famg outputs in little-endian :'/
                _emit @op2.ext_bytes, @op2.ext_bytes_bits bswap @op2.ext_bytes
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
                _emit 1, first_byte + tmp shl 1

                ; second byte
                _emit 1, size_bits shl 6 + @op2.ea_mode_bits shl 3 + @op2.ea_reg_bits
                
                ; extension words
                ; bswap is needed because famg outputs in little-endian :'/
                _emit @op2.ext_bytes, @op2.ext_bytes_bits bswap @op2.ext_bytes
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
calminstruction moveq? data*, dn*
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
define moveq +moveq