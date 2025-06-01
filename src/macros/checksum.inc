virtual at 0 as 'checksum'
    checksum_area::
    rb 5
end virtual

; Checksum is word (i.e. 16 bits)
; It's calculated by summing the values of all bytes from $200 to the end of ROM
calminstruction calc_checksum
        local tmp
        local offset
        local rom_end
        local sum
        local checksum_offset

        compute offset, $200
        compute rom_end, $
        compute sum, 0
        compute checksum_offset, checksum
    loop:
        check offset < rom_end
        jno store_checksum
        load_be tmp, offset, 2
        compute sum, sum + tmp
        compute offset, offset + 2 ; + 2 because we check word by word
        jump loop
    store_checksum:
        compute tmp, sum and $FFFF
        store_be checksum_offset, 2, tmp

        arrange tmp, tmp
        stringify tmp
        store checksum_area:0, lengthof tmp, tmp
end calminstruction

postpone ?
        calc_checksum
end postpone