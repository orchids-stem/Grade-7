// Define input pins for Motor 1
const int input11 = 7;
const int input12 = 8;
// Define input pins for Motor 2
const int input21 = 9;
const int input22 = 10;
// Define enable (PWM) pins for Motor 1 and Motor 2
const int enable1 = 3; // PWM pin for Motor 1
const int enable2 = 5; // PWM pin for Motor 2

void setup()
{
  // Set all motor direction pins as output
  pinMode(input11, OUTPUT);
  pinMode(input12, OUTPUT);
  pinMode(input21, OUTPUT);
  pinMode(input22, OUTPUT);
  // Set enable pins (PWM pins) as output
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
}

void loop()
{
  // Set motor speeds using PWM
  // Motor 1 (left) 75% speed (approx 75% duty cycle)
  analogWrite(enable1, 191);
  // Motor 2 (right) full speed (100% duty cycle)
  analogWrite(enable2, 255);
  // Set Motor 1 (left) direction to forward (clockwise)
  // input11 = HIGH, input12 = LOW
  digitalWrite(input11, HIGH);
  digitalWrite(input12, LOW);
  // Set Motor 2 (right) direction to forward (clockwise)
  // input21 = HIGH, input22 = LOW
  digitalWrite(input21, HIGH);
  digitalWrite(input22, LOW);
  // Move forward left for 3 seconds
  delay(3000);
  
  // Stop both motors by setting all inputs LOW
  digitalWrite(input11, LOW);
  digitalWrite(input12, LOW);
  digitalWrite(input21, LOW);
  digitalWrite(input22, LOW);
}

