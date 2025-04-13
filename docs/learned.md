* Seems instuctions always need to be word aligned.
* Seems numbers you put int interrupt vectors must also be word-aligned.
* Use -wfail in vasm.
* Use -spaces in vasm.
* vdp register 0 bit 0 should ALWAYS be 0, otherwise it will work like crap on
  real hardware.