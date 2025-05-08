.PHONY: all preprocess build-preprocessed fasm68k build hexdump run clean update-submodules

all: preprocess build-preprocessed hexdump

preprocess:
	fasmg src/fasmg/preprocess.asm -isource=\'src/main.asm\' preprocessed.asm -e100

build-preprocessed:
	clownassembler -c -l main.lst -o main.bin -i preprocessed.asm

fasm68k:
#	make preprocess
	fasm68k src/main_fasm68k.asm main.bin -e10
	make hexdump
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

# Should keep/get the fasm68k submodule in sync with fasm68k master branch.
update-submodules:
	git submodule update --remote

# Update the branch tracked by the main repo.
stage-submodules:
	git add fasm68k
