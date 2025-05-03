;; Just instructions for testing addressing modes and stuff ;;;;;;;;;;;;;;;;;;;;

; TODO: Remove when not needed or move to test.asm?
calminstruction parse_operand? op
    call m68k.parse_operand@op1, op
end calminstruction

; TODO: Remove when not needed or move to test.asm?
calminstruction parse_reg_list? op
    call m68k.parse_reg_list@reg_list1, op
end calminstruction

; TODO: Remove when not needed or move to test.asm?
calminstruction parse_indirect_displacement? op
    call m68k.parse_indirect_displacement, op
end calminstruction

; TODO: Remove when not needed or move to test.asm?
calminstruction parse_pc_index? op
    call m68k.parse_pc_index, op
end calminstruction