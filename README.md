; mega drive test. 68k processor.
; using vasm assembler.

* to build
  `make build` or just `make`

* vasm is a bit retarded
  This is not allowed:
    `move.w #$2700, sr`
  buit this is:
    `move.w #$2700,sr`
  so cant have a space after the comma...
  Well if -spaces option is used then you can have space after comma...

* vasm is a bit retarded
  Everything except labels need to be indented...