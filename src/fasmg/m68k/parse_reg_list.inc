;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; PARSE_REG_LIST                                                             ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Define variable/namespace where parse_reg_list will store its results,
; for example @reg_list1.type
; Use parse_reg_list by suffixing it will either @reg_list1 or @reg_list2 like this:
;     parse_reg_list@reg_list1 some_operand_to_parse
; This is just for convenience.
define @reg_list1 @reg_list1
define @reg_list2 @reg_list2

iterate reg_list, @reg_list1,@reg_list2
    namespace reg_list
        ;; Define values in the @reg_list1 and @reg_list2 namespaces. ;;;;;;;;;;;;;;;;;;;;;;

        ; populated by parse_single_register
        define single_reg_found ; TODO: Comment
        define single_reg_mask_word ; TODO: Comment
        define single_reg_mask_word_reverse ; TODO: Comment
        define single_reg_type ; TODO: Comment

        ; populated by parse_reg_list
        define is_reg_list ; TODO: Comment
        define mask_word ; TODO: Comment
        define mask_word_reverse ; TODO: Comment

        ; populated by parse_register_range
        define reg_range_found ; TODO: Comment

        ; Supposed to be call:ed.
        ; TODO: Maybe this should not be called with @reg_list1/@reg_list2 but
        ;       @reg_list1/@reg_list2?
        ;
        ; Side-effects:
        ;     is_reg_list
        ;         1 if operand was a register list
        ;         0 otherwise
        ;
        ;     mask_word
        ;         Stores the `register mask` for the found register
        ;         Example:
        ;           a7 would be:
        ;               1000 0000 0000 0000b or
        ;               1 shl 15
        ;
        ;     mask_word_reverse
        ;         single_reg_mask_word but reversed
        calminstruction m68k.parse_reg_list#reg_list operand*
                    local tmp1
                    local tmp2
                    local opstr
                    local tail
                    local head

                ; Init default values
                    compute is_reg_list, 0
                    compute mask_word, 0
                    compute mask_word_reverse, 0

                ; Display operand
                    arrange opstr, operand
                    stringify opstr
                    display 10
                    display opstr bappend ":" bappend 10

                ; Check if operator is a single register token
                    call m68k.parse_single_register#reg_list, operand
                    check single_reg_found = 1
                    jno register_range
                ; is_single_register_token:
                    compute is_reg_list, 1
                    ; we should also compute the mask here
                    compute mask_word, single_reg_mask_word
                    compute mask_word_reverse, single_reg_mask_word_reverse
                    jump done
                ; Check if operator is a `register range`
                register_range:
                    call m68k.parse_register_range#reg_list, operand
                    check reg_range_found = 1
                    jno reg_groups
                    compute is_reg_list, 1
                    ; we should also compute the mask here
                    ; compute mask_word, single_reg_mask_word
                    ; compute mask_word_reverse, single_reg_mask_word_reverse
                    jump done ; temporary. TODO: DO checks for other stuff
                reg_groups:
                    

                done:
                    ;; Log stuff ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                    ; is_reg_list
                    arrange tmp1, is_reg_list
                    stringify tmp1
                    display 'is_reg_list:                  ' bappend tmp1 bappend 10

                    ; mask_word
                    arrange tmp1, mask_word
                    stringify tmp1
                    display 'mask_word:                    ' bappend tmp1 bappend 10

                    ; mask_word_reverse
                    arrange tmp1, mask_word_reverse
                    stringify tmp1
                    display 'mask_word_reverse:            ' bappend tmp1 bappend 10

                
                ;; start new code ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                    ; call m68k.count_reg_groups#@reg_list1, operand
                    ; call m68k.parse_reg_groups#@reg_list1, operand
                
                ;; end new code ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                    arrange tail, operand

            ; ;; Some initial parsing to see if this is a reg_list at all ;;;;;;;;
            ;         match tmp1 =/ tmp2, tail
            ;         jyes parse_tail
            ;         display 'FAILED MATCH: match tmp1 =/ tmp2, tail' bappend 10

            ;         match tmp1 =- tmp2, tail
            ;         jyes check_reg_interval
            ;         ; So it contain a - but that does not prove
            ;         display 'FAILED MATCH: match tmp1 =- tmp2, tail' bappend 10
            ;         jump check_single_reg
            ;     check_reg_interval:
            ;         ; TODO: Too long lines :'/
            ;         ;     |- check if tmp1 and tmp2 are data regs --------------------------|   |- check if tmp1 and tmp2 are address regs -----------------------------|
            ;         check ((tmp1 relativeto m68k.data_reg) & (tmp2 relativeto m68k.data_reg)) | ((tmp1 relativeto m68k.address_reg) & (tmp2 relativeto m68k.address_reg))
            ;         jyes parse_tail
            ;     ; Check if single register
            ;     check_single_reg:
            ;         check operand relativeto m68k.data_reg | operand relativeto m68k.address_reg
            ;         jyes parse_tail
            ;         display 'FAILED CHECK: relativeto regs' bappend 10
            ;         jump not_reg_list

            ; parse_tail:
            ;     display 'Is a register list!' bappend 10
            ;     exit

            ; not_reg_list:
            ;     display 'Not a register list!' bappend 10
                
        end calminstruction

         ; TODO: Comment
        ; What I mean with `reg_group` is `reg_group1/reg_group2/reg_group3`
        ; i.e. split with `/`
        calminstruction m68k.count_reg_groups#reg_list operand*

            compute reg_groups, 0

            ;; Replace << with shl ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            next_slash:
                match a? =<=< b?, expr
                jno done_slash
                arrange expr, a =slash b
                jump next_slash
            done_slash:

                
                jno not_single_register

            not_single_register:
                display 'not_single_register' bappend 10

        end calminstruction

        ; TODO: Comment
        ; What I mean with `reg_group` is `reg_group1/reg_group2/reg_group3`
        ; i.e. split with `/`
        calminstruction m68k.parse_reg_groups#reg_list operand*

                
                jno not_single_register

            not_single_register:
                display 'not_single_register' bappend 10

        end calminstruction

        ; TODO: Comment
        ; For use with parse_single_register.
        ; I suppose these need to be reverse somehow later.
        ; TODO: Or maybe parse_single_register should not return this
        ;       but rather a higher up function should take care of this stuff
        ;       a function that knows if forward or reversed mask should be used
        ; TODO: These kinda stuff could also be made with `iterate`...
        define single_reg_mask_words
        namespace single_reg_mask_words
            define d0 1 shl 0
            define d1 1 shl 1 
            define d2 1 shl 2
            define d3 1 shl 3
            define d4 1 shl 4
            define d5 1 shl 5
            define d6 1 shl 6
            define d7 1 shl 7
            define a0 1 shl (0 + 8)
            define a1 1 shl (1 + 8)
            define a2 1 shl (2 + 8)
            define a3 1 shl (3 + 8)
            define a4 1 shl (4 + 8)
            define a5 1 shl (5 + 8)
            define a6 1 shl (6 + 8)
            define a7 1 shl (7 + 8)
        end namespace

        ; Same as above but reversed
        ; TODO: These kinda stuff could also be made with `iterate`...
        define single_reg_mask_words_reverse
        namespace single_reg_mask_words_reverse
            define a7 1 shl 0
            define a6 1 shl 1 
            define a5 1 shl 2
            define a4 1 shl 3
            define a3 1 shl 4
            define a2 1 shl 5
            define a1 1 shl 6
            define a0 1 shl 7
            define d7 1 shl (0 + 8)
            define d6 1 shl (1 + 8)
            define d5 1 shl (2 + 8)
            define d4 1 shl (3 + 8)
            define d3 1 shl (4 + 8)
            define d2 1 shl (5 + 8)
            define d1 1 shl (6 + 8)
            define d0 1 shl (7 + 8)
        end namespace

        ; TODO: Double-check if I am even using `single_reg_types`
        define single_reg_types
        namespace single_reg_types
            iterate i, 0,1,2,3,4,5,6,7
                define d#i 'dreg'
                define a#i 'areg'
            end iterate
        end namespace

        ; TODO: Comment
        ;
        ; Side-effects:
        ;     @reg_list1.single_reg_found
        ;         1 if operand was a single register
        ;         0 otherwise
        ;
        ;     @reg_list1.single_reg_mask_word
        ;         Stores the `register mask` for the found register
        ;         Example:
        ;           a7 would be:
        ;               1000 0000 0000 0000b or
        ;               1 shl 15
        ;
        ;     @reg_list1.single_reg_mask_word_reverse
        ;         single_reg_mask_word but reversed
        ;
        ;     @reg_list1.single_reg_type
        ;         'dreg' - data register
        ;         'areg' - address register
        calminstruction m68k.parse_single_register#reg_list operand*
                local tmp1
                local tmp2

            ; Init default values
                compute single_reg_found, 0
                compute single_reg_mask_word, 0
                compute single_reg_mask_word_reverse, 0
                compute single_reg_type, 'unknown'

            ; Validate is not empty
                match , operand
                jno at_least_one_token
                err 'operand is empty'
            at_least_one_token:

            ; Check if only one token.
                match tmp1 tmp2, operand
                jyes done
                ; display '== was single token ==' bappend 10
                check operand relativeto m68k.data_reg | operand relativeto m68k.address_reg
                jno done
                ; display '== was a single register ==' bappend 10

                ; single_reg_type
                arrange single_reg_type, operand
                transform single_reg_type, single_reg_types
                compute single_reg_type, single_reg_type ; TODO: Is this needed?

                ; mask
                arrange single_reg_mask_word, operand
                transform single_reg_mask_word, single_reg_mask_words
                ; TODO: Is compute needed here?
                compute single_reg_mask_word, single_reg_mask_word

                ; mask reverse
                arrange single_reg_mask_word_reverse, operand
                transform single_reg_mask_word_reverse, single_reg_mask_words_reverse
                ; TODO: Is compute needed here?
                compute single_reg_mask_word_reverse, single_reg_mask_word_reverse

                ; "return true" so to speak
                compute single_reg_found, 1
            done:
                ;; Display log ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                ; single_reg_found
                arrange tmp1, single_reg_found
                stringify tmp1
                display 'single_reg_found:             ' bappend tmp1 bappend 10

                ; single_reg_type
                display 'single_reg_type:              ' bappend single_reg_type bappend 10

                ; single_reg_mask_word
                arrange tmp1, single_reg_mask_word
                stringify tmp1
                display 'single_reg_mask_word:         ' bappend tmp1 bappend 10

                ; single_reg_mask_word_reverse
                arrange tmp1, single_reg_mask_word_reverse
                stringify tmp1
                display 'single_reg_mask_word_reverse: ' bappend tmp1 bappend 10

        end calminstruction

        ; TODO: Comment.
        ; Side-effects:
        ;     reg_range_found
        ;         TODO: comment
        ;
        ; Examples of register ranges:
        ;     d0-d7
        ;     a2-a4
        calminstruction m68k.parse_register_range#reg_list operand*
                local tmp1
                local tmp2

            ; Init default values
                compute reg_range_found, 0
                ; compute single_reg_mask_word, 0
                ; compute single_reg_mask_word_reverse, 0
                ; compute single_reg_type, 'unknown'

            ; Validate is not empty
                match , operand
                jno at_least_one_token
                err 'operand is empty'
            at_least_one_token:

            ; Check if only one token.
                match tmp1 =- tmp2, operand
                jno done

                ; TODO: This might be slow.
                call m68k.parse_single_register@reg_list1, tmp1
                call m68k.parse_single_register@reg_list2, tmp2

                ; TODO: Too long line.
                check @reg_list1.single_reg_found = 1 & @reg_list2.single_reg_found = 1 & @reg_list1.single_reg_type = @reg_list2.single_reg_type
                jno done
            ; is_reg_range:
                compute reg_range_found, 1
                ; So now I need to compute the mask word and reverse mask word.

                jump done ; TODO: Remove this jump?







                ; ; display '== was single token ==' bappend 10
                ; check operand relativeto m68k.data_reg | operand relativeto m68k.address_reg
                ; jno done
                ; ; display '== was a single register ==' bappend 10

                ; ; single_reg_type
                ; arrange single_reg_type, operand
                ; transform single_reg_type, single_reg_types
                ; compute single_reg_type, single_reg_type ; TODO: Is this needed?

                ; ; mask
                ; arrange single_reg_mask_word, operand
                ; transform single_reg_mask_word, single_reg_mask_words
                ; ; TODO: Is compute needed here?
                ; compute single_reg_mask_word, single_reg_mask_word

                ; ; mask reverse
                ; arrange single_reg_mask_word_reverse, operand
                ; transform single_reg_mask_word_reverse, single_reg_mask_words_reverse
                ; ; TODO: Is compute needed here?
                ; compute single_reg_mask_word_reverse, single_reg_mask_word_reverse

                ; ; "return true" so to speak
                ; compute single_reg_found, 1
            done:
                ;; Display log ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                ; single_reg_found
                arrange tmp1, reg_range_found
                stringify tmp1
                display 'reg_range_found:             ' bappend tmp1 bappend 10

                ; ; single_reg_type
                ; display 'single_reg_type:              ' bappend single_reg_type bappend 10

                ; ; single_reg_mask_word
                ; arrange tmp1, single_reg_mask_word
                ; stringify tmp1
                ; display 'single_reg_mask_word:         ' bappend tmp1 bappend 10

                ; ; single_reg_mask_word_reverse
                ; arrange tmp1, single_reg_mask_word_reverse
                ; stringify tmp1
                ; display 'single_reg_mask_word_reverse: ' bappend tmp1 bappend 10

        end calminstruction

    end namespace
end iterate