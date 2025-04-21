* Implement `assert_word_aligned` and use it in every instruction.
* Generate tests with famg macros. Output text with overridden emit/assemble.
  Then run vasm, clownassembler and famsg on that to be able to diff output.
  Also check what vams and clownassembler accept and does not accept.
* Make macro that "marks" all labels (label stuff interceptor thingie).
* I've seen d0.b/d0.w/d0.l used in some code but how does that work?
  I probaly should add support for that if it makes sense.
* Remove my exporting of instructions macros to preprocess.asm,
  because I will no longer need it, because I have a much better way to test now
  Remove the different forms of _assemble and _emit too.
* Hm could I override `emit` to output in big-endian?? That should be possible
  right? That would make the code less messy and I could skip using `bswap`.