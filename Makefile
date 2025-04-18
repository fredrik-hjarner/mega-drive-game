.PHONY: all preprocess build-preprocessed build hexdump run clean

all: preprocess build-preprocessed hexdump

preprocess:
	fasmg src/fasmg/preprocess.asm -isource=\'src/main.asm\' preprocessed.asm -e100

build-preprocessed:
	clownassembler -c -l main.lst -o main.bin -i preprocessed.asm

# build:
# 	clownassembler -c -l main.lst -o main.bin -i main.asm

hexdump:
	hexdump -C -v main.bin > main.hex

run:
	cd ~/Downloads/Exodus_2.1 && wine exodus

clean:
	rm -f main.bin main.hex main.lst preprocessed.asm


