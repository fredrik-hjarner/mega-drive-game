; =====================================================================
; ROM METADATA
; 
; =====================================================================
    dc.b "SEGA GENESIS    "      ; 16 bytes: Console name
    dc.b "(C)SEGA 2025.MAR"      ; 16 bytes: Copyright/date
    dc.b "HELLO WORLD DEMO                                 " ; 49 bytes: Domestic name
    dc.b "HELLO WORLD DEMO                                 " ; 49 bytes: International name
    dc.b "GM XXXXXXXX-XX"        ; 14 bytes: Version number
    dc.w $0000                   ; 2 bytes: Checksum
    dc.b "J               "      ; 1 byte: I/O support
    dc.l $00000000               ; 4 bytes: ROM start address
    dc.l $00100000               ; 4 bytes: ROM end address
    dc.l $00FF0000               ; 4 bytes: Start of RAM
    dc.l $00FFFFFF               ; 4 bytes: End of RAM
    dc.l $00000000               ; 4 bytes: SRAM enabled
    dc.l $00000000               ; 4 bytes: Unused
    dc.l $00000000               ; 4 bytes: Unused
    dc.l $00000000               ; 4 bytes: Unused
    dc.b "                                        "         ; 40 bytes: Notes
    dc.b "JUE             "      ; 27 bytes: Country codes