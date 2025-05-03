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

export type Group = {
    instructions: string[];
    variants: InstructionVariant[];
}

export type InstructionSet = Group[];

export const data: InstructionSet = [
  // Immediate to CCR/SR instructions group
  {
    instructions: ["ori", "andi", "eori"],
    variants: [
      // CCR variant
      {
        sizes: ["b"],
        sourceOperands: ["imm"],
        destOperands: ["ccr"]
      },
      // SR variant
      {
        sizes: ["w"],
        sourceOperands: ["imm"],
        destOperands: ["sr"]
      },
      // Standard variant
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["imm"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // Immediate to memory/register instructions
  {
    instructions: ["subi", "addi", "cmpi"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["imm"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // Bit manipulation instructions (register source)
  {
    instructions: ["btst", "bchg", "bclr", "bset"],
    variants: [
      {
        sizes: ["l"],
        sourceOperands: ["dn"],
        destOperands: ["dn"]
      },
      {
        sizes: ["b"],
        sourceOperands: ["dn"],
        destOperands: ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"]
      },
      {
        sizes: ["l"],
        sourceOperands: ["imm"],
        destOperands: ["dn"]
      },
      {
        sizes: ["b"],
        sourceOperands: ["imm"],
        destOperands: ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"]
      }
    ]
  },
  // MOVEP
  {
    instructions: ["movep"],
    variants: [
      {
        sizes: ["w", "l"],
        sourceOperands: ["d(an)"],
        destOperands: ["dn"]
      },
      {
        sizes: ["w", "l"],
        sourceOperands: ["dn"],
        destOperands: ["d(an)"]
      }
    ]
  },
  // MOVEA
  {
    instructions: ["movea"],
    variants: [
      {
        sizes: ["w", "l"],
        sourceOperands: ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["an"]
      }
    ]
  },
  // MOVE
  {
    instructions: ["move"],
    variants: [
      {
        sizes: ["b"],
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "imm", "d(pc)", "d(pc,ix)"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      {
        sizes: ["w", "l"],
        sourceOperands: ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "imm", "d(pc)", "d(pc,ix)"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      {
        sizes: ["w"],
        sourceOperands: ["sr"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      {
        sizes: ["w"],
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["ccr"]
      },
      {
        sizes: ["w"],
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["sr"]
      }
    ]
  },
  // Simple memory/register operations
  {
    instructions: ["negx", "clr", "neg", "not", "tas"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: [],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // Register-only operations
  {
    instructions: ["ext", "swap"],
    variants: [
      {
        sizes: ["w", "l"],
        sourceOperands: [],
        destOperands: ["dn"]
      }
    ]
  },
  // NBCD
  {
    instructions: ["nbcd"],
    variants: [
      {
        sizes: ["b"],
        sourceOperands: [],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // PEA
  {
    instructions: ["pea"],
    variants: [
      {
        sizes: ["l"],
        sourceOperands: ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
        destOperands: []
      }
    ]
  },
  // No operand instructions
  {
    instructions: ["illegal", "reset", "nop", "rte", "rts", "trapv", "rtr"],
    variants: [
      {
        sizes: [""],
        sourceOperands: [],
        destOperands: []
      }
    ]
  },
  // TST
  {
    instructions: ["tst"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: [],
        destOperands: ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"]
      }
    ]
  },
  // TRAP
  {
    instructions: ["trap"],
    variants: [
      {
        sizes: [""],
        sourceOperands: ["imm4"],
        destOperands: []
      }
    ]
  },
  // LINK
  {
    instructions: ["link"],
    variants: [
      {
        sizes: ["w"],
        sourceOperands: ["imm"],
        destOperands: ["an"]
      }
    ]
  },
  // UNLK
  {
    instructions: ["unlk"],
    variants: [
      {
        sizes: [""],
        sourceOperands: [],
        destOperands: ["an"]
      }
    ]
  },
  // MOVE USP
  {
    instructions: ["move usp"],
    variants: [
      {
        sizes: ["l"],
        sourceOperands: ["an"],
        destOperands: ["an"]
      }
    ]
  },
  // STOP
  {
    instructions: ["stop"],
    variants: [
      {
        sizes: [""],
        sourceOperands: ["imm"],
        destOperands: []
      }
    ]
  },
  // Jump instructions
  {
    instructions: ["jsr", "jmp"],
    variants: [
      {
        sizes: [""],
        sourceOperands: ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
        destOperands: []
      }
    ]
  },
  // MOVEM
  {
    instructions: ["movem"],
    variants: [
      {
        sizes: ["w", "l"],
        sourceOperands: ["register_list", "(an)", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
        destOperands: ["register_list", "(an)", "(an)+", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // LEA
  {
    instructions: ["lea"],
    variants: [
      {
        sizes: ["l"],
        sourceOperands: ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
        destOperands: ["an"]
      }
    ]
  },
  // CHK
  {
    instructions: ["chk"],
    variants: [
      {
        sizes: ["w"],
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["dn"]
      }
    ]
  },
  // Quick operations
  {
    instructions: ["addq", "subq"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["imm3"],
        destOperands: ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // MOVEQ
  {
    instructions: ["moveq"],
    variants: [
      {
        sizes: ["l"],
        sourceOperands: ["imm8"],
        destOperands: ["dn"]
      }
    ]
  },
  // Division operations
  {
    instructions: ["divu", "divs"],
    variants: [
      {
        sizes: ["w"],
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["dn"]
      }
    ]
  },
  // Binary-coded decimal operations
  {
    instructions: ["sbcd", "abcd"],
    variants: [
      {
        sizes: ["b"],
        sourceOperands: ["dn", "-(an)"],
        destOperands: ["dn", "-(an)"]
      }
    ]
  },
  // Logical operations
  {
    instructions: ["or", "and"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // Subtraction operations
  {
    instructions: ["sub"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // SUBX
  {
    instructions: ["subx"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["dn", "-(an)"],
        destOperands: ["dn", "-(an)"]
      }
    ]
  },
  // SUBA
  {
    instructions: ["suba"],
    variants: [
      {
        sizes: ["w", "l"],
        sourceOperands: ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["an"]
      }
    ]
  },
  // EOR
  {
    instructions: ["eor"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["dn"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // CMPM
  {
    instructions: ["cmpm"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["(an)+"],
        destOperands: ["(an)+"]
      }
    ]
  },
  // CMP
  {
    instructions: ["cmp"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["dn"]
      }
    ]
  },
  // CMPA
  {
    instructions: ["cmpa"],
    variants: [
      {
        sizes: ["w", "l"],
        sourceOperands: ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["an"]
      }
    ]
  },
  // Multiplication operations
  {
    instructions: ["mulu", "muls"],
    variants: [
      {
        sizes: ["w"],
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["dn"]
      }
    ]
  },
  // EXG
  {
    instructions: ["exg"],
    variants: [
      {
        sizes: ["l"],
        sourceOperands: ["dn", "an"],
        destOperands: ["dn", "an"]
      }
    ]
  },
  // Addition operations
  {
    instructions: ["add"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // ADDX
  {
    instructions: ["addx"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["dn", "-(an)"],
        destOperands: ["dn", "-(an)"]
      }
    ]
  },
  // ADDA
  {
    instructions: ["adda"],
    variants: [
      {
        sizes: ["w", "l"],
        sourceOperands: ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["an"]
      }
    ]
  },
  // Shift/Rotate operations
  {
    instructions: ["asl", "asr", "lsl", "lsr", "roxl", "roxr", "rol", "ror"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["dn", "imm3"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  }
];