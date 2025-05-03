#!/usr/bin/env bun
// Generate M68K instruction tests using Bun
// This script generates test cases for 68K assembly instructions

// Load instruction definitions from TypeScript file
import { data } from './m68k_instructions.ts';
const instructionsData = data;

// Function to generate example values for each operand type, with size awareness
function getExampleValue(operandType, size = '', instr) {
  switch(operandType) {
    case "dn": return "d5";
    case "an": return "a2";
    case "(an)": return "(a2)";
    case "(an)+": return "(a2)+";
    case "-(an)": return "-(a2)";
    case "d(an)": return "$7FFF(a2)";
    case "d(an,ix)": return "$7F(a2,d5.w)";
    case "abs.w": return "($FFFFFFFF).w";
    case "abs.l": return "($FFFFFFFF).l";
    case "d(pc)": return "@(pc)";
    case "d(pc,ix)": return "@(pc,d5.w)";
    case "imm":
      if (['btst', 'bchg', 'bclr'].includes(instr)) {
        return "#0";
      }
      if (size === 'b') return "#$FF";
      if (size === 'w') return "#$FFFF";
      if (size === 'l') return "#$FFFFFFFF";
      return "#$FF"; // default
    case "imm3": return "#1";
    case "imm4": return "#2";
    case "imm8": return "#0";
    case "label": return "@";
    case "register_list": return "d5-a7";
    case "ccr": return "ccr";
    case "sr": return "sr";
    default: return "";
  }
}

// Generate valid test cases
function generateValidTests() {
  let output = "";
  let previousInstrName = ""; // Track the previous instruction name
  
  // Process each instruction
  for (const [instrName, instrVariants] of Object.entries(instructionsData.instructions)) {
    // Add a newline between different instructions
    if (previousInstrName && previousInstrName !== instrName) {
      output += "\n";
    }
    
    // Process variants
    for (const variant of instrVariants) {
      // Handle instructions with no operands
      if (variant.sourceOperands.length === 0 && variant.destOperands.length === 0) {
        output += `\t${instrName}\n`;
        continue;
      }
      
      // Process sizes for this variant
      for (const size of variant.sizes) {
        const sizeSuffix = size ? `.${size}` : '';
        
        // Single operand instructions (dest only)
        if (variant.sourceOperands.length === 0 && variant.destOperands.length > 0) {        
          for (const destOp of variant.destOperands) {
            const destExample = getExampleValue(destOp, size, instrName);
            output += `\t${instrName}${sizeSuffix}\t${destExample}\n`;
          }
        }
        // Source-only instructions (like branch)
        else if (variant.sourceOperands.length > 0 && variant.destOperands.length === 0) {
          for (const srcOp of variant.sourceOperands) {
            const srcExample = getExampleValue(srcOp, size, instrName);
            output += `\t${instrName}${sizeSuffix}\t${srcExample}\n`;
          }
        }
        // Two-operand instructions - systematically generate all combinations
        else if (variant.sourceOperands.length > 0 && variant.destOperands.length > 0) {
          // Generate all combinations
          for (const srcOp of variant.sourceOperands) {
            const srcExample = getExampleValue(srcOp, size, instrName);
            
            for (const destOp of variant.destOperands) {
              const destExample = getExampleValue(destOp, size, instrName);
              output += `\t${instrName}${sizeSuffix}\t${srcExample},${destExample}\n`;
            }
          }
        }
      }
      
      // For bit manipulation and other instructions, also generate without size specifier
      if (['btst', 'bchg', 'bclr', 'bset'].includes(instrName)) {
        for (const srcOp of variant.sourceOperands) {
          const srcExample = getExampleValue(srcOp, '', instrName);
          
          for (const destOp of variant.destOperands) {
            const destExample = getExampleValue(destOp, '', instrName);
            output += `\t${instrName}\t${srcExample},${destExample}\n`;
          }
        }
      }
    }
    
    previousInstrName = instrName;
  }
  
  // Add end marker
  output += `\n\trts\n`;
  
  return output;
}

// Main function to generate test files
function generateTestFiles() {
  const validTests = generateValidTests();
  
  // Define output path
  const validTestsPath = './valid_instructions.asm';
  
  // Write file using Node.js fs module which Bun supports
  const fs = require('fs');
  fs.writeFileSync(validTestsPath, validTests);
  console.log(`Valid tests written to: ${validTestsPath}`);
}

// Run the generator
generateTestFiles(); 