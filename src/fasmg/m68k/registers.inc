define m68k m68k

element m68k.data_reg
d0? := m68k.data_reg + 000b
d1? := m68k.data_reg + 001b
d2? := m68k.data_reg + 010b
d3? := m68k.data_reg + 011b
d4? := m68k.data_reg + 100b
d5? := m68k.data_reg + 101b
d6? := m68k.data_reg + 110b
d7? := m68k.data_reg + 111b

element m68k.address_reg
a0? := m68k.address_reg + 000b
a1? := m68k.address_reg + 001b
a2? := m68k.address_reg + 010b
a3? := m68k.address_reg + 011b
a4? := m68k.address_reg + 100b
a5? := m68k.address_reg + 101b
a6? := m68k.address_reg + 110b
a7? := m68k.address_reg + 111b
sp? := m68k.address_reg + 111b

; TODO: Comment
element pc
; TODO: Comment
element sr
; TODO: Comment
element ccr
; TODO: Comment
element usp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Trying to make it work with preprocess.inc                                  ;;
; TODO: Remove the stuff beneath when it's no longer needed.                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

m68k.d0 equ d0
m68k.d1 equ d1
m68k.d2 equ d2
m68k.d3 equ d3
m68k.d4 equ d4
m68k.d5 equ d5
m68k.d6 equ d6
m68k.d7 equ d7

m68k.a0 equ a0
m68k.a1 equ a1
m68k.a2 equ a2
m68k.a3 equ a3
m68k.a4 equ a4
m68k.a5 equ a5
m68k.a6 equ a6
m68k.a7 equ a7