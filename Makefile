.PHONY: all preprocess build-preprocessed build-preprocessed-fasmg build hexdump run clean

all: preprocess build-preprocessed hexdump

preprocess:
	fasmg src/fasmg/preprocess.asm -isource=\'src/main.asm\' preprocessed.asm -e100

build-preprocessed:
	clownassembler -c -l main.lst -o main.bin -i preprocessed.asm

build-preprocessed-fasmg:
	fasmg preprocessed.asm main.bin -e10
	xxd -b -c1 main.bin | cut -d' ' -f2,4 > main.hex
# hexdump -C -v main.bin > main.hex

# build:
# 	clownassembler -c -l main.lst -o main.bin -i main.asm

hexdump:
	xxd -b -c1 main.bin | cut -d' ' -f2,4 > main.hex
# hexdump -C -v main.bin > main.hex

run:
	cd ~/Downloads/Exodus_2.1 && wine exodus

clean:
	rm -f main.bin main.hex main.lst preprocessed.asm


