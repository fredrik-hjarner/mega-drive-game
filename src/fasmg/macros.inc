; macro calminstruction?.assemble? &line&
;     stringify line
;     ; TODO: Shoten this code?
;     ; vasm stuff usually needs to be prefixed with whitespace.
;     emit 1, 20h
;     emit 1, 20h
;     emit 1, 20h
;     emit 1, 20h
;     emit lengthof line, line
;     emit 1, 13
;     emit 1, 10
; end macro

; TODO: Name sucks.
; TODO: Maybe I can match to see if it contains equ here like macro above?
macro calminstruction?.assemble2? &line&
    stringify line
    ; In vasm labels need to NOT be prefixed with whitespace.
    emit lengthof line, line
    emit 1, 13
    emit 1, 10
end macro

; curr_var_addr stores where to place the next variable in RAM.
; It is initialized to the start of RAM.
curr_var_addr = $FF0000

; Declares a word variable in RAM.
calminstruction word var_name
    local tmp
    arrange tmp, var_name =equ= curr_var_addr
    assemble2 tmp
    ; increment the address for the next variable
    compute curr_var_addr, curr_var_addr + 2
end calminstruction

; Declares a byte variable in RAM.
calminstruction byte var_name
    local tmp
    arrange tmp, var_name =equ= curr_var_addr
    assemble2 tmp
    ; increment the address for the next variable
    compute curr_var_addr, curr_var_addr + 1
end calminstruction

; arguments:
;     reg_nr: register number: 0-23d
;     value:  value: 8 bits
calminstruction set_vdp_register reg_nr, value
    local set_reg
    local reg
    local res
    local cmd

    compute set_reg, 1 shl 15
    compute reg, reg_nr shl 8
    compute res, set_reg or reg or value
    arrange cmd,=move.=w #res,=vdp_ctrl
    _assemble cmd
end calminstruction

calminstruction meta_version
    local tmp, quote, s_since_2025, m_since_2025

    arrange quote, '

    compute tmp, __time__
    compute s_since_2025, tmp - 1735686000
    compute m_since_2025, s_since_2025 / 60

    arrange tmp, =dc.=b quote=GM m_since_2025 quote
    _assemble tmp
end calminstruction

; arguments:
;     r: 0-7
;     g: 0-7
;     b: 0-7
; TODO: The name kinda sucks.
; TODO: This would be better as an inline fasmg macro.
macro set_palette_color r, g, b
    ; bbb0 ggg0 rrr0
    emit move.w  #((b)<<9) | ((g)<<5) | ((r)<<1), vdp_data
end macro
define set_palette_color +set_palette_color

; arguments:
;     addr: address: $0000-$FFFF
; https://segaretro.org/Sega_Mega_Drive/VDP_general_usage
macro set_write_vram addr
    emit move.l #$40000000+(((addr)&$3FFF)<<16)+(((addr)&$C000)>>14),vdp_ctrl
end macro
define set_write_vram +set_write_vram

; arguments:
;     addr: address: $00-$FF
; https://segaretro.org/Sega_Mega_Drive/VDP_general_usage
macro set_write_vsram addr
    emit move.l #$40000010+((addr)<<16),vdp_ctrl
end macro
define set_write_vsram +set_write_vsram

; https://plutiedev.com/controllers
macro gamepads_get_input
    ; a0 = IoData1 for player 1
    ;    = IoData2 for player 2

    emit move.b #$40, gamepad1_ctrl

    ; TODO: Wouldn't movea work here as well??
    ; Why or why not??
    emit lea.l  gamepad1_data.l, a0
    
    ; set bit 6 (TH) to 1 to get first group of buttons
    emit move.b  #$40, (a0)  ; Do 1st step
    emit nop                 ; D-pad, B and C
    emit nop
    emit move.b  (a0), d0
    emit not.b d0 ; invert so pressed = 1 instead of 0
    ; d0 will now contain
    ; Bit5 	Bit4 	Bit3 	Bit2 	Bit1 	Bit0
    ; C 	B 	    Right 	Left 	Down 	Up

    ; Up
    emit move.b d0, d1
    emit andi.b #1, d1
    emit move.b d1, gamepad1_up

    ; Down
    emit lsr.b #1, d0
    emit move.b d0, d1
    emit andi.b #1, d1
    emit move.b d1, gamepad1_down

    ; Left
    emit lsr.b #1, d0
    emit move.b d0, d1
    emit andi.b #1, d1
    emit move.b d1, gamepad1_left

    ; Right
    emit lsr.b #1, d0
    emit move.b d0, d1
    emit andi.b #1, d1
    emit move.b d1, gamepad1_right

    ; B
    emit lsr.b #1, d0
    emit move.b d0, d1
    emit andi.b #1, d1
    emit move.b d1, gamepad1_b

    ; C
    emit lsr.b #1, d0
    emit move.b d0, d1
    emit andi.b #1, d1
    emit move.b d1, gamepad1_c
    
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; 2nd set of buttons                                                 ;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    emit move.b  #$00, (a0)
    emit nop
    emit nop
    emit move.b  (a0), d0
    emit not.b d0 ; invert so pressed = 1 instead of 0
    ; d0 will now contain
    ; Bit5   Bit4
    ; Start  A

    ; A
    emit lsr.b #4, d0
    emit move.b d0, d1
    emit andi.b #1, d1
    emit move.b d1, gamepad1_a

    ; Start
    emit lsr.b #1, d0
    emit move.b d0, d1
    emit andi.b #1, d1
    emit move.b d1, gamepad1_start
end macro
define gamepads_get_input +gamepads_get_input

; bappend
; Util macro for CALM to concatenate strings with shorter syntax.
; Only works when added to preprocess.asm
; Example:
;     calminstruction tester
;         local tmp, tmp2
;         bappend tmp, 13, 10
;         display tmp ; Output: empty line
;         bappend tmp, "a", "b", "c", 13, 10
;         display tmp ; Output: abc
;         compute tmp2, "$"
;         bappend tmp, tmp2, "a", "b", "c", 13, 10
;         display tmp ; Output: $abc
;     end calminstruction
;     tester
; OBSERVE! I managed to make a version of append that works without
; preprocess.asm so I am using that instead.
; macro bappend dest*, strings&
;     emit compute dest, ""
;     iterate string, strings
;         emit compute dest, dest bappend string
;     end iterate
; end macro

; Make visible to the preprocessor
; define bappend +bappend
define word +word
define byte +byte
define set_vdp_register +set_vdp_register
define meta_version +meta_version