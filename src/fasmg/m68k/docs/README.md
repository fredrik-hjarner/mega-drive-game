# Motorola 68000 Instruction Set for Flat Assembler G

I am trying to make a m68k instruction set for fasmg.

`parse_operand` must be run on all operands before any byte is emitted! The
reason for this has to do with pc-relative addressing modes.

## Strangeness

I run it in a weird way. Since it will take a long time to make the whole
instruction set I am trying to make "instruction per instruction". The way I
attempt to do that is to have two "modes": one mode to generate binary directly
with fasmg alone, another mode to use fasmg as a preprocessor to generate "text"
that then clownassembler assembles.

The generated file "preprocessed.asm" is the output from fasmg that then
clownassembler assembles.

## Current hacks

### Overriding `emit` and `assemble`

Obviuosly the `emit` and `assemble` will have been needed top be changed to
support the two "modes". For example `emit` normally emits raw binary that for
clownassembler mode I instead output a string like `dc.b 12` so that then
clownassembler will make that into binary so to speak.

TODO: Explain more!