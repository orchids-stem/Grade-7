#include <PS2X_lib.h> // PS2X Library
// --- PS2 controller pins ---
#define PS2_CLK 11
#define PS2_CMD 4
#define PS2_SEL 6
#define PS2_DAT 2

// --- Motor control pins ---
const int motorIn1Pin = 7; // Right motor IN1
const int motorIn2Pin = 8; // Right motor IN2
const int motorIn3Pin = 10; // Left motor IN3
const int motorIn4Pin = 9; // Left motor IN4
const int motor1_LEN = 3; // Left Enable (PWM)
const int motor1_REN = 5; // Right Enable (PWM)
PS2X ps2x; // PS2 controller object
int error = 0;

void setup() 
{
  // Setup motor control pins
  pinMode(motorIn1Pin, OUTPUT);
  pinMode(motorIn2Pin, OUTPUT);
  pinMode(motorIn3Pin, OUTPUT);
  pinMode(motorIn4Pin, OUTPUT);
  pinMode(motor1_LEN, OUTPUT);
  pinMode(motor1_REN, OUTPUT);
  // Enable motor drivers
  digitalWrite(motor1_LEN, HIGH);
  digitalWrite(motor1_REN, HIGH);
  // Stop motors at start
  Brake();
  Serial.begin(9600);
  delay(300);
  // Setup PS2 controller
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true,
  true);
  if (error == 0)
  {
  Serial.println("Controller configured successfully");
  } 
  else 
  {
  Serial.print("Controller configuration failed, error code: ");
  Serial.println(error);
  }
}

void loop() 
{
  ps2x.read_gamepad(false, 0); // Read controller data
  if (error != 0) return;
  int leftX = ps2x.Analog(PSS_LX); // Steering
  int rightY = ps2x.Analog(PSS_RY); // Throttle
  Serial.print("Left X: ");
  Serial.print(leftX);
  Serial.print(" | Right Y: ");
  Serial.println(rightY);
  if (isValidSignal(leftX, rightY))
  {
  controlCar(leftX, rightY);
  }
  else 
  {
  Brake();
  }
  delay(50); // Loop delay
}

// --- Validate analog input ---
bool isValidSignal(int leftX, int rightY) 
{
  return (leftX >= 0 && leftX <= 255 && rightY >= 0 && rightY <= 255);
}
// --- Main control function ---

void controlCar(int leftX, int rightY) 
{
  int motorSpeed = map(rightY, 0, 255, 255, -255); // Up = forward
  int turnSpeed = map(leftX, 0, 255, -255, 255); // Left = left turn
  Serial.print("Motor Speed: ");
  Serial.print(motorSpeed);
  Serial.print(" | Turn Speed: ");
  Serial.println(turnSpeed);
  // Reduced deadzone for more responsiveness
  if (abs(motorSpeed) <= 5 && abs(turnSpeed) <= 5) 
  {
  Brake();
  return;
  }

  // Forward
  if (motorSpeed > 5) 
  {
    if (turnSpeed > 5) 
    {
      forwardRight(motorSpeed);
      Serial.println(" Forward Right");
      
    }
    else if (turnSpeed < -5) 
    {
      forwardLeft(motorSpeed);
      Serial.println(" Forward Left");
      }
      else
      {
        moveForward(motorSpeed);
        Serial.println(" Forward");
      }
  }

  // Backward
  else if (motorSpeed < -5) 
  {
    if (turnSpeed > 5) 
    {
      backwardRight(abs(motorSpeed));
      Serial.println("Backward Right");
    }
    else if (turnSpeed < -5) 
    {
      backwardLeft(abs(motorSpeed));
      Serial.println("Backward Left");
    }
    else
    {
      moveBackward(abs(motorSpeed));
      Serial.println("Backward");
    }
  }
  // In-place turn only
  else
  {
    if (turnSpeed > 5) 
    {
      turnRight(255);
      Serial.println("Turn Right");
    }
    else if (turnSpeed < -5) 
    {
      turnLeft(255);
    Serial.println("Turn Left");
    }
  }
}

// --- Movement Functions ---
void moveForward(int speed) 
{
  digitalWrite(motorIn1Pin, LOW);
  analogWrite(motorIn2Pin, constrain(speed, 0, 255));
  analogWrite(motorIn3Pin, constrain(speed, 0, 255));
  digitalWrite(motorIn4Pin, LOW);
}

void moveBackward(int speed) 
{
  analogWrite(motorIn1Pin, constrain(speed, 0, 255));
  digitalWrite(motorIn2Pin, LOW);
  digitalWrite(motorIn3Pin, LOW);
  analogWrite(motorIn4Pin, constrain(speed, 0, 255));
}

void turnRight(int speed) 
{
  analogWrite(motorIn1Pin, constrain(speed, 0, 255));
  digitalWrite(motorIn2Pin, LOW);
  analogWrite(motorIn3Pin, constrain(speed, 0, 255));
  digitalWrite(motorIn4Pin, LOW);
}

void turnLeft(int speed) 
{
  digitalWrite(motorIn1Pin, LOW);
  analogWrite(motorIn2Pin, constrain(speed, 0, 255));
  digitalWrite(motorIn3Pin, LOW);
  analogWrite(motorIn4Pin, constrain(speed, 0, 255));
}

void forwardRight(int speed) 
{
  analogWrite(motorIn2Pin, constrain(speed, 0, 255)); // Full speed right
  digitalWrite(motorIn1Pin, LOW);
  digitalWrite(motorIn4Pin, LOW);
  analogWrite(motorIn3Pin, constrain(speed, 0, 255)); // Full speed left
}

void forwardLeft(int speed) 
{
  analogWrite(motorIn2Pin, constrain(speed, 0, 255)); // Full speed right
  digitalWrite(motorIn1Pin, LOW);
  digitalWrite(motorIn4Pin, LOW);
  analogWrite(motorIn3Pin, constrain(speed, 0, 255)); // Full speed left
}

void backwardRight(int speed) 
{
  analogWrite(motorIn1Pin, constrain(speed, 0, 255)); // Full speed right
  digitalWrite(motorIn2Pin, LOW);
  digitalWrite(motorIn3Pin, LOW);
  analogWrite(motorIn4Pin, constrain(speed, 0, 255)); // Full speed left
}

void backwardLeft(int speed) 
{
  analogWrite(motorIn1Pin, constrain(speed, 0, 255)); // Full speed right
  digitalWrite(motorIn2Pin, LOW);
  digitalWrite(motorIn3Pin, LOW);
  analogWrite(motorIn4Pin, constrain(speed, 0, 255)); // Full speed left
}

void Brake() 
{
  digitalWrite(motorIn1Pin, LOW);
  digitalWrite(motorIn2Pin, LOW);
  digitalWrite(motorIn3Pin, LOW);
  digitalWrite(motorIn4Pin, LOW);
}
