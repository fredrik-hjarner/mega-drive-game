;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ALIAS MACROS FOR INSTRUCTIONS THAT ONLY HAVE ONE SIZE                      ;;
;; TODO: Would these be faster as calminstructions??                          ;;
;; TODO: Setting boolean to enable/disable these??                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; TODO: ori to ccr

;; TODO: ori to sr

;; TODO: andi to ccr

;; TODO: andi to sr

;; TODO: eori to ccr

;; TODO: eori to sr

;; TODO: move from sr

;; TODO: move to ccr

;; TODO: move to sr

macro nbcd line&
    nbcd.b line
end macro

macro swap line&
    swap.w line
end macro

macro pea line&
    pea.l line
end macro

macro tas line&
    tas.b line
end macro

macro link line&
    link.w line
end macro

;; TODO: move usp

macro lea line&
    lea.l line
end macro

macro chk line&
    chk.w line
end macro

;; TODO: Add Scc here.

;; TODO: Add DBcc here.

macro moveq line&
    moveq.l line
end macro

macro divu line&
    divu.w line
end macro

macro divs line&
    divs.w line
end macro

macro sbcd line&
    sbcd.b line
end macro

;mulu
;muls
;abcd
;exg

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; SOME INSTRUCTIONS CAN HAVE .S SUFFIX INSTEAD OF .B                         ;;
;; TODO: Which instructions? All, some?                                       ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro bra.s line&
    bra.b line
end macro

macro bsr.s line&
    bsr.b line
end macro