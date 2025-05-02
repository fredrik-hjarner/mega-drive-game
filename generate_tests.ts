#!/usr/bin/env bun
// Generate M68K instruction tests using Bun
// This script generates test cases for 68K assembly instructions

// Load instruction definitions from TypeScript file
import { data } from './m68k_instructions.ts';
const instructionsData = data;

// Function to generate example values for each operand type
function getExampleValue(operandType) {
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
    case "imm": return "#$FF";
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
    
    // Process each variant of the instruction
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
            const destExample = getExampleValue(destOp);
            output += `\t${instrName}${sizeSuffix}\t${destExample}\n`;
          }
        }
        // Source-only instructions (like branch)
        else if (variant.sourceOperands.length > 0 && variant.destOperands.length === 0) {
          for (const srcOp of variant.sourceOperands) {
            const srcExample = getExampleValue(srcOp);
            output += `\t${instrName}${sizeSuffix}\t${srcExample}\n`;
          }
        }
        // Two-operand instructions
        else if (variant.sourceOperands.length > 0 && variant.destOperands.length > 0) {
          // Special case for immediate instructions (ori to ccr, etc.)
          if (variant.variant === "to_ccr" || variant.variant === "to_sr") {
            const immediate = size === 'b' ? '#$FF' : '#$FFFF';
            output += `\t${instrName}${sizeSuffix}\t${immediate},${getExampleValue(variant.destOperands[0])}\n`;
            // Also generate without size (e.g., "ori #$FF,ccr")
            output += `\t${instrName}\t${immediate},${getExampleValue(variant.destOperands[0])}\n`;
          }
          // Regular two-operand instructions
          else {
            // Only generate a reasonable number of examples to avoid huge test files
            const maxSrcExamples = 3;
            const maxDestExamples = 3;
            
            for (let i = 0; i < Math.min(variant.sourceOperands.length, maxSrcExamples); i++) {
              const srcOp = variant.sourceOperands[i];
              const srcExample = getExampleValue(srcOp);
              
              for (let j = 0; j < Math.min(variant.destOperands.length, maxDestExamples); j++) {
                const destOp = variant.destOperands[j];
                const destExample = getExampleValue(destOp);
                
                output += `\t${instrName}${sizeSuffix}\t${srcExample},${destExample}\n`;
              }
            }
          }
        }
      }
      
      // For bit manipulation and other instructions, also generate without size specifier
      if (['btst', 'bchg', 'bclr', 'bset'].includes(instrName)) {
        for (const srcOp of variant.sourceOperands) {
          const srcExample = getExampleValue(srcOp);
          
          for (const destOp of variant.destOperands) {
            const destExample = getExampleValue(destOp);
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
  
  // Write file using Bun's API
  Bun.write(validTestsPath, validTests);
  console.log(`Valid tests written to: ${validTestsPath}`);
}

// Run the generator
generateTestFiles(); 