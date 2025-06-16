;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FASMG SYNTAX HIGHLIGHTING TEST FILE
; Open this file in VS Code with your extension to visually check colors
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; COMMENTS - Should be gray (#777777)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; This is a single line comment
    ; Indented comment
; Comment with symbols: +-*/=<>()[]{}:?!,.|&~#`\

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; CONTROL KEYWORDS - Should be blue (#2277FF)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
break
else  
if
irp
irpv
iterate
repeat
while

; Mixed case (should still work due to (?i)):
BREAK
Else
If

; Edge cases - these should NOT be blue (they're not whole words):
breaking
elsewhere
endif
iffy

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; DATA DIRECTIVES - Should be keyword.other.fasmg color
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
db 'hello'
dw 1234
dd 0x12345678
dp 0
dq 0x123456789ABCDEF0
dt 3.14159
ddq 0
dqq 0
ddqq 0

rb 10
rw 5
rd 1
rp 2
rq 1
rt 1
rdq 1
rqq 1
rdqq 1

dup
dbx
emit
file

; Mixed case:
DB 'test'
DW 1000
EMIT 4, 0x12345678

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; OPERATOR KEYWORDS - Should be cyan (#33FFFF)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
bsf
bsr
defined
definite
elementsof
float
lengthof
not
sizeof
string
trunc
used
and
bappend
bswap
element
eq
eqtype
metadata
metadataof
mod
or
relativeto
scale
scaleof
shl
shr
xor

; Mixed case:
BSF
AND
XOR
NOT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SUPPORT FUNCTIONS - Should be yellow (#FFFF44)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
assert
display
err

; Mixed case:
ASSERT
DISPLAY
ERR

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SUPPORT CONSTANTS - Should be orange (#FF6622)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
byte
word
dword
fword
pword
qword
tbyte
tword
dqword
xword
qqword
yword
dqqword
zword
__time__
__file__
__line__
__source__

; Mixed case:
BYTE
WORD
DWORD

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; NUMBERS - Should be green (#22FF22)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Decimal numbers:
123
456d
0
999999

; Hexadecimal ($ prefix):
$FF
$1234
$ABCDEF
$deadbeef

; Hexadecimal (0x prefix):
0xFF
0x1234
0xABCDEF
0xdeadbeef

; Hexadecimal (h suffix):
0FFh
1234h
0ABCDEFh
0deadbeefh

; Binary:
10101010b
11111111b
01010101b
0b
01_01_01_01b
01_01_01_01_b
01'01'01'01b
01'01'01'01'b

; Octal:
777o
123q
0o
7q

; Edge cases - these should NOT be green:
FFh     ; Missing leading digit
abc123  ; Starts with letter
123x    ; Invalid suffix
_01_01_01_01b ; invalid
'01'01'01'01b ; invalid

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; PUNCTUATION - Should be magenta (#FF00FF)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
+ - * / = < > ( ) [ ] { } : ? ! , . | & ~ # ` \

; In context:
variable = 123
array[index]
if (condition)
namespace.symbol
label:
macro param1, param2
result = value1 + value2 * value3

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; MIXED SCENARIOS - Check for conflicts
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Numbers next to operators:
123+456
$FF*2
0xAB-0xCD

; Keywords with punctuation:
if(condition)
db'hello'
word[index]

; Comments with everything:
; This comment has numbers 123, keywords if, operators and, punctuation ()[]

; Edge case - description> (the one that was broken):
description>other
test>
>alone

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; THINGS THAT SHOULD BE DEFAULT COLOR (unmatched)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
unknown_identifier
someVariable
my_label
CamelCase
snake_case
SCREAMING_CASE

; These should be default color since they're not recognized keywords

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; SOME MORE CASES                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; These should NOT be colored (invalid):
$$111           ; Two dollar signs
a$0x0BEEF       ; Starts with letter  
a$0BEEFh        ; Starts with letter
if(condition)   ; No space after if
db'hello'       ; No space after db

; These SHOULD be colored (valid):
$111            ; Single dollar sign
0x0BEEF         ; Proper hex
0BEEFh          ; Proper hex with h
if (condition)  ; Space after if
db 'hello'      ; Space after db

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; COMPREHENSIVE NUMBER TESTS - Should all be green (#22FF22)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; DECIMAL NUMBERS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
123
456d
0
999999
42D     ; Mixed case

; In context:
variable = 123
array[456]
(789)
{012}
123+456
789*2
if 999
db 42
result = 100 + 200

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; HEXADECIMAL WITH $ PREFIX  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
$FF
$1234
$ABCDEF
$deadbeef
$0      ; Edge case: zero
$A      ; Single digit
$123ABC ; Mixed digits/letters

; In context:
variable = $FF
array[$1234]
($ABCDEF)
{$FF}
$FF+$AA
$BB*2
if $CC
db $DD
result = $EE + $FF

; Mixed case:
$ff
$ABCD
$aBcD

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; HEXADECIMAL WITH 0x PREFIX
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
0xFF
0x1234
0xABCDEF
0xdeadbeef
0x0
0xA
0x123ABC

; In context:
variable = 0xFF
array[0x1234]
(0xABCDEF)
{0xFF}
0xFF+0xAA
0xBB*2
if 0xCC
db 0xDD

; Mixed case:
0xff
0XABCD   ; Capital X
0xaBcD

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; HEXADECIMAL WITH h SUFFIX
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
0FFh
1234h
0ABCDEFh
0deadbeefh
0h       ; Edge case: zero
0Ah      ; Single digit after required leading digit
123ABCh

; In context:
variable = 0FFh
array[1234h]
(0ABCDEFh)
{0FFh}
0FFh+0AAh
0BBh*2
if 0CCh
db 0DDh

; Mixed case:
0ffH     ; Capital H
0ABCDH
0aBcDh

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; BINARY NUMBERS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
10101010b
11111111b
01010101b
0b
1b
10000000b

; In context:
variable = 10101010b
array[1111b]
(0101b)
{1010b}
1111b+0000b
1010b*2
if 1100b
db 1001b

; Mixed case:
10101010B
1111B

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; OCTAL NUMBERS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
777o
123q
0o
7q
377o
666q

; In context:
variable = 777o
array[123q]
(777o)
{123q}
777o+123o
456q*2
if 777o
db 123q

; Mixed case:
777O
123Q

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; EDGE CASES - SHOULD BE GREEN (valid numbers)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; At start/end of line:
$FF
123
0xAB

; With all possible separators:
,$FF
;$FF comment
+$FF
-$FF
*$FF
/$FF
=$FF
<$FF
>$FF
($FF)
[$FF]
{$FF}
:$FF
?$FF
!$FF
.$FF
|$FF
&$FF
~$FF
#$FF
`$FF
\$FF

; In expressions:
result = ($FF + 123) * 0xAB - 1010b / 777o
array[($1234 + 0x5678) and 0FFFFh]

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; INVALID CASES - SHOULD NOT BE GREEN (default color)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Invalid hex patterns:
FFh         ; Missing required leading digit
abc$FF      ; Letter before $
var$FF      ; Variable name before $
$$FF        ; Double dollar
a$FF        ; Letter before $
123$FF      ; Number before $

; Invalid 0x patterns:
abc0xFF     ; Letter before 0x
var0xFF     ; Variable name before 0x
10xFF       ; Number before 0x

; Invalid suffixes:
123x        ; Invalid suffix
456y        ; Invalid suffix
789z        ; Invalid suffix

; Partial matches in words:
variable123d    ; d is part of identifier
nameFFh         ; h is part of identifier
test0xAB        ; 0x is part of identifier

; Invalid characters in numbers:
$GGG        ; G not valid hex
0xGGG       ; G not valid hex
0GGGh       ; G not valid hex
22b         ; 2 not valid binary
888o        ; 8 not valid octal
999q        ; 9 not valid octal

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; MIXED SCENARIOS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Multiple numbers on same line:
db $FF, 123, 0xAB, 1010b, 777o, 0CDh

; Complex expressions:
if (($FF + 123) * 0xAB) > (1010b - 777o)
    result = array[($1234 and 0FFFFh) + offset]
end if

; Numbers with comments:
variable = $DEAD    ; This should be green
other = 0xBEEF      ; This too
final = 123d        ; And this













;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; KEYWORD BOUNDARY TESTS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; VALID - Should be colored:
if condition
db 'hello'
while x > 0
dd 0x12345

; INVALID - Should NOT be colored (no space):
if(condition)
db'hello'
while(x)
dd+5

; VALID - Comments after keywords:
if ; comment
db ; comment

; VALID - End of line:
if
db

1 or 1   ; Valid
(1)or(1) ; Valid
.1.or.1. ; Invalid
1or1     ; Invalid

db 'Hello World'        ; String should be one color
display "Error!"        ; No special chars colored inside
file 'data.bin'         ; Works with any keyword








;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; STRING EDGE CASE STRESS TESTS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; IMMEDIATELY ADJACENT - No spaces before/after strings
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Adjacent to identifiers:
variable'string'
'string'variable
word'middle'word
identifier"string"
"string"identifier

; Adjacent to numbers:
123'string'
'string'456
$FF"string"
"string"$AB
0x12'text'34

; Adjacent to operators:
+'string'
'string'+
='text'
'text'=
*"data"
"data"*

; Adjacent to punctuation:
('string')
['text']
{'data'}
:'label'
'value':
,'item'
'item',

; Complex adjacency:
func('param')
array['key']
obj.prop'suffix'
$addr'data'$end

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ESCAPED QUOTES - fasmg doubles quotes to escape them
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Single quotes with escaped single quotes:
'Don''t' ; comment
'It''s working' ; comment
'Can''t stop won''t stop' ; comment
'Multiple''escaped''quotes' ; comment
'End with escape: ''' ; comment
''''                   ; Four single quotes: empty string with quote inside

; Double quotes with escaped double quotes:
"Say ""Hello""" ; comment
"This is ""quoted"" text" ; comment
"Multiple ""escaped"" ""quotes""" ; comment
"End with escape: """" ; comment
""""                   ; Four double quotes: empty string with quote inside

; Complex escape patterns:
'Text with '' and more'
"Text with "" and more"
'Start''middle''end'
"Start""middle""end"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; QUOTE COMBINATIONS - Mixed patterns that could confuse parser
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Alternating quote types:
'"'                    ; Single quotes containing double quote
"'"                    ; Double quotes containing single quote
'"text"'               ; Single quotes around double-quoted text
"'text'"               ; Double quotes around single-quoted text

; Complex nesting scenarios:
'outer "inner" text'
"outer 'inner' text"
'He said "Don''t do that!"'
"She replied 'I won''t!'"

; Quote sequences:
''                     ; Empty single-quoted string
""                     ; Empty double-quoted string
''''                   ; Two empty strings or escaped quote?
""""                   ; Two empty strings or escaped quote?
''"                    ; Empty single + start double?
""'                    ; Empty double + start single?

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; BOUNDARY STRESS TESTS - Where string parsing often breaks
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; String immediately followed by same quote type:
'first''second'        ; Should be: 'first' + 'second' 
"first""second"        ; Should be: "first" + "second"

; Mixed quote boundaries:
'text'"more"
"text"'more'
'a'"b"'c'
"a"'b'"c"

; Strings with special sequence starters:
'0x'                   ; Looks like hex start
'$'                    ; Looks like hex prefix  
'123'                  ; Looks like number
'if'                   ; Looks like keyword
'and'                  ; Looks like operator

; Problematic character sequences inside strings:
'contains ; semicolon'
"contains ; semicolon"
'has \ backslash'
"has \ backslash"
'newline\n'
"tab\t"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; REAL-WORLD USAGE PATTERNS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; File paths with quotes:
file 'C:\Program Files\data.bin'
include "headers\main.inc"
load 'files with spaces.dat'

; Assembly string data:
db 'String 1', 'String 2'
dw "First", "Second", "Third"
dd 'Mixed''quotes''here'

; Error messages with quotes:
err 'Error: Can''t open file'
display "Warning: ''undefined''"
assert "Test failed: ""expected"""

; Complex expressions:
result = 'prefix' + variable + 'suffix'
if filename = 'data.bin'
message = 'Status: ' + (status ? 'OK' : 'Failed')

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; POTENTIAL PARSER BREAKERS - These often cause issues
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Unmatched quotes (should break gracefully):
; 'unterminated string at end of line
; "another unterminated string
; 'wrong terminator"
; "wrong terminator'

; Escaped quotes at string boundaries:
'ends with escape'''
"ends with escape"""
'''starts with escape'
"""starts with escape"

; Complex multi-line scenarios:
db 'line 1',\
   'line 2'
macro test param
    display 'param is: ' + param
end macro

; Maximum confusion patterns:
''''''''               ; Multiple escaped quotes
""""""""               ; Multiple escaped quotes  
'"'"'"'                ; Alternating quote types
"'"'"'"                ; Alternating quote types

'''






;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; EMBEDDED CODE IN COMMENTS - BACKTICKS SHOULD HIGHLIGHT SYNTAX
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Keywords should be highlighted inside backticks:
; Use `repeat 10` to loop ten times
; Try `db 'hello'` to define a string  
; The `macro test` directive is useful
; End with `end macro` statement

; Numbers should be highlighted inside backticks:
; Set value to `$FF` for 255 decimal
; Binary `1010b` equals decimal 10
; Hex number `0xABCD` is also valid
; Use `123h` for hexadecimal

; Strings should be highlighted inside backticks:
; Define text with `db 'Hello World'`
; Or use double quotes: `db "test"`  
; Empty string: `db ''`

; Mixed syntax should work:
; Full instruction: `mov eax, $12345678`
; With operators: `result = (value + 10) * 2`
; Complex: `repeat count, i:0`

; Multiple backticks on same line:
; Use `db` for bytes and `dw` for words
; Compare `$FF` with `255` - they're equal

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; EDGE CASES FOR BACKTICKS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Empty backticks: ``
; Single character: `a`
; Just a number: `123`
; Just whitespace: `   `
; Unclosed backtick: `this should not highlight
; Multiple on line: `first` and `second` code blocks
















;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; MULTI-LINE COMMENT BLOCKS - BASIC FUNCTIONALITY
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Simple block - all code inside should be highlighted:
; ```
; db 'hello world'
; repeat 10
;     mov eax, $FF
; end repeat
; ```

; Block with keywords:
; ```
; macro test name
;     local temp
;     temp = name + 1
; end macro
; ```

; Block with numbers and operators:
; ```
; value = $1234 + 0xABCD
; result = (value shl 2) and 0FFFFh
; binary = 1010b or 0011b
; ```

; Block with strings and mixed syntax:
; ```
; message db 'Hello, World!', 0
; count dw 256
; buffer rb count * 2
; ```

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; INDENTATION EDGE CASES
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; No indentation:
; ```
; db 1
; ```

; Heavy indentation:
;           ```
;           repeat 5
;               db %
;           end repeat
;           ```

; Mixed indentation levels:
;   ```
; db 'start'
;     nested_value = 123
;       very_nested db 'deep'
; db 'end'
;   ```

; Tabs vs spaces (if your editor shows them):
;	```
;	db	'tab-indented'
;	```

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; EMPTY AND MINIMAL CASES
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Empty block:
; ```
; ```

; Block with only whitespace:
; ```
;   
;     
; ```

; Single line of code:
; ```
; db 42
; ```

; Block with only comments inside:
; ```
; ; this is a comment inside code block
; ; another comment
; ```

; Block with mixed comments and code:
; ```
; ; Setup phase
; counter = 0
; ; Processing phase  
; repeat 10
;     counter = counter + 1
; end repeat
; ```

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; COMPLEX FASMG CODE IN BLOCKS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; CALM instructions:
; ```
; calminstruction test? value
;     compute value, value and 0FFh
;     assemble value
; end calminstruction
; ```

; Nested structures:
; ```
; struc POINT
;     .x dd ?
;     .y dd ?
; end struc
; 
; my_point POINT
; ```

; Complex expressions:
; ```
; result = ((base + offset) shl 2) and mask
; array[index] = string 'complex' bappend 10
; condition = defined symbol and symbol > 0
; ```

; Macro with parameters:
; ```
; macro declare_array name, size, init_val:0
;     name dd size dup init_val
; end macro
; ```

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; MULTIPLE BLOCKS AND SEQUENCES
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Two blocks in sequence:
; ```
; db 'first block'
; ```
; ```
; db 'second block'
; ```

; Blocks separated by regular comments:
; ```
; db 'block one'
; ```
; This is a regular comment between blocks
; ```
; db 'block two'  
; ```

; Blocks separated by actual code:
real_code db 'this is actual code, not in block'
; ```
; db 'this is in a block'
; ```
more_real_code dw 1234

; Multiple blocks with different content types:
; ```
; ; Data definitions
; buffer rb 256
; ```
; ```
; ; Control structures  
; if buffer_size > 128
;     db 'large buffer'
; end if
; ```
; ```
; ; Macro definitions
; macro debug msg
;     display msg, 10
; end macro
; ```

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ERROR CONDITIONS AND EDGE CASES
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; Block with extra text after opening ``` (should this work?):
; ``` extra text here
; db 'questionable'
; ``` extra text here

; Nested ``` inside block (should not close the block):
; ```
; comment_text db 'Use ``` for code blocks'
; another_line db 'still inside block'
; ```

; Block at very start of file (no preceding content):

; Block at very end of file (no following content):
; ```
; final_instruction db 'last line'
; ```

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; MIXED WITH INLINE BACKTICKS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Regular comment with inline code before block:
; Use `db` instruction for bytes, then:
; ```
; data_section:
;     db 'hello'
;     db 0
; ```

; Regular comment with inline code after block:
; ```
; setup_code db 'initialization'
; ```
; The above uses `db` to define byte data.

; Block containing inline backticks (nested):
; ```
; ; Use `repeat` for loops:
; repeat 5
;     db %
; end repeat
; ```

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; WHITESPACE AND FORMATTING VARIATIONS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; No space after semicolon:
;```
;db 'tight formatting'  
;```

; Extra spaces after semicolon:
;    ```
;    db 'extra spaces'
;    ```

; Inconsistent spacing:
; ```
;db 'line1'
;  db 'line2'  
;    db 'line3'
; ```

; Empty lines within block:
; ```
; db 'first'

; db 'after empty line'
; 
; db 'after another empty'
; ```

; color test

db ; 1
qword assert ; 2
assert 5 ; 3
0BEEFh ; 4
white ; 5
metadata break ; 6
break metadata 54 ; 7
'pink' db ;8
+-*/=<>( db ; 9
















;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; CALM INSTRUCTION SCOPING
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Outside CALM - these should be regular colors
display 'regular display'      ; 1
local temp                     ; 2  
match a, b                     ; 3

; Basic CALM block
calminstruction simple_test    ; 4
    display 'CALM display'     ; 5 (should be different color than #1)
    local result               ; 6 (should be different color than #2) 
    match result, value        ; 7 (should be different color than #3)
end calminstruction           ; 8

; Back outside CALM
display 'regular again'        ; 9 (should match color #1)

; CALM with comments and embedded code
calminstruction comment_test   ; 10
    ; Regular comment with `display 'embedded'` code  ; 11
    display 'actual CALM code' ; 12
end calminstruction           ; 13
    
display 'should be regular'    ; 16 (critical test - should NOT be CALM colored)

; Recovery test  
macro recovery                 ; 17
    display 'in macro'         ; 18 (should be regular, not CALM)
end macro                     ; 19

; Case variations
CALMINSTRUCTION UPPERCASE      ; 20
    DISPLAY 'test'            ; 21
END CALMINSTRUCTION           ; 22

calminstruction lowercase      ; 23  
    display 'test'            ; 24
end calminstruction           ; 25

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; COMPREHENSIVE CALM TOKEN TESTING
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Outside CALM - baseline colors for comparison
display 'baseline regular'
local baseline_var
match baseline_a, baseline_b
db 42
assert 1
'string' + 0x42 and byte

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ALL TOKEN TYPES INSIDE CALM
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

calminstruction comprehensive_test param1*, param2:default, param3&
    
    ; =================================================================
    ; COMMENTS (all variations)
    ; =================================================================
    ; Regular comment
    ; Comment with `embedded regular code: db 'test'`
    ; Comment with numbers: 42, 0xFF, 1010b
    ; Comment with operators: +, -, *, /, and, or, xor
    ; Comment with built-ins: byte, word, __time__
    
    ; =================================================================
    ; STRINGS (all quote types and escapes)
    ; =================================================================
    local single_quoted, double_quoted, complex_string
    arrange single_quoted, 'single quoted string'
    arrange double_quoted, "double quoted string"
    arrange complex_string, 'String with ''escaped quotes'' inside'
    arrange complex_string, "String with ""escaped quotes"" inside"
    arrange complex_string, 'Mixed: "double" inside single'
    arrange complex_string, "Mixed: 'single' inside double"
    arrange complex_string, 'Special chars: !@#$%^&*()[]{}|\\:";\'<>?,./'
    
    ; =================================================================
    ; NUMBERS (all formats from your grammar)
    ; =================================================================
    local decimal_nums, hex_nums, binary_nums, octal_nums
    compute decimal_nums, 123        ; Plain decimal
    compute decimal_nums, 456d       ; Decimal with 'd'
    compute hex_nums, 0xFF           ; Hex with 0x
    compute hex_nums, 0ABCDh         ; Hex with h (starts with digit)
    compute hex_nums, $BEEF          ; Hex with $
    compute binary_nums, 1010b       ; Binary
    compute binary_nums, 11110000b   ; Longer binary
    compute octal_nums, 377o         ; Octal with o
    compute octal_nums, 177q         ; Octal with q
    
    ; =================================================================
    ; SPECIAL CHARACTERS (all from your entity pattern)
    ; =================================================================
    local expressions
    compute expressions, param1 + param2       ; +
    compute expressions, param1 - param2       ; -
    compute expressions, param1 * param2       ; *
    compute expressions, param1 / param2       ; /
    compute expressions, param1 = param2       ; =
    compute expressions, param1 < param2       ; < >
    compute expressions, param1 > param2
    check param1 <= param2                     ; <= >=
    check param1 >= param2
    check param1 <> param2                     ; <>
    
    ; Brackets and delimiters: ( ) [ ] { }
    arrange expressions, (param1 + param2) * [param3]
    arrange expressions, {complex: expression}
    
    ; Other special chars: : ? ! , . | & ~ # ` \
    arrange expressions, label:value            ; :
    check param1 ? param2 : param3            ; ? :
    arrange expressions, important!            ; !
    arrange expressions, item1, item2, item3   ; ,
    arrange expressions, struct.member         ; .
    compute expressions, param1 | param2      ; |
    compute expressions, param1 & param2      ; &
    compute expressions, ~param1               ; ~
    arrange expressions, concat#param1#param2 ; #
    arrange expressions, `param1              ; `
    arrange expressions, path\file            ; \
    
    ; =================================================================
    ; UNARY OPERATORS (from your grammar)
    ; =================================================================
    local unary_results
    compute unary_results, bsf(param1)
    compute unary_results, bsr(param1)
    check defined param1
    check definite param2
    compute unary_results, elementsof(param1)
    compute unary_results, float(param1)
    compute unary_results, lengthof(param1)
    compute unary_results, not param1
    compute unary_results, sizeof param1
    compute unary_results, string(param1)
    compute unary_results, trunc(param1)
    check used param1
    
    ; =================================================================
    ; BINARY OPERATORS (from your grammar)  
    ; =================================================================
    local binary_results
    compute binary_results, param1 and param2
    compute binary_results, param1 bappend param2
    compute binary_results, param1 bswap 4
    compute binary_results, param1 element 0
    check param1 eq param2
    check param1 eqtype param2
    compute binary_results, param1 metadata 0
    compute binary_results, param1 metadataof 0
    compute binary_results, param1 mod param2
    compute binary_results, param1 or param2
    check param1 relativeto param2
    compute binary_results, param1 scale 0
    compute binary_results, param1 scaleof 0
    compute binary_results, param1 shl 2
    compute binary_results, param1 shr 2
    compute binary_results, param1 xor param2
    
    ; =================================================================
    ; BUILT-IN CONSTANTS (from your support.constant pattern)
    ; =================================================================
    local size_constants, builtin_vars
    compute size_constants, byte
    compute size_constants, word
    compute size_constants, dword
    compute size_constants, fword
    compute size_constants, pword
    compute size_constants, qword
    compute size_constants, tbyte
    compute size_constants, tword
    compute size_constants, dqword
    compute size_constants, xword
    compute size_constants, qqword
    compute size_constants, yword
    compute size_constants, dqqword
    compute size_constants, zword
    
    arrange builtin_vars, __time__
    arrange builtin_vars, __file__
    arrange builtin_vars, __line__
    arrange builtin_vars, __source__
    arrange builtin_vars, %t        ; legacy time
    
    ; =================================================================
    ; DATA DIRECTIVES (from your keyword.other pattern)
    ; =================================================================
    emit 1, 42                      ; emit (CALM version)
    emit 2, 0x1234
    emit 4, param1
    emit 8, param1 + param2
    
    ; =================================================================
    ; DIAGNOSTIC FUNCTIONS (from your support.function pattern)
    ; =================================================================
    display 'CALM display function'  ; CALM version of display
    err 'CALM error message'         ; CALM version of err
    
    ; =================================================================
    ; ALL CALM-SPECIFIC COMMANDS
    ; =================================================================
    
    ; Internal commands (should be keyword.control.calm)
    assemble param1
    arrange local_var, param1, ' + ', param2
    call other_instruction, param1
    check param1 > 0
    compute local_var, param1 * 2
    exit
    
    ; Jump commands  
    check param1 = param2
    jyes success
    jno failure
    jump done
    
    ; Variable manipulation
    local temp_var
    match temp_var, param1
    publish temp_var, param1
    stringify temp_var
    take temp_var, param1
    taketext temp_var, param1
    transform temp_var
    
    ; Assembly commands (should be support.function.calm)
    load temp_var, 0, 4
    store 0, 4, param1
    
    ; Extension commands (should be keyword.other.calm)
    init temp_var, 0
    initsym temp_var, param1
    xcall other_instruction
    
success:
    display 'Success path'
    jump done
    
failure:
    err 'Failure path'
    
done:
    ; =================================================================
    ; COMPLEX EXPRESSIONS AND COMBINATIONS
    ; =================================================================
    local complex_expr
    compute complex_expr, (param1 + param2) * sizeof(dword) shl 2
    compute complex_expr, param1 and 0FFh or (param2 shl 8)
    compute complex_expr, bsr(param1) + lengthof('test string')
    check (param1 relativeto param2) & (param1 > 0)
    
    arrange complex_expr, 'Result: ', complex_expr, ' at ', __time__
    display complex_expr
    
    ; =================================================================
    ; WHITESPACE VARIATIONS
    ; =================================================================
    local		tab_separated
    compute	tab_separated	,	param1	+	param2
    display		tab_separated
    
    local    multiple_spaces
    compute    multiple_spaces    ,    param1    *    2
    display    multiple_spaces
    
    local minimal
    compute minimal,param1+param2*3
    display minimal
    
end calminstruction

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; CALM BLOCK WITH NESTED CONSTRUCTS  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

calminstruction nested_constructs_test value*
    
    ; CALM commands mixed with control structures
    local counter, result
    compute counter, 0
    
    ; Note: These might not work if you don't have repeat/if patterns in CALM
    ; But they test how CALM scope interacts with other constructs
    
    check value > 0
    jno skip_processing
    
    ; Simulated repeat with labels and jumps
loop_start:
    display 'Processing iteration: ', counter
    compute result, counter * value
    emit 1, result
    compute counter, counter + 1
    check counter < value
    jyes loop_start
    
skip_processing:
    display 'Final result: ', result
    
end calminstruction

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; EDGE CASES AND MALFORMED CONSTRUCTS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; CALM with parameter edge cases
calminstruction edge_case_params (label_param) name*, value:42, rest&
    arrange name, label_param, ': ', value
    display name, rest
end calminstruction

; CALM with complex whitespace
calminstruction	whitespace_test	
    local	result
    compute	result	,	42
    display	result
end	calminstruction

; CALM with line continuation (if your grammar supports it)
calminstruction line_continuation_test \
    param1*, \
    param2:default
    local very_long_variable_name
    compute very_long_variable_name, \
            param1 + \
            param2 * \
            2
    display very_long_variable_name
end calminstruction

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; COMPARISON - SAME TOKENS OUTSIDE CALM
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; These should have DIFFERENT colors than their CALM counterparts above
display 'regular display - compare with CALM display'
local regular_var
match regular_a, regular_b
assert regular_var > 0
db 'regular data directive'
42 + 0xFF and byte
bsf(regular_var) + sizeof(word)