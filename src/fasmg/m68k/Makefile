.PHONY: all clown build clownassembler hexdump clean

all: build hexdump

clown: clownassembler hexdump

vasm: build_vasm hexdump

# clownassembler runs `valid_instructions.asm` directly while fasmg runs a wrapper
# file that includes the m68k instruction set.
# The reason is that * is not supported in fasmg and I don't know if I can
# make it supported, in fasmg $ is used instead. I use @ as a kind of
# "middle-ground" since it is almost the same as * in clownassembler and I can
# easily have `@ equ $` in fasmg.
clownassembler:
	clownassembler -c -o tests/test.bin -i tests/valid_instructions.asm

build_vasm:
	vasm -Fbin -spaces -wfail -o tests/test.bin tests/test.asm

build:
	fasmg tests/test.asm tests/test.bin -e20

build2:
	fasmg tests/test2.asm tests/test2.bin -e20

hexdump:
	xxd -b -c1 tests/test.bin | cut -d' ' -f2,4 > tests/test.hex
#  hexdump -v -e '/1 "%02x\n"' tests/test.bin > tests/test.hex

clean:
	rm -f tests/test.bin tests/test.hex


