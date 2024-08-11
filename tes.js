function convertInterestRate(rate) {
  // Ensure the input is a number
  if (typeof rate !== 'number' || isNaN(rate)) {
    throw new Error('Input must be a valid number');
  }

  // Split the rate into integer and decimal parts
  let [integerPart, decimalPart] = rate.toString().split('.');
  
  // Handle case where there is no decimal part
  if (!decimalPart) {
    decimalPart = '0';
  }
  
  // Pad the integer part to 4 digits
  integerPart = integerPart.padStart(4, '0');
  
  // Pad the decimal part to 7 digits
  decimalPart = decimalPart.padEnd(7, '0');
  
  // Combine both parts to get the final string
  const result = integerPart + decimalPart.slice(0, 7);
  
  return result;
}

// Example usage:
console.log(convertInterestRate(2.5)); // Output: '00025000000'
console.log(convertInterestRate(123.456)); // Output: '01234560000'
console.log(convertInterestRate(0.1234567)); // Output: '00000123456'
