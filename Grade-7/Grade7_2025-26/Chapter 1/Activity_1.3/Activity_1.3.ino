// Define input pins for Motor 1
const int input11 = 7;
const int input12 = 8;
// Define input pins for Motor 1
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
  // To move Motor 1 clockwise, set input11 = HIGH and input12 = LOW
  digitalWrite(input11, HIGH);
  digitalWrite(input12, LOW);
  // To move Motor 2 clockwise, set input21 = HIGH and input22 = LOW
  digitalWrite(input21, HIGH);
  digitalWrite(input22, LOW);
  // Run both motors clockwise for 3 seconds
  delay(3000);

  // Stop both motors by setting all inputs LOW
  digitalWrite(input11, LOW);
  digitalWrite(input12, LOW);
  digitalWrite(input21, LOW);
  digitalWrite(input22, LOW);
  // Wait for 2 second while motors are stopped
  delay(2000);

  // To move Motor 1 move anti-clockwise, input11 = LOW, input12 = HIGH
  digitalWrite(input11, LOW);
  digitalWrite(input12, HIGH);
  // To move Motor 2 move anti-clockwise, input21 = LOW, input22 = HIGH
  digitalWrite(input21, LOW);
  digitalWrite(input22, HIGH);
  // Run both motors anti-clockwise for 3 seconds
  delay(3000);
  
  // Stop both motors by setting all inputs LOW
  digitalWrite(input11, LOW);
  digitalWrite(input12, LOW);
  digitalWrite(input21, LOW);
  digitalWrite(input22, LOW);
  // Wait for 2 second while motors are stopped
  delay(2000);
}

