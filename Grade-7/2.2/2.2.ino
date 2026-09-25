#include <LiquidCrystal_I2C.h>

// Initialize the LCD with the I2C address (0x27) and specify the number of columns and rows
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 is a common I2C address for 16x2 LCDs


// SDA is connected to A4
// SCL is connected to A5

void setup() {
  // Initialize the LCD
  lcd.init(); 
  
  // Turn on the backlight of the LCD
  lcd.backlight(); 
  
  // Set the cursor to column 0, row 0 and print a message to the LCD
  lcd.setCursor(0, 0); // Set cursor to the first position
  lcd.print("Hello World!"); // Display message on the first line 
}

void loop() {
  // The loop function is empty as there is nothing to repeat
}
