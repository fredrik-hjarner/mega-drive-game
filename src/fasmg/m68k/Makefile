.PHONY: all build hexdump clean

all: build hexdump

build:
	fasm2 test.asm test.bin -e20

hexdump:
	hexdump -C -v test.bin > test.hex

clean:
	rm -f test.bin


