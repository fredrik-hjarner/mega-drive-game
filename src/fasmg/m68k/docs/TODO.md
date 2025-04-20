* Implement `assert_word_aligned` and use it in every instruction.
* Generate tests with famg macros. Output text with overridden emit/assemble.
  Then run vasm, clownassembler and famsg on that to be able to diff output.
  Also check what vams and clownassembler accept and does not accept.
* Make macro that "marks" all labels (label stuff interceptor thingie).
* I've seen d0.b/d0.w/d0.l used in some code but how does that work?
  I probaly should add support for that if it makes sense.