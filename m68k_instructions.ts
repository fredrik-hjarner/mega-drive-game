export const data = {
  "instructions": {
        "ori": [
            {
                // CCR variant
                "variant": "to_ccr",
                "sizes": ["b"],
                "sourceOperands": ["imm"],
                "destOperands": ["ccr"]
            },
            {
                // SR variant
                "variant": "to_sr",
                "sizes": ["w"],
                "sourceOperands": ["imm"],
                "destOperands": ["sr"]
            },
            {
                // Standard variant
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "andi": [
            {
                // CCR variant
                "variant": "to_ccr",
                "sizes": ["b"],
                "sourceOperands": ["imm"],
                "destOperands": ["ccr"]
            },
            {
                // SR variant  
                "variant": "to_sr",
                "sizes": ["w"],
                "sourceOperands": ["imm"],
                "destOperands": ["sr"]
            },
            {
                // Standard variant
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "subi": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "addi": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "eori": [
            {
                // CCR variant
                "variant": "to_ccr",
                "sizes": ["b"],
                "sourceOperands": ["imm"],
                "destOperands": ["ccr"]
            },
            {
                // SR variant
                "variant": "to_sr",
                "sizes": ["w"],
                "sourceOperands": ["imm"],
                "destOperands": ["sr"]
            },
            {
                // Standard variant
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "cmpi": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "btst": [
            {
                "variant": "register",
                "sizes": ["b", "l"],
                "sourceOperands": ["dn"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"]
            },
            {
                "variant": "immediate",
                "sizes": ["b", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"]
            }
        ],
        "bchg": [
            {
                "variant": "register",
                "sizes": ["b", "l"],
                "sourceOperands": ["dn"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            },
            {
                "variant": "immediate",
                "sizes": ["b", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "bclr": [
            {
                "variant": "register",
                "sizes": ["b", "l"],
                "sourceOperands": ["dn"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            },
            {
                "variant": "immediate",
                "sizes": ["b", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "bset": [
            {
                "variant": "register",
                "sizes": ["b", "l"],
                "sourceOperands": ["dn"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            },
            {
                "variant": "immediate",
                "sizes": ["b", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "movep": [
            {
                "variant": "standard",
                "sizes": ["w", "l"],
                "sourceOperands": ["dn", "d(an)"],
                "destOperands": ["dn", "d(an)"]
            }
        ],
        "movea": [
            {
                "variant": "standard",
                "sizes": ["w", "l"],
                "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["an"]
            }
        ],
        "move": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            },
            {
                "variant": "from_sr",
                "sizes": ["w"],
                "sourceOperands": ["sr"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            },
            {
                "variant": "to_ccr",
                "sizes": ["w"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["ccr"]
            },
            {
                "variant": "to_sr",
                "sizes": ["w"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["sr"]
            }
        ],
        "negx": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": [],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "clr": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": [],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "neg": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": [],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "not": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": [],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "ext": [
            {
                "variant": "standard",
                "sizes": ["w", "l"],
                "sourceOperands": [],
                "destOperands": ["dn"]
            }
        ],
        "nbcd": [
            {
                "variant": "standard",
                "sizes": ["b"],
                "sourceOperands": [],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "swap": [
            {
                "variant": "standard",
                "sizes": ["w"],
                "sourceOperands": [],
                "destOperands": ["dn"]
            }
        ],
        "pea": [
            {
                "variant": "standard",
                "sizes": ["l"],
                "sourceOperands": ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
                "destOperands": []
            }
        ],
        "illegal": [
            {
                "variant": "standard",
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": []
            }
        ],
        "tas": [
            {
                "variant": "standard",
                "sizes": ["b"],
                "sourceOperands": [],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "tst": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": [],
                "destOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"]
            }
        ],
        "trap": [
            {
                "variant": "standard",
                "sizes": [""],
                "sourceOperands": ["imm4"],
                "destOperands": []
            }
        ],
        "link": [
            {
                "variant": "standard",
                "sizes": ["w"],
                "sourceOperands": ["imm"],
                "destOperands": ["an"]
            }
        ],
        "unlk": [
            {
                "variant": "standard",
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": ["an"]
            }
        ],
        "move usp": [
            {
                "variant": "standard",
                "sizes": ["l"],
                "sourceOperands": ["an"],
                "destOperands": ["an"]
            }
        ],
        "reset": [
            {
                "variant": "standard",
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": []
            }
        ],
        "nop": [
            {
                "variant": "standard",
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": []
            }
        ],
        "stop": [
            {
                "variant": "standard",
                "sizes": [""],
                "sourceOperands": ["imm"],
                "destOperands": []
            }
        ],
        "rte": [
            {
                "variant": "standard",
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": []
            }
        ],
        "rts": [
            {
                "variant": "standard",
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": []
            }
        ],
        "trapv": [
            {
                "variant": "standard",
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": []
            }
        ],
        "rtr": [
            {
                "variant": "standard",
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": []
            }
        ],
        "jsr": [
            {
                "variant": "standard",
                "sizes": [""],
                "sourceOperands": ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
                "destOperands": []
            }
        ],
        "jmp": [
            {
                "variant": "standard",
                "sizes": [""],
                "sourceOperands": ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
                "destOperands": []
            }
        ],
        "movem": [
            {
                "variant": "standard",
                "sizes": ["w", "l"],
                "sourceOperands": ["register_list", "(an)", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
                "destOperands": ["register_list", "(an)", "(an)+", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "lea": [
            {
                "variant": "standard",
                "sizes": ["l"],
                "sourceOperands": ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
                "destOperands": ["an"]
            }
        ],
        "chk": [
            {
                "variant": "standard",
                "sizes": ["w"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn"]
            }
        ],
        "addq": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm3"],
                "destOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "subq": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm3"],
                "destOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "moveq": [
            {
                "variant": "standard",
                "sizes": ["l"],
                "sourceOperands": ["imm8"],
                "destOperands": ["dn"]
            }
        ],
        "divu": [
            {
                "variant": "standard",
                "sizes": ["w"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn"]
            }
        ],
        "divs": [
            {
                "variant": "standard",
                "sizes": ["w"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn"]
            }
        ],
        "sbcd": [
            {
                "variant": "standard",
                "sizes": ["b"],
                "sourceOperands": ["dn", "-(an)"],
                "destOperands": ["dn", "-(an)"]
            }
        ],
        "or": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "sub": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "subx": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "-(an)"],
                "destOperands": ["dn", "-(an)"]
            }
        ],
        "suba": [
            {
                "variant": "standard",
                "sizes": ["w", "l"],
                "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["an"]
            }
        ],
        "eor": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "cmpm": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["(an)+"],
                "destOperands": ["(an)+"]
            }
        ],
        "cmp": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn"]
            }
        ],
        "cmpa": [
            {
                "variant": "standard",
                "sizes": ["w", "l"],
                "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["an"]
            }
        ],
        "mulu": [
            {
                "variant": "standard",
                "sizes": ["w"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn"]
            }
        ],
        "muls": [
            {
                "variant": "standard",
                "sizes": ["w"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn"]
            }
        ],
        "abcd": [
            {
                "variant": "standard",
                "sizes": ["b"],
                "sourceOperands": ["dn", "-(an)"],
                "destOperands": ["dn", "-(an)"]
            }
        ],
        "exg": [
            {
                "variant": "standard",
                "sizes": ["l"],
                "sourceOperands": ["dn", "an"],
                "destOperands": ["dn", "an"]
            }
        ],
        "and": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "add": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "addx": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "-(an)"],
                "destOperands": ["dn", "-(an)"]
            }
        ],
        "adda": [
            {
                "variant": "standard",
                "sizes": ["w", "l"],
                "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["an"]
            }
        ],
        "asl": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "asr": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "lsl": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "lsr": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "roxl": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "roxr": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "rol": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "ror": [
            {
                "variant": "standard",
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ]
    }
};