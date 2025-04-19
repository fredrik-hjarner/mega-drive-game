.PHONY: all clown build clownassembler hexdump clean

all: build hexdump

clown: clownassembler hexdump

clownassembler:
	clownassembler -c -o tests/test.bin -i tests/test.asm

build:
	fasmg tests/test.asm tests/test.bin -e20

hexdump:
	hexdump -C -v tests/test.bin > tests/test.hex

clean:
	rm -f tests/test.bin tests/test.hex


