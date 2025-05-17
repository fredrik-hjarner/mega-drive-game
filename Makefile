all: clean build hexdump
.PHONY: all

build:
	fasm68k src/main.asm main.bin -e30 -v2
.PHONY: build

hexdump:
	xxd -b -c1 main.bin | cut -d' ' -f2,4 > main.hex
.PHONY: hexdump

clean:
	rm -f main.bin main.hex
.PHONY: clean

run:
	cd ~/Downloads/Exodus_2.1 && wine exodus
.PHONY: run

# Should keep/get the fasm68k submodule in sync with fasm68k master branch.
update-submodules:
	git submodule update --remote
.PHONY: update-submodules

# Update the branch tracked by the main repo.
stage-submodules:
	git add fasm68k
.PHONY: stage-submodules