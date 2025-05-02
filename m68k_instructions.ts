export const data = {
  "instructions": {
        "ori": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["imm"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "andi": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["imm"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "subi": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["imm"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "addi": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["imm"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "eori": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["imm"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "cmpi": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["imm"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "btst": {
            "sizes": ["b", "l"],
            "sourceOperands": ["dn", "imm"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "bchg": {
            "sizes": ["b", "l"],
            "sourceOperands": ["dn", "imm"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "bclr": {
            "sizes": ["b", "l"],
            "sourceOperands": ["dn", "imm"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "bset": {
            "sizes": ["b", "l"],
            "sourceOperands": ["dn", "imm"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "movep": {
            "sizes": ["w", "l"],
            "sourceOperands": ["dn", "d(an)"],
            "destOperands": ["dn", "d(an)"]
        },
        "movea": {
            "sizes": ["w", "l"],
            "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["an"]
        },
        "move": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "negx": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "clr": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "neg": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "not": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "ext": {
            "sizes": ["w", "l"],
            "sourceOperands": [],
            "destOperands": ["dn"]
        },
        "nbcd": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "swap": {
            "sizes": ["w"],
            "sourceOperands": [],
            "destOperands": ["dn"]
        },
        "pea": {
            "sizes": ["l"],
            "sourceOperands": ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
            "destOperands": []
        },
        "illegal": {
            "sizes": [""],
            "sourceOperands": [],
            "destOperands": []
        },
        "tas": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "tst": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": [],
            "destOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"]
        },
        "trap": {
            "sizes": [""],
            "sourceOperands": ["imm4"],
            "destOperands": []
        },
        "link": {
            "sizes": ["w"],
            "sourceOperands": ["imm"],
            "destOperands": ["an"]
        },
        "unlk": {
            "sizes": [""],
            "sourceOperands": [],
            "destOperands": ["an"]
        },
        "move usp": {
            "sizes": ["l"],
            "sourceOperands": ["an"],
            "destOperands": ["an"]
        },
        "reset": {
            "sizes": [""],
            "sourceOperands": [],
            "destOperands": []
        },
        "nop": {
            "sizes": [""],
            "sourceOperands": [],
            "destOperands": []
        },
        "stop": {
            "sizes": [""],
            "sourceOperands": ["imm"],
            "destOperands": []
        },
        "rte": {
            "sizes": [""],
            "sourceOperands": [],
            "destOperands": []
        },
        "rts": {
            "sizes": [""],
            "sourceOperands": [],
            "destOperands": []
        },
        "trapv": {
            "sizes": [""],
            "sourceOperands": [],
            "destOperands": []
        },
        "rtr": {
            "sizes": [""],
            "sourceOperands": [],
            "destOperands": []
        },
        "jsr": {
            "sizes": [""],
            "sourceOperands": ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
            "destOperands": []
        },
        "jmp": {
            "sizes": [""],
            "sourceOperands": ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
            "destOperands": []
        },
        "movem": {
            "sizes": ["w", "l"],
            "sourceOperands": ["register_list", "(an)", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
            "destOperands": ["register_list", "(an)", "(an)+", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "lea": {
            "sizes": ["l"],
            "sourceOperands": ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
            "destOperands": ["an"]
        },
        "chk": {
            "sizes": ["w"],
            "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["dn"]
        },
        "addq": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["imm3"],
            "destOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "subq": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["imm3"],
            "destOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "st": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "sf": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "shi": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "sls": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "scc": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "scs": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "sne": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "seq": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "svc": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "svs": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "spl": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "smi": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "sge": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "slt": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "sgt": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "sle": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "shs": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "slo": {
            "sizes": ["b"],
            "sourceOperands": [],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "dbt": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dbf": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dbhi": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dbls": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dbcc": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dbcs": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dbne": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dbeq": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dbvc": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dbvs": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dbpl": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dbmi": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dbge": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dblt": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dbgt": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dble": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dbhs": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "dblo": {
            "sizes": ["w"],
            "sourceOperands": ["label"],
            "destOperands": ["dn"]
        },
        "bra": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "bsr": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "bhi": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "bls": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "bcc": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "bcs": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "bne": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "beq": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "bvc": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "bvs": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "bpl": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "bmi": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "bge": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "blt": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "bgt": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "ble": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "bhs": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "blo": {
            "sizes": ["b", "w"],
            "sourceOperands": ["label"],
            "destOperands": []
        },
        "moveq": {
            "sizes": ["l"],
            "sourceOperands": ["imm8"],
            "destOperands": ["dn"]
        },
        "divu": {
            "sizes": ["w"],
            "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["dn"]
        },
        "divs": {
            "sizes": ["w"],
            "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["dn"]
        },
        "sbcd": {
            "sizes": ["b"],
            "sourceOperands": ["dn", "-(an)"],
            "destOperands": ["dn", "-(an)"]
        },
        "or": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "sub": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "subx": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "-(an)"],
            "destOperands": ["dn", "-(an)"]
        },
        "suba": {
            "sizes": ["w", "l"],
            "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["an"]
        },
        "eor": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "cmpm": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["(an)+"],
            "destOperands": ["(an)+"]
        },
        "cmp": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["dn"]
        },
        "cmpa": {
            "sizes": ["w", "l"],
            "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["an"]
        },
        "mulu": {
            "sizes": ["w"],
            "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["dn"]
        },
        "muls": {
            "sizes": ["w"],
            "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["dn"]
        },
        "abcd": {
            "sizes": ["b"],
            "sourceOperands": ["dn", "-(an)"],
            "destOperands": ["dn", "-(an)"]
        },
        "exg": {
            "sizes": ["l"],
            "sourceOperands": ["dn", "an"],
            "destOperands": ["dn", "an"]
        },
        "and": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "add": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "addx": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "-(an)"],
            "destOperands": ["dn", "-(an)"]
        },
        "adda": {
            "sizes": ["w", "l"],
            "sourceOperands": ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
            "destOperands": ["an"]
        },
        "asl": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "imm3"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "asr": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "imm3"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "lsl": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "imm3"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "lsr": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "imm3"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "roxl": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "imm3"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "roxr": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "imm3"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "rol": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "imm3"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        },
        "ror": {
            "sizes": ["b", "w", "l"],
            "sourceOperands": ["dn", "imm3"],
            "destOperands": ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
        }
    }
};