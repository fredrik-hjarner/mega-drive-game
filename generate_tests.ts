#!/usr/bin/env bun
// Generate M68K instruction tests using Bun
// This script generates test cases for 68K assembly instructions

// Load instruction definitions from TypeScript file
import { data } from './m68k_instructions.ts';
const instructionsData = data;

// Function to generate example values for each operand type, with size awareness
function getExampleValue(operandType, size = '') {
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

// A standard order for addressing modes to ensure consistency
const standardAddressingModeOrder = [
  "dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm", 
  "imm3", "imm4", "imm8", "label", "register_list", "ccr", "sr"
];

// Sort operands by the standard order
function sortByStandardOrder(operands) {
  return operands.sort((a, b) => {
    return standardAddressingModeOrder.indexOf(a) - standardAddressingModeOrder.indexOf(b);
  });
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
    
    // Process variants in a specific order:
    // 1. CCR variants first
    // 2. SR variants second
    // 3. Standard variants last
    
    // Find special variants
    const ccrVariants = instrVariants.filter(v => v.destOperands.includes("ccr"));
    const srVariants = instrVariants.filter(v => v.destOperands.includes("sr"));
    
    // Get remaining "standard" variants
    const standardVariants = instrVariants.filter(v => 
      !v.destOperands.includes("ccr") && !v.destOperands.includes("sr"));
    
    // Process CCR variants first
    for (const variant of ccrVariants) {
      for (const size of variant.sizes) {
        const sizeSuffix = size ? `.${size}` : '';
        const immediate = size === 'b' ? '#$FF' : '#$FFFF';
        
        // With size
        output += `\t${instrName}${sizeSuffix}\t${immediate},ccr\n`;
        // Without size
        output += `\t${instrName}\t${immediate},ccr\n`;
      }
    }
    
    // Process SR variants second
    for (const variant of srVariants) {
      for (const size of variant.sizes) {
        const sizeSuffix = size ? `.${size}` : '';
        const immediate = '#$FFFF';
        
        // With size
        output += `\t${instrName}${sizeSuffix}\t${immediate},sr\n`;
        // Without size
        output += `\t${instrName}\t${immediate},sr\n`;
      }
    }
    
    // Process standard variants
    for (const variant of standardVariants) {
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
          // Sort destination operands by standard order
          const sortedDestOps = sortByStandardOrder([...variant.destOperands]);
          
          for (const destOp of sortedDestOps) {
            const destExample = getExampleValue(destOp, size);
            output += `\t${instrName}${sizeSuffix}\t${destExample}\n`;
          }
        }
        // Source-only instructions (like branch)
        else if (variant.sourceOperands.length > 0 && variant.destOperands.length === 0) {
          // Sort source operands by standard order
          const sortedSrcOps = sortByStandardOrder([...variant.sourceOperands]);
          
          for (const srcOp of sortedSrcOps) {
            const srcExample = getExampleValue(srcOp, size);
            output += `\t${instrName}${sizeSuffix}\t${srcExample}\n`;
          }
        }
        // Two-operand instructions - systematically generate all combinations
        else if (variant.sourceOperands.length > 0 && variant.destOperands.length > 0) {
          // Sort operands by standard order
          const sortedSrcOps = sortByStandardOrder([...variant.sourceOperands]);
          const sortedDestOps = sortByStandardOrder([...variant.destOperands]);
          
          // Generate all combinations
          for (const srcOp of sortedSrcOps) {
            const srcExample = getExampleValue(srcOp, size);
            
            for (const destOp of sortedDestOps) {
              const destExample = getExampleValue(destOp, size);
              output += `\t${instrName}${sizeSuffix}\t${srcExample},${destExample}\n`;
            }
          }
        }
      }
      
      // For bit manipulation and other instructions, also generate without size specifier
      if (['btst', 'bchg', 'bclr', 'bset'].includes(instrName)) {
        const sortedSrcOps = sortByStandardOrder([...variant.sourceOperands]);
        const sortedDestOps = sortByStandardOrder([...variant.destOperands]);
        
        for (const srcOp of sortedSrcOps) {
          const srcExample = getExampleValue(srcOp);
          
          for (const destOp of sortedDestOps) {
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
  
  // Write file using Node.js fs module which Bun supports
  const fs = require('fs');
  fs.writeFileSync(validTestsPath, validTests);
  console.log(`Valid tests written to: ${validTestsPath}`);
}

// Run the generator
generateTestFiles(); 