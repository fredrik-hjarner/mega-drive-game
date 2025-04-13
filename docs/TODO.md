* ~~Automatically make a hexdump on build so I can commit it and diff with git~~
* Use fasmg/fasm2 to proprocess the file with fasmg macros.
* make macros to set up write to CRAM, VRAM and VSRAM
    move.l  #$40000000, vdp_ctrl    ; Start writing at VRAM $0000
* Implement bra.b, bra.w, bsr.b, bsr.w, b[cond].b, b[cond].w, 
* Add "Releases" maybe?
* Add github flows where binary is generated maybe?
* Add an "artifacts" folder where all artifacts (in binary) are stored.
* Make a hexdump that is one byte per line.
* Prefix all macros with `%`.