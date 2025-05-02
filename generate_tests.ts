#!/usr/bin/env bun
// Generate M68K instruction tests using Bun
// This script generates test cases for 68K assembly instructions

const fs = require('fs');
const path = require('path');

// Load instruction definitions from TypeScript file
// This import works with Bun which natively supports TypeScript
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
    default: return "";
  }
}

// Generate valid test cases
function generateValidTests() {
  let output = "";
  let previousInstrName = ""; // Track the previous instruction name
  
  // Generate instruction tests directly (no categories)
  for (const [instrName, instrData] of Object.entries(instructionsData.instructions)) {
    // Add a newline between different instructions
    if (previousInstrName && previousInstrName !== instrName) {
      output += "\n";
    }
    
    // Handle instructions with no operands
    if (instrData.sourceOperands.length === 0 && instrData.destOperands.length === 0) {
      output += `\t${instrName}\n`;
      previousInstrName = instrName;
      continue;
    }
    
    // Handle different sizes
    for (const size of instrData.sizes) {
      const sizeSuffix = size ? `.${size}` : '';
      
      // Handle single operand instructions (dest only)
      if (instrData.sourceOperands.length === 0 && instrData.destOperands.length > 0) {
        for (const destOp of instrData.destOperands) {
          const destExample = getExampleValue(destOp);
          output += `\t${instrName}${sizeSuffix}\t${destExample}\n`;
        }
      }
      // Handle source-only instructions (like branch)
      else if (instrData.sourceOperands.length > 0 && instrData.destOperands.length === 0) {
        for (const srcOp of instrData.sourceOperands) {
          const srcExample = getExampleValue(srcOp);
          output += `\t${instrName}${sizeSuffix}\t${srcExample}\n`;
        }
      }
      // Handle two-operand instructions
      else if (instrData.sourceOperands.length > 0 && instrData.destOperands.length > 0) {
        // Generate more comprehensive tests for certain instructions
        if (['ori', 'andi', 'subi', 'addi', 'eori', 'cmpi'].includes(instrName)) {
          // Special handling for immediate-to-memory instructions
          const immediate = size === 'b' ? '#$FF' : 
                           size === 'w' ? '#$FFFF' : '#$FFFFFFFF';
          
          for (const destOp of instrData.destOperands) {
            const destExample = getExampleValue(destOp);
            output += `\t${instrName}${sizeSuffix}\t${immediate},${destExample}\n`;
          }
          
          // Handle special cases for CCR and SR
          if (instrName === 'ori' || instrName === 'andi' || instrName === 'eori') {
            if (size === 'b') {
              output += `\t${instrName}.b\t#$FF,ccr\n`;
              output += `\t${instrName}\t#$FF,ccr\n`;
            } else if (size === 'w') {
              output += `\t${instrName}.w\t#$FFFF,sr\n`;
              output += `\t${instrName}\t#$FFFF,sr\n`;
            }
          }
        } 
        // For bit manipulation instructions
        else if (['btst', 'bchg', 'bclr', 'bset'].includes(instrName)) {
          // Register source
          for (const destOp of instrData.destOperands) {
            const destExample = getExampleValue(destOp);
            output += `\t${instrName}${sizeSuffix}\td5,${destExample}\n`;
          }
          
          // Immediate source
          for (const destOp of instrData.destOperands) {
            const destExample = getExampleValue(destOp);
            output += `\t${instrName}${sizeSuffix}\t#0,${destExample}\n`;
          }
          
          // Without size specifier
          for (const destOp of instrData.destOperands) {
            const destExample = getExampleValue(destOp);
            output += `\t${instrName}\td5,${destExample}\n`;
            output += `\t${instrName}\t#0,${destExample}\n`;
          }
        }
        // Default handling for other instructions
        else {
          // Only generate a few combinations to avoid huge test files
          const maxSrcExamples = 3;
          const maxDestExamples = 3;
          
          for (let i = 0; i < Math.min(instrData.sourceOperands.length, maxSrcExamples); i++) {
            const srcOp = instrData.sourceOperands[i];
            const srcExample = getExampleValue(srcOp);
            
            for (let j = 0; j < Math.min(instrData.destOperands.length, maxDestExamples); j++) {
              const destOp = instrData.destOperands[j];
              const destExample = getExampleValue(destOp);
              
              output += `\t${instrName}${sizeSuffix}\t${srcExample},${destExample}\n`;
            }
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
  const validTestsPath = path.join(process.cwd(), 'valid_instructions.asm');
  
  // Write file
  fs.writeFileSync(validTestsPath, validTests);
  console.log(`Valid tests written to: ${validTestsPath}`);
}

// Run the generator
generateTestFiles(); 