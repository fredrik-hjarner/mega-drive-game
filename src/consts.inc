; vdp ports
vdp_data  equ $C00000
vdp_data2 equ $C00002
vdp_ctrl  equ $C00004
vdp_ctrl2 equ $C00006

; name tables addresses
vram_hscroll_addr equ $0400
vram_plane_a_addr equ $2000

; tile data addresses
vdp_tiles_addr equ $0000

; gampads
gamepad1_ctrl equ $A10009
gamepad1_data equ $A10003
gamepad2_ctrl equ $A1000B
gamepad2_data equ $A10005

; buttons
; Do logical AND with these to check if the button is pressed
; button_up    equ %00000001
; button_down  equ %00000010
; button_left  equ %00000100
; button_right equ %00001000
; button_b     equ %00010000
; button_c     equ %00100000
; button_a     equ %01000000
; button_start equ %10000000