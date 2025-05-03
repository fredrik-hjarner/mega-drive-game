// Types for M68k instructions data
export type OperandType = 
  | "dn" | "an" | "(an)" | "(an)+" | "-(an)" | "d(an)" | "d(an,ix)" 
  | "abs.w" | "abs.l" | "d(pc)" | "d(pc,ix)" | "imm" | "imm3" | "imm4" 
  | "imm8" | "label" | "register_list" | "ccr" | "sr";

export type OperandSize = "b" | "w" | "l" | "";

export type InstructionVariant = {
  sizes: OperandSize[];
  sourceOperands: OperandType[];
  destOperands: OperandType[];
};

export type InstructionSet = {
  instructions: {
    [instructionName: string]: InstructionVariant[];
  };
};

export const data: InstructionSet = {
  "instructions": {
        "ori": [
            {
                // CCR variant
                "sizes": ["b"],
                "sourceOperands": ["imm"],
                "destOperands": ["ccr"]
            },
            {
                // SR variant
                "sizes": ["w"],
                "sourceOperands": ["imm"],
                "destOperands": ["sr"]
            },
            {
                // Standard variant
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "andi": [
            {
                // CCR variant
                "sizes": ["b"],
                "sourceOperands": ["imm"],
                "destOperands": ["ccr"]
            },
            {
                // SR variant  
                "sizes": ["w"],
                "sourceOperands": ["imm"],
                "destOperands": ["sr"]
            },
            {
                // Standard variant
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "subi": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "addi": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "eori": [
            {
                // CCR variant
                "sizes": ["b"],
                "sourceOperands": ["imm"],
                "destOperands": ["ccr"]
            },
            {
                // SR variant
                "sizes": ["w"],
                "sourceOperands": ["imm"],
                "destOperands": ["sr"]
            },
            {
                // Standard variant
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "cmpi": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "btst": [
            {
                "sizes": ["l"],
                "sourceOperands": ["dn"],
                "destOperands": ["dn"]
            },
            {
                "sizes": ["b"],
                "sourceOperands": ["dn"],
                "destOperands": [ "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"]
            },
            {
                "sizes": ["l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn"]
            },
            {
                "sizes": ["b"],
                "sourceOperands": ["imm"],
                "destOperands": ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"]
            }
        ],
        "bchg": [
            {
                "sizes": ["l"],
                "sourceOperands": ["dn"],
                "destOperands": ["dn"]
            },
            {
                "sizes": ["b"],
                "sourceOperands": ["dn"],
                "destOperands": [ "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            },
            {
                "sizes": ["l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn"]
            },
            {
                "sizes": ["b"],
                "sourceOperands": ["imm"],
                "destOperands": ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "bclr": [
            {
                "sizes": ["l"],
                "sourceOperands": ["dn"],
                "destOperands": ["dn"]
            },
            {
                "sizes": ["b"],
                "sourceOperands": ["dn"],
                "destOperands": [ "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            },
            {
                "sizes": ["l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn"]
            },
            {
                "sizes": ["b"],
                "sourceOperands": ["imm"],
                "destOperands": ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "bset": [
            {
                "sizes": ["l"],
                "sourceOperands": ["dn"],
                "destOperands": ["dn"]
            },
            {
                "sizes": ["b"],
                "sourceOperands": ["dn"],
                "destOperands": [ "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            },
            {
                "sizes": ["l"],
                "sourceOperands": ["imm"],
                "destOperands": ["dn"]
            },
            {
                "sizes": ["b"],
                "sourceOperands": ["imm"],
                "destOperands": ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "movep": [
            {
                "sizes": ["w", "l"],
                "sourceOperands": ["d(an)"],
                "destOperands": ["dn"]
            },
            {
                "sizes": ["w", "l"],
                "sourceOperands": ["dn"],
                "destOperands": ["d(an)"]
            },
        ],
        "movea": [
            {
                "sizes": ["w", "l"],
                "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["an"]
            }
        ],
        "move": [
            {
                "sizes": ["b"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "imm", "d(pc)", "d(pc,ix)"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            },
            {
                "sizes": ["w", "l"],
                "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "imm", "d(pc)", "d(pc,ix)"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            },
            {
                "sizes": ["w"],
                "sourceOperands": ["sr"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            },
            {
                "sizes": ["w"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["ccr"]
            },
            {
                "sizes": ["w"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["sr"]
            }
        ],
        "negx": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": [],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "clr": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": [],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "neg": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": [],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "not": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": [],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "ext": [
            {
                "sizes": ["w", "l"],
                "sourceOperands": [],
                "destOperands": ["dn"]
            }
        ],
        "nbcd": [
            {
                "sizes": ["b"],
                "sourceOperands": [],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "swap": [
            {
                "sizes": ["w"],
                "sourceOperands": [],
                "destOperands": ["dn"]
            }
        ],
        "pea": [
            {
                "sizes": ["l"],
                "sourceOperands": ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
                "destOperands": []
            }
        ],
        "illegal": [
            {
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": []
            }
        ],
        "tas": [
            {
                "sizes": ["b"],
                "sourceOperands": [],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "tst": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": [],
                "destOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"]
            }
        ],
        "trap": [
            {
                "sizes": [""],
                "sourceOperands": ["imm4"],
                "destOperands": []
            }
        ],
        "link": [
            {
                "sizes": ["w"],
                "sourceOperands": ["imm"],
                "destOperands": ["an"]
            }
        ],
        "unlk": [
            {
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": ["an"]
            }
        ],
        "move usp": [
            {
                "sizes": ["l"],
                "sourceOperands": ["an"],
                "destOperands": ["an"]
            }
        ],
        "reset": [
            {
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": []
            }
        ],
        "nop": [
            {
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": []
            }
        ],
        "stop": [
            {
                "sizes": [""],
                "sourceOperands": ["imm"],
                "destOperands": []
            }
        ],
        "rte": [
            {
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": []
            }
        ],
        "rts": [
            {
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": []
            }
        ],
        "trapv": [
            {
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": []
            }
        ],
        "rtr": [
            {
                "sizes": [""],
                "sourceOperands": [],
                "destOperands": []
            }
        ],
        "jsr": [
            {
                "sizes": [""],
                "sourceOperands": ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
                "destOperands": []
            }
        ],
        "jmp": [
            {
                "sizes": [""],
                "sourceOperands": ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
                "destOperands": []
            }
        ],
        "movem": [
            {
                "sizes": ["w", "l"],
                "sourceOperands": ["register_list", "(an)", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
                "destOperands": ["register_list", "(an)", "(an)+", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "lea": [
            {
                "sizes": ["l"],
                "sourceOperands": ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
                "destOperands": ["an"]
            }
        ],
        "chk": [
            {
                "sizes": ["w"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn"]
            }
        ],
        "addq": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm3"],
                "destOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "subq": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["imm3"],
                "destOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "moveq": [
            {
                "sizes": ["l"],
                "sourceOperands": ["imm8"],
                "destOperands": ["dn"]
            }
        ],
        "divu": [
            {
                "sizes": ["w"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn"]
            }
        ],
        "divs": [
            {
                "sizes": ["w"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn"]
            }
        ],
        "sbcd": [
            {
                "sizes": ["b"],
                "sourceOperands": ["dn", "-(an)"],
                "destOperands": ["dn", "-(an)"]
            }
        ],
        "or": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "sub": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "subx": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "-(an)"],
                "destOperands": ["dn", "-(an)"]
            }
        ],
        "suba": [
            {
                "sizes": ["w", "l"],
                "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["an"]
            }
        ],
        "eor": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "cmpm": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["(an)+"],
                "destOperands": ["(an)+"]
            }
        ],
        "cmp": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn"]
            }
        ],
        "cmpa": [
            {
                "sizes": ["w", "l"],
                "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["an"]
            }
        ],
        "mulu": [
            {
                "sizes": ["w"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn"]
            }
        ],
        "muls": [
            {
                "sizes": ["w"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn"]
            }
        ],
        "abcd": [
            {
                "sizes": ["b"],
                "sourceOperands": ["dn", "-(an)"],
                "destOperands": ["dn", "-(an)"]
            }
        ],
        "exg": [
            {
                "sizes": ["l"],
                "sourceOperands": ["dn", "an"],
                "destOperands": ["dn", "an"]
            }
        ],
        "and": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "add": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "addx": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "-(an)"],
                "destOperands": ["dn", "-(an)"]
            }
        ],
        "adda": [
            {
                "sizes": ["w", "l"],
                "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
                "destOperands": ["an"]
            }
        ],
        "asl": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "asr": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "lsl": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "lsr": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "roxl": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "roxr": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "rol": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ],
        "ror": [
            {
                "sizes": ["b", "w", "l"],
                "sourceOperands": ["dn", "imm3"],
                "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
            }
        ]
    }
};