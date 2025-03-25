.PHONY: all build run clean

all: build

# -Fbin
#     Output formatless raw binary.
# 
# -spaces
#     Allow whitespace characters in the operand field. Otherwise a whitespace
#     could start the comment field there.
build:
	vasm -Fbin -spaces -o main.bin main.asm

run:
	cd ~/Downloads/Exodus_2.1 && wine exodus

clean:
	rm -f main.bin


