// Script to run the test generator and save results to a file
const fs = require('fs');
const path = require('path');

// Import the generator code
const testGenerator = require('./generate_tests.js');

// Generate the tests and write to file
const outputPath = path.join(__dirname, 'valid_instructions.asm');

try {
  fs.writeFileSync(outputPath, testGenerator.generateTests());
  console.log(`Test file generated successfully at: ${outputPath}`);
} catch (error) {
  console.error('Failed to generate test file:', error);
} 