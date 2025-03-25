.PHONY: all preprocess build hexdump run clean

all: preprocess build hexdump

preprocess:
	fasm2 fasmg/preprocess.asm -isource=\'main.asm\' preprocessed.asm -e200

# -Fbin
#     Output formatless raw binary.
# 
# -spaces
#     Allow whitespace characters in the operand field. Otherwise a whitespace
#     could start the comment field there.
build:
	vasm -Fbin -spaces -o main.bin preprocessed.asm

hexdump:
	hexdump -C -v main.bin > main.hex

run:
	cd ~/Downloads/Exodus_2.1 && wine exodus

clean:
	rm -f main.bin main.hex


