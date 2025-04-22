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
* `<<` creates some problems... since fasmg uses `shl` instead.
  I wonder if I could fix that with `match`....
      ```
          match a? =<=< b?, maybe_number
          jno skip
          arrange maybe_number, a =shl b
      skip:
      ```
  Same problem with other operators such as `|` as fasmg uses `or` instead.
* Make sure all instructions are case-insensitive.
* Add alias macros for instructions that only have one size
  such as lea for lea.l
* Hm, could I do wrappers for all instructions that log the name and the
  parameters, then executes the instruction, then logs @op1/@op2 values??
  because that's be neat so I can easily disable/enable logging.