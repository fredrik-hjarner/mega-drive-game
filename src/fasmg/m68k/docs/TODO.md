* Implement `assert_word_aligned` and use it in every instruction.
* Generate tests with famg macros. Output text with overridden emit/assemble.
  Then run vasm, clownassembler and famsg on that to be able to diff output.
  Also check what vams and clownassembler accept and does not accept.
* Make macro that "marks" all labels (label stuff interceptor thingie).
  I also need to mark labels create with the `label` instruction.
* I've seen d0.b/d0.w/d0.l used in some code but how does that work?
  I probaly should add support for that if it makes sense.
* Remove my exporting of instructions macros to preprocess.asm,
  because I will no longer need it, because I have a much better way to test now
  Remove the different forms of _assemble and _emit too.
* Hm could I override `emit` to output in big-endian?? That should be possible
  right? That would make the code less messy and I could skip using `bswap`.
* ~~`<<` creates some problems... since fasmg uses `shl` instead.~~
  ~~I wonder if I could fix that with `match`....~~
  ~~    ```~~
  ~~        match a? =<=< b?, maybe_number~~
  ~~        jno skip~~
  ~~        arrange maybe_number, a =shl b~~
  ~~    skip:~~
  ~~    ```~~
  ~~Same problem with other operators such as `|` as fasmg uses `or` instead.~~
* Make sure all instructions are case-insensitive.
* Add alias macros for instructions that only have one size
  such as lea for lea.l
* Hm, could I do wrappers for all instructions that log the name and the
  parameters, then executes the instruction, then logs @op1/@op2 values??
  because that's be neat so I can easily disable/enable logging.
* Sometimes I require a label to be specified with label1.w/.l and sometimes
  I require it to have no .w/.l part, examine this and how other assemblers
  do/behave and what they allow and don't allow.
  I think that's because branch instructions are relative jumps,
  the label's address is never sent instead the assembler calculates the
  jump length and send that jump length.
* Experiment with `relativeto` to find out if I can use that more in parsing.
  for example if I can have an m68k.register element instead of separate
  data_reg and address_reg elements, or actually if I can have both.
* If `$` is part on an expression then that expression MUST be `compute`:ed
      before any `emit` is done since otherwise it will change the value of `$`!
      This particular problem probably needs a well-thought out solution.
      You can see some of my primitive fixes by searching for `label_val`.
      It would be better if it came "pre-computed" from parse_operand though.
* I could probably have a `iterate <size, size_bytes>` and have bcc, bra and bsr
      in it to save a bit of space/code duplication (also .s alias has to be
      move into aliases.inc file for that to work smoothly).
* An idea I could have `parse_operand[@ea1|@ea2|dn1|dn2|an1|an2]`
      then I could have `reset@ea1` etc to reset vals to defaults
      then I could just emit <ea1> and <ea2> extension bits with one small macro
      or something
      ... though I don't know that may just be cumbersome...
* Maybe I should have branching instruction have .s as default and .b as the
      alias instead, dunno. Also I should move the alias into compat directory
      maybe?
* How should too large numbers behave? asl.w	($FFFFFFFF).w
      should it just be assigned max or should it wrap around??
      I currently have some code in parse_operand that sets too big numbers to
      the max allowed value.
* Make sure to test very very large and very very negative number for immediate
      values, and other relevant types, to see if bahaviour is good.
* Find out all the cases for when CALMINSTRUCTIONS can explode in an
      unrecoverable error, then make "safe" wrapper or overrides which
      error in a controlled fashion which you then can follow by `jok`/`jerr`
      checks.
* Make a count_tokens util.
* I now support `$7FFF(a2)` but I should also support `($7FFF,a2)` and add a lot
      of test cases to test that.
* vasm m68k manual has info about some of it's optimizations.
* Crap, maybe it's possible to write `(d8,Xn,PC)`
  etc. as any permutation (example `(d8,PC,Xn)`).
  I need to implement that if other assemblers
  support that...
* What is this about:
  btst.b	d5,#$55 ; TODO: destination can never be an immediate?! ; See clownassembler tests it's mentioned in two files there.
* ori.b	#$FF,ccr ; TODO: Have ccr test for ori.w ori.l which should fail.
  ori.w	#$FFFF,sr ; TODO: Have sr test for ori.b ori.l which should fail
  andi.b	#$FF,ccr ; TODO: Have ccr test for .w .l which should fail.
  eori.b	#$FF,ccr ; TODO: Have ccr test for .w .l which should fail.
  btst.l	#0,d5 ; TODO: Need to try to shift with more values than #0.
  move.w	@(pc,d5.w),sr ; TODO: Add move tests without size suffix!
  chk.w	@(pc),d5; TODO: I need to test other values than @ since @ is
      one token which makes my current tests succeed, but for several tokens it will fail. A `parse_immediate` util would help.
  chk.w	@(pc,d5.w),d5 ; must test this with an too: @(pc,a5.w)
  cmpm.b	(a2)+,(a1)+ ; TODO: More test of cmpm
  ror.w	(a2) ; TODO: What happens if you do ror.b (a2) or ror.l (a2) ?

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; things that cause unrecoverable errors in fasmg                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

`check reg_groups_found = 1` when reg_groups_found is not a value.
`Error: invalid expression.`

---

dividing an expression that contains an element, right?

---

