all: clean build hexdump
.PHONY: all

build:
	fasm68k src/main.asm main.bin -e30 -v1
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

################################################################################
#                                                                              #
# RAM DISK                                                                     #
#                                                                              #
################################################################################

# pull into ram disk
ram-pull:
	mkdir -p /dev/shm/code/68k
	rsync -a --delete ~/Desktop/code/68k/ /dev/shm/code/68k
.PHONY: ram-pull

# push ram disk to hard drive (DRY RUN)
ram-push-dry:
	rsync -ain --stats --progress --delete /dev/shm/code/68k/ ~/Desktop/code/68k
.PHONY: ram-push-dry

# push ram disk to hard drive
ram-push:
	rsync -a --stats --progress --delete /dev/shm/code/68k/ ~/Desktop/code/68k
.PHONY: ram-push