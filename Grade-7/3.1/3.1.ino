#include <Keypad.h> // Include the Keypad library

// Define the number of rows and columns in the keypad
const int ROWS = 4;
const int COLS = 4;

// Create a 2D array that matches the layout of the keypad buttons
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Define which pins on the Arduino connect to the rows and columns of the keypad
byte rowPins[ROWS] = {9, 8, 7, 6};  // Pins connected to the rows
byte colPins[COLS] = {5, 4, 3, 2};  // Pins connected to the columns

// Create the keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
}

void loop() {
  char key = keypad.getKey();  // Get the key press (if any)
  
  if (key) { // If a key is pressed
    Serial.println(key);  // Print the key to the serial monitor
  }
}
