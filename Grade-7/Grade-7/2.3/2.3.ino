#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16x2 display

// SDA is connected to A4
// SCL is connected to A5

// Custom characters
byte Hammer[8] = {
  B00100,
  B11111,
  B11111,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100
};

byte Dumbbell[8] = {
  B00100,
  B11111,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100
};

byte Alien[8] = {
  B11111,
  B10101,
  B11111,
  B11111,
  B01110,
  B01010,
  B11011,
  B00000
};

byte Trident[8] = {
  B10101,
  B10101,
  B10101,
  B01110,
  B00100,
  B00100,
  B00100,
  B00100
};

byte Speaker[8] = {
  B00001,
  B00011,
  B01111,
  B01111,
  B01111,
  B00011,
  B00001,
  B00000
};

byte Sound[8] = {
  B00001,
  B00011,
  B00101,
  B01001,
  B01001,
  B01011,
  B11011,
  B11000
};

byte Skull[8] = {
  B00000,
  B01110,
  B10101,
  B11011,
  B01110,
  B01110,
  B00000,
  B00000
};

byte Face[8] = {
  B01110,
  B10001,
  B11011,
  B10001,
  B10101,
  B10001,
  B01110,
  B00000
};

void setup() {
  lcd.init(); // Initialize LCD
  lcd.backlight(); // Turn on the backlight

  // Create custom characters
  lcd.createChar(0, Hammer);
  lcd.createChar(1, Dumbbell);
  lcd.createChar(2, Alien);
  lcd.createChar(3, Trident);
  lcd.createChar(4, Speaker);
  lcd.createChar(5, Sound);
  lcd.createChar(6, Skull);
  lcd.createChar(7, Face);

  lcd.clear(); // Clear the display
  lcd.print("Custom Characters"); // Display a message
}

void loop() {
  lcd.setCursor(0, 1); // Set cursor to second line
  lcd.write(0); // Display Hammer
  lcd.setCursor(2, 1);
  lcd.write(1); // Display Dumbbell
  lcd.setCursor(4, 1);
  lcd.write(2); // Display Alien
  lcd.setCursor(6, 1);
  lcd.write(3); // Display Trident
  lcd.setCursor(8, 1);
  lcd.write(4); // Display Speaker
  lcd.setCursor(10, 1);
  lcd.write(5); // Display Sound
  lcd.setCursor(12, 1);
  lcd.write(6); // Display Skull
  lcd.setCursor(14, 1);
  lcd.write(7); // Display Face

  delay(1000); // Wait for a second before repeating
}
