// Types for M68k instructions data
export type OperandType = 
    | "dn" | "an" | "(an)" | "(an)+" | "-(an)" | "d(an)" | "d(an,ix)" 
    | "abs.w" | "abs.l" | "d(pc)" | "d(pc,ix)" | "imm" | "imm3" | "imm4" 
    | "imm8" | "imm8s" | "imm16" | "label" | "register_list" | "ccr" | "sr";

export type OperandSize = "b" | "w" | "l" | "s" | "";

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
  // Bit manipulation instructions - BTST (supports PC-relative addressing)
  {
    instructions: ["btst"],
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
        sourceOperands: ["imm8"],
        destOperands: ["dn"]
      },
      {
        sizes: ["b"],
        sourceOperands: ["imm"],
        destOperands: ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"]
      }
    ]
  },
  // Bit manipulation instructions - BCHG, BCLR, BSET (no PC-relative addressing)
  {
    instructions: ["bchg", "bclr", "bset"],
    variants: [
      {
        sizes: ["l"],
        sourceOperands: ["dn"],
        destOperands: ["dn"]
      },
      {
        sizes: ["b"],
        sourceOperands: ["dn"],
        destOperands: ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      {
        sizes: ["l"],
        sourceOperands: ["imm8"],
        destOperands: ["dn"]
      },
      {
        sizes: ["b"],
        sourceOperands: ["imm"],
        destOperands: ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // Set according to condition (Scc) instructions
  {
    instructions: ["st", "sf", "shi", "sls", "scc", "scs", "sne", "seq", "svc", "svs", "spl", "smi", "sge", "slt", "sgt", "sle", "shs", "slo"],
    variants: [
      {
        sizes: ["b"],
        sourceOperands: [],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // Branch instructions
  {
    instructions: ["bra", "bsr", "bhi", "bls", "bcc", "bcs", "bne", "beq", "bvc", "bvs", "bpl", "bmi", "bge", "blt", "bgt", "ble", "bhs", "blo"],
    variants: [
      {
        sizes: ["s", "w"],
        sourceOperands: ["label"],
        destOperands: []
      }
    ]
  },
  // DBcc instructions
  {
    instructions: ["dbt", "dbf", "dbhi", "dbls", "dbcc", "dbcs", "dbne", "dbeq", "dbvc", "dbvs", "dbpl", "dbmi", "dbge", "dblt", "dbgt", "dble", "dbhs", "dblo"],
    variants: [
      {
        sizes: ["w"],
        sourceOperands: ["dn"],
        destOperands: ["label"]
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
      },
      // MOVE USP
      {
        sizes: ["l"],
        sourceOperands: ["an"],
        destOperands: ["an"]
      }
    ]
  },
  // Simple memory/register operations (negx, clr, neg, not)
  {
    instructions: ["negx", "clr", "neg", "not"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: [],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // TAS instruction (byte only)
  {
    instructions: ["tas"],
    variants: [
      {
        sizes: ["b"],
        sourceOperands: [],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // Register-only operations
  {
    instructions: ["ext"],
    variants: [
      {
        sizes: ["w", "l"],
        sourceOperands: [],
        destOperands: ["dn"]
      }
    ]
  },
  // SWAP instruction (no size suffix)
  {
    instructions: ["swap"],
    variants: [
      {
        sizes: [""],
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
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
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
        sourceOperands: ["an"],
        destOperands: ["imm"]
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
  // STOP
  {
    instructions: ["stop"],
    variants: [
      {
        sizes: [""],
        sourceOperands: ["imm16"],
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
  // MOVEM // verified
  {
    instructions: ["movem"],
    variants: [ // verified
      {
        sizes: ["w", "l"], // verified
        sourceOperands: ["register_list"], // verified
        destOperands: ["(an)", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      {
        sizes: ["w", "l"], // verified
        sourceOperands: ["(an)", "(an)+", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"], // verified
        destOperands: ["register_list"] // verified
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
  // Quick operations // verified
  {
    instructions: ["addq", "subq"], // verified
    variants: [ // verified
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["imm3"], // verified
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"] // verified
      },
      {
        sizes: ["w", "l"], // verified
        sourceOperands: ["imm3"], // verified
        destOperands: ["an"] // verified
      },
    ]
  },
  // MOVEQ
  {
    instructions: ["moveq"],
    variants: [
      {
        sizes: ["l"],
        sourceOperands: ["imm8s"],
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
        sourceOperands: ["dn"],
        destOperands: ["dn"]
      },
      {
        sizes: ["b"],
        sourceOperands: ["-(an)"],
        destOperands: ["-(an)"]
      },
    ]
  },
  // Logical operations // verified
  {
    instructions: ["or", "and"], // verified
    variants: [
      {
        sizes: ["b", "w", "l"], // verified
        // TODO: This includes "imm"???
        // https://github.com/prb28/m68k-instructions-documentation/blob/master/instructions/and.md
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"], // verified
        destOperands: ["dn"] // verified
      },
      {
        sizes: ["b", "w", "l"], // verified
        sourceOperands: ["dn"], // verified
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"] // verified
      },
    ]
  },
  {
    instructions: ["sub", "add"], // verified
    variants: [
      {
        sizes: ["b", "w", "l"], // verified
        // TODO: This includes "imm"???
        // https://github.com/prb28/m68k-instructions-documentation/blob/master/instructions/add.md
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"], // verified
        destOperands: ["dn"] // verified
      },
      {
        sizes: ["w", "l"], // verified
        sourceOperands: ["an"], // verified
        destOperands: ["dn"] // verified
      },
      {
        sizes: ["b", "w", "l"], // verified
        sourceOperands: ["dn"], // verified
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"] // verified
      }
    ]
  },
  {
    instructions: ["subx", "addx"], // verified
    variants: [
      {
        sizes: ["b", "w", "l"], // verified
        sourceOperands: ["dn"], // verified
        destOperands: ["dn"] // verified
      },
      {
        sizes: ["b", "w", "l"], // verified
        sourceOperands: ["-(an)"], // verified
        destOperands: ["-(an)"] // verified
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
    instructions: ["cmp"], // verified
    variants: [
      {
        sizes: ["b", "w", "l"], // verified
        // TODO: This includes "imm"???
        // https://github.com/prb28/m68k-instructions-documentation/blob/master/instructions/cmp.md
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"], // verified
        destOperands: ["dn"] // verified
      },
      {
        sizes: ["w", "l"], // verified
        sourceOperands: [ "an"], // verified
        destOperands: ["dn"] // verified
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
        destOperands: ["dn"]
      },
      {
        sizes: ["w"],
        sourceOperands: [],
        destOperands: ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  }
];