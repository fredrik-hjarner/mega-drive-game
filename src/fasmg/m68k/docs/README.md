# Motorola 68000 Instruction Set for Flag Assembler G

I am trying to make a m68k instruction set for fasmg.

## Strangeness

I run it in a weird way. Since it will take a long time to make the whole
instruction set I am trying to make "instruction per instruction". The way I
attempt to do that is to have two "modes": one mode to generate binary directly
with fasmg alone, another mode to use fasmg as a preprocessor to generate "text"
that then clownassembler assembles.

The generated file "preprocessed.asm" is the output from fasmg that then
clownassembler assembles.

## Current hacks

### Transforming registers

I have had to do some hacks in order for both "modes" to work.
I place registers (d0-d7, a0-a7) in a namespace called m68k and then do a
transform in every calminstruction using data or address registers.

It looks something like this:

```
m68k.d0 equ d0
m68k.d1 equ d1
m68k.d2 equ d2
; etc
```

```
macro calminstruction?.asl? imm*, dn*
    transform dn, m68k ; TODO: Only for preprocess.inc!!
```

Somehow that makes `d0`, `d1`, `d2` etc. work in preprocess.inc.
That transform could probably be removed once the instructions set in completed
and the clownassembler mode is no longer needed.

### Overriding `emit` and `assemble`

Obviuosly the `emit` and `assemble` will have been needed top be changed to
support the two "modes". For example `emit` normally emits raw binary that for
clownassembler mode I instead output a string like `dc.b 12` so that then
clownassembler will make that into binary so to speak.

TODO: Explain more!