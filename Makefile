.PHONY: all preprocess build-preprocessed build hexdump run clean

all: preprocess build-preprocessed hexdump

preprocess:
	fasm2 fasmg/preprocess.asm -isource=\'main.asm\' preprocessed.asm -e200

# -Fbin
#     Output formatless raw binary.
# 
# -spaces
#     Allow whitespace characters in the operand field. Otherwise a whitespace
#     could start the comment field there.
# -wfail
#     The return code of vasm will no longer be 0 (success), when there was a
#     warning. Errors always make the return code non-zero (failure).
build-preprocessed:
	vasm -Fbin -spaces -wfail -o main.bin preprocessed.asm

build:
	vasm -Fbin -spaces -wfail -o main.bin main.asm

hexdump:
	hexdump -C -v main.bin > main.hex

run:
	cd ~/Downloads/Exodus_2.1 && wine exodus

clean:
	rm -f main.bin main.hex


