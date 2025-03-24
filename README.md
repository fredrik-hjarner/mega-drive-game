; mega drive test. 68k processor.
; make by running

* To compile
    `vasm -Fbin -o main.bin main.asm`

* To run exodus:
    `cd ~/Downloads/Exodus_2.1/`
    `wine exodus`

* vasm is a bit retarded
  This is not allowed:
    `move.w #$2700, sr`
  buit this is:
    `move.w #$2700,sr`
  so cant have a space after the comma...

* vasm is a bit retarded
  Everything except labels need to be indented...