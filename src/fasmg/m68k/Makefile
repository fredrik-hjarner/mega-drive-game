.PHONY: all clown build clownassembler hexdump clean

all: build hexdump

clown: clownassembler hexdump

clownassembler:
	clownassembler -c -o test.bin -i test.asm

build:
	fasm2 test.asm test.bin -e20

hexdump:
	hexdump -C -v test.bin > test.hex

clean:
	rm -f test.bin test.hex


