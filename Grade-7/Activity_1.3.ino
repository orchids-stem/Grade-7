// Define input pins for Motor 1
const int input11 = 7;
const int input12 = 8;

// Define input pins for Motor 2
const int input21 = 9;
const int input22 = 10;

void setup()
{
  // Set pins 7, 8, 9, and 10 as output pins
  pinMode(input11, OUTPUT);
  pinMode(input12, OUTPUT);
  pinMode(input21, OUTPUT);
  pinMode(input22, OUTPUT);
}

void loop()
{
  // —-------------- Turn LEFT —--------------

  // To turn left, we make the left motor (Motor 1) rotate backward (anti- clockwise)
  // and the right motor (Motor 2) rotates forward (clockwise).
  // Motor 1 (left) anti-clockwise => input11 = LOW, input12 = HIGH

  digitalWrite(input11, LOW);
  digitalWrite(input12, HIGH);
  // Motor 2 (right) clockwise => input21 = HIGH, input22 = LOW
  digitalWrite(input21, HIGH);
  digitalWrite(input22, LOW);
  // Run both motors for 3 seconds

  delay(3000);
  // Stop both motors by setting all inputs LOW

  digitalWrite(input11, LOW);
  digitalWrite(input12, LOW);
  digitalWrite(input21, LOW);
  digitalWrite(input22, LOW);
  // Wait for 2 seconds while motors are stopped
  delay(2000);

  // —-------------- Turn RIGHT —--------------

  // To turn right, we make the left motor (Motor 1) rotate forward (clockwise)
  // and the right motor (Motor 2) rotates backward (anti-clockwise).
  // Motor 1 (left) clockwise => input11 = HIGH, input12 = LOW

  digitalWrite(input11, HIGH);
  digitalWrite(input12, LOW);
  // Motor 2 (right) anti-clockwise => input21 = LOW, input22 = HIGH
  digitalWrite(input21, LOW);
  digitalWrite(input22, HIGH);
  // Run both motors for 3 seconds

  delay(3000);
  // Stop both motors by setting all inputs LOW

  digitalWrite(input11, LOW);
  digitalWrite(input12, LOW);
  digitalWrite(input21, LOW);
  digitalWrite(input22, LOW);
  delay(2000);
}
