#!/usr/bin/env bun
// Generate M68K instruction tests using Bun
// This script generates test cases for 68K assembly instructions

// Load instruction definitions from TypeScript file
import { data, OperandType } from './m68k_instructions.ts';
const instructionsData = data;

// Example values for each addressing mode
const examples: Record<OperandType, string[]> = {
  "dn": ["d2", "d5"],
  "an": ["a2", "a5"],
  "(an)": ["(a2)", "(a5)"],
  "(an)+": ["(a2)+", "(a5)+"],
  "-(an)": ["-(a2)", "-(a5)"],
  "d(an)": ["$7FFF(a2)", "$7FFF(a5)"],
  "d(an,ix)": ["$7F(a2,d5.w)", "$7F(a5,d2.w)"],
  "abs.w": ["($FFFFFFFF).w"],
  "abs.l": ["($FFFFFFFF).l"],
  "d(pc)": ["@(pc)"],
  "d(pc,ix)": ["@(pc,d5.w)"],
  "imm": ["#0", "#$FF", "#$FFFF", "#$FFFFFFFF"],
  "imm3": ["#1", "#7"],
  "imm4": ["#2"],
  "imm8": ["#0", "#$FF"],
  "label": ["@", "label"],
  "register_list": ["d5-a7", "d0-d7/a0-a7"],
  "ccr": ["ccr"],
  "sr": ["sr"]
};

// Helper function to get example values
function getExampleValues(operandType) {
  return examples[operandType] || [];
}

// Generate valid test cases
function generateValidTests() {
  let output = "";
  let previousInstrName = ""; // Track the previous instruction name
  
  // Process each group in the data
  for (const group of instructionsData) {
    // Get the variants for this group
    const variants = group.variants;
    
    // Process each instruction in this group
    for (const instrName of group.instructions) {
      // Add a newline between different instructions
      if (previousInstrName && previousInstrName !== instrName) {
        output += "\n";
      }
      
      // Process variants
      for (const variant of variants) {
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
              const destExamples = getExampleValues(destOp);
              
              for (const destExample of destExamples) {
                output += `\t${instrName}${sizeSuffix}\t${destExample}\n`;
              }
            }
          }
          // Source-only instructions (like branch)
          else if (variant.sourceOperands.length > 0 && variant.destOperands.length === 0) {
            for (const srcOp of variant.sourceOperands) {
              const srcExamples = getExampleValues(srcOp);
              
              for (const srcExample of srcExamples) {
                output += `\t${instrName}${sizeSuffix}\t${srcExample}\n`;
              }
            }
          }
          // Two-operand instructions - systematically generate all combinations
          else if (variant.sourceOperands.length > 0 && variant.destOperands.length > 0) {
            // Generate all combinations for all instructions
            for (const srcOp of variant.sourceOperands) {
              const srcExamples = getExampleValues(srcOp);
              
              for (const destOp of variant.destOperands) {
                const destExamples = getExampleValues(destOp);
                
                // Generate all combinations of source and dest examples
                for (const srcExample of srcExamples) {
                  for (const destExample of destExamples) {
                    output += `\t${instrName}${sizeSuffix}\t${srcExample},${destExample}\n`;
                  }
                }
              }
            }
          }
        }
      }
      
      previousInstrName = instrName;
    }
  }
  
  // Add label for instructions that need it
  output += `\nlabel:\n`;
  
  // Add end marker
  output += `\trts\n`;
  
  return output;
}

// Main function to generate test files
function generateTestFiles() {
  const validTests = generateValidTests();
  
  // Define output path
  const validTestsPath = './src/fasmg/m68k/tests/valid_instructions_new.asm';
  
  // Write file using Bun.write
  Bun.write(validTestsPath, validTests);
  console.log(`Valid tests written to: ${validTestsPath}`);
}

// Run the generator
generateTestFiles(); 