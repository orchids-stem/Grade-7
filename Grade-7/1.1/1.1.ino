// Define the LED pins
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int numLeds = 10;

void setup() {
  // Initialize all LED pins as outputs
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {
  // Turn on LEDs sequentially
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH); // Turn on the LED
    Serial.print("LED ");
    Serial.print(ledPins[i]);
    Serial.println(" ON");
    delay(500); // Wait for 500 milliseconds
  }

  // Turn off LEDs sequentially
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW); // Turn off the LED
    Serial.print("LED ");
    Serial.print(ledPins[i]);
    Serial.println(" OFF");
    delay(500); // Wait for 500 milliseconds
  }
}
