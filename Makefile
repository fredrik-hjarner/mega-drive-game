.PHONY: all build hexdump run clean

all: build hexdump

# -Fbin
#     Output formatless raw binary.
# 
# -spaces
#     Allow whitespace characters in the operand field. Otherwise a whitespace
#     could start the comment field there.
build:
	vasm -Fbin -spaces -o main.bin main.asm

hexdump:
	hexdump -C -v main.bin > main.hex

run:
	cd ~/Downloads/Exodus_2.1 && wine exodus

clean:
	rm -f main.bin main.hex


