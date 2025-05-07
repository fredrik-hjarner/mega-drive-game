* ~~Automatically make a hexdump on build so I can commit it and diff with git~~
* ~~Use fasmg/fasm2 to proprocess the file with fasmg macros.~~
* make macros to set up write to CRAM, VRAM and VSRAM
    move.l  #$40000000, vdp_ctrl    ; Start writing at VRAM $0000
* Implement
      BRA
      BSR
      Bcc
* Implement
      dc.b
      dc.w
      dc.l
* Add "Releases" maybe?
* Add github flows where binary is generated maybe?
* Add an "artifacts" folder where all artifacts (in binary) are stored.
* Make a hexdump that is one byte per line.
* Prefix all macros with `%`.
* "Ban" instructions that take too many cycles like DIVS, DIVU.
* Make some x86 inspired macros such as INC (addq.b #1, d0), DEC (subq.b #1, d0), etc.
  maybe some movzx or something that zero extends after a move, dunno.
  maybe push.w, pop.w, push.l, pop.l, etc.
* Remake all macros in fasmg so all macros are fasmg macros.
* Move tiles into a separate file.
* Store all the VDP registers in memory, that way the code can now their values.
      Then have som kind of sync function that either syncs all or syncs any
      specific one of them.
      This would allow me to "toggle", or set the VDP register single
      bits/settings while keeping the rest of the settings the same.
      So in other words I can have a function named `set_interlaced val`.