#include <Servo.h>

// Create a Servo object
Servo myServo;

void setup() {
  // Attach the Servo to pin 9
  myServo.attach(9);
}

void loop() {
  // Sweep the Servo from 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);  // Set the Servo to the current position
    delay(15);  // Wait for 15 milliseconds to let the Servo reach the position
  }
  
  // Sweep the Servo from 180 to 0 degrees
  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);  // Set the Servo to the current position
    delay(15);  // Wait for 15 milliseconds to let the Servo reach the position
  }
}
