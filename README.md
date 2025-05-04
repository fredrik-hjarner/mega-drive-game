; mega drive test. 68k processor.
; using clownassembler.
; using fasmg to preprocess so I can use fasmg macros.

* to get
  `git clone --recurse-submodules git@github.com:fredrik-hjarner/mega-drive-game.git`

* to build
  `make build` or just `make`

* to install git hooks:
  `git config core.hooksPath .hooks`

* clownassembler is a bit pedantic
  Everything except labels need to be indented.