.PHONY: all clown build clownassembler hexdump clean

all: build hexdump

clown: clownassembler hexdump

vasm: build_vasm hexdump

clownassembler:
	clownassembler -c -o tests/test.bin -i tests/test.asm

build_vasm:
	vasm -Fbin -spaces -wfail -o tests/test.bin tests/test.asm

build:
	fasmg tests/test.asm tests/test.bin -e20

hexdump:
	xxd -b -c1 tests/test.bin | cut -d' ' -f2,4 > tests/test.hex
#  hexdump -v -e '/1 "%02x\n"' tests/test.bin > tests/test.hex

clean:
	rm -f tests/test.bin tests/test.hex


