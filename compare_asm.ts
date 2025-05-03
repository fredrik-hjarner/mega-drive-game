#!/usr/bin/env bun

// Path to the original file
const originalFilePath = "src/fasmg/m68k/tests/valid_instructions.asm";
// Path to the new generated file
const generatedFilePath = "./valid_instructions.asm";

async function compareFiles() {
  // Read both files
  const originalContent = await Bun.file(originalFilePath).text();
  const generatedContent = await Bun.file(generatedFilePath).text();
  
  // Function to process a line: trim and remove comments
  function processLine(line) {
    // Remove comments starting with ; and trim
    return line.split(';')[0].trim();
  }
  
  // Split into lines and filter out comments and empty lines
  const originalLines = originalContent.split('\n')
    .map(processLine)
    .filter(line => line && !line.startsWith('*'));
  
  const generatedLines = generatedContent.split('\n')
    .map(processLine)
    .filter(line => line && !line.startsWith('*'));
  
  // Find lines in original that are missing from generated
  const missingLines = originalLines.filter(line => !generatedLines.includes(line));
  
  // Output results
  console.log(`Original file has ${originalLines.length} non-empty, non-comment lines`);
  console.log(`Generated file has ${generatedLines.length} non-empty, non-comment lines`);
  console.log(`\nFound ${missingLines.length} lines missing from the generated file:`);
  
  if (missingLines.length > 0) {
    console.log('\nMissing lines:');
    missingLines.forEach(line => {
      // Find the original line with potential comment for better context
      const originalLineIndex = originalContent.split('\n')
        .map(l => l.trim())
        .findIndex(l => l.startsWith(line));
      
      if (originalLineIndex >= 0) {
        const originalLine = originalContent.split('\n')[originalLineIndex].trim();
        console.log(originalLine); // Show with comment for context
      } else {
        console.log(line); // Fallback to just the instruction
      }
    });
  } else {
    console.log('All lines from the original file are present in the generated file!');
  }
}

// Run the comparison
compareFiles().catch(error => {
  console.error('Error comparing files:', error);
}); 