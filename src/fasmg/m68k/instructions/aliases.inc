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