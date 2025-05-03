# Motorola 68000 Instruction Set for Flat Assembler G

`parse_operand` must be run on all operands before any byte is emitted! The
reason for this has to do with pc-relative addressing modes.