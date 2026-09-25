#include <PS2X_lib.h>


// PS2 controller pins
#define PS2_DAT 2
#define PS2_CMD 4
#define PS2_SEL 6
#define PS2_CLK 11


// Motor control pins
const int motorIn1Pin = 7;  // Right motor direction pin 1
const int motorIn2Pin = 8;  // Right motor direction pin 2
const int motorIn3Pin = 10;  // Left motor direction pin 1
const int motorIn4Pin = 9; // Left motor direction pin 2


const int motor1_LEN = 3;   // Right motor enable (PWM)
const int motor1_REN = 5;   // Left motor enable (PWM)


PS2X ps2x; // Create PS2 Controller Class


void setup() {
  pinMode(motorIn1Pin, OUTPUT);
  pinMode(motorIn2Pin, OUTPUT);
  pinMode(motorIn3Pin, OUTPUT);
  pinMode(motorIn4Pin, OUTPUT);
  pinMode(motor1_LEN, OUTPUT);
  pinMode(motor1_REN, OUTPUT);


  brakeMotors();


  Serial.begin(9600);
  delay(300); // Allow wireless PS2 to start up


  int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  if (error == 0) {
    Serial.println("PS2 Controller connected successfully.");
  } else {
    Serial.print("Controller config failed. Error code: ");
    Serial.println(error);
    while (1); // Stop program if controller not found
  }
}


void loop() {
  ps2x.read_gamepad(false, 0);


  int leftX = ps2x.Analog(PSS_LX);
  int rightY = ps2x.Analog(PSS_RY);
  bool fullSpeed = ps2x.Button(PSB_L2) || ps2x.Button(PSB_R2);


  // Map joystick values to -255 to 255
  int motorSpeed = map(rightY, 0, 255, 255, -255); // forward = positive
  int turnSpeed = map(leftX, 0, 255, -255, 255);   // left = negative


  // Optional full speed mode
  float speedMultiplier = fullSpeed ? 1.5 : 1.0;
  motorSpeed = constrain(motorSpeed * speedMultiplier, -255, 255);
  turnSpeed = constrain(turnSpeed * speedMultiplier, -255, 255);


  Serial.print("motorSpeed: ");
  Serial.print(motorSpeed);
  Serial.print(" | turnSpeed: ");
  Serial.println(turnSpeed);


  controlCar(motorSpeed, turnSpeed);
  delay(50);
}


void controlCar(int motorSpeed, int turnSpeed) {
  const int deadzone = 15;


  if (abs(motorSpeed) <= deadzone && abs(turnSpeed) <= deadzone) {
    brakeMotors();
    return;
  }


  // Forward movement
  if (motorSpeed > deadzone) {
    if (turnSpeed > deadzone) {
      forwardRight(motorSpeed, turnSpeed);
    } else if (turnSpeed < -deadzone) {
      forwardLeft(motorSpeed, turnSpeed);
    } else {
      moveForward(motorSpeed);
    }


  // Backward movement
  } else if (motorSpeed < -deadzone) {
    if (turnSpeed > deadzone) {
      backwardRight(-motorSpeed, turnSpeed);
    } else if (turnSpeed < -deadzone) {
      backwardLeft(-motorSpeed, turnSpeed);
    } else {
      moveBackward(-motorSpeed);
    }


  // In-place turning
  } else {
    if (turnSpeed > deadzone) {
      turnRight(turnSpeed);
    } else if (turnSpeed < -deadzone) {
      turnLeft(-turnSpeed);
    } else {
      brakeMotors();
    }
  }
}


// --- Motor control functions ---


void moveForward(int speed) {
  // Right motor forward
  digitalWrite(motorIn1Pin, HIGH);
  digitalWrite(motorIn2Pin, LOW);
  analogWrite(motor1_LEN, constrain(speed, 0, 255));


  // Left motor forward
  digitalWrite(motorIn3Pin, HIGH);
  digitalWrite(motorIn4Pin, LOW);
  analogWrite(motor1_REN, constrain(speed, 0, 255));
}


void moveBackward(int speed) {
  // Right motor backward
  digitalWrite(motorIn1Pin, LOW);
  digitalWrite(motorIn2Pin, HIGH);
  analogWrite(motor1_LEN, constrain(speed, 0, 255));


  // Left motor backward
  digitalWrite(motorIn3Pin, LOW);
  digitalWrite(motorIn4Pin, HIGH);
  analogWrite(motor1_REN, constrain(speed, 0, 255));
}


void turnLeft(int speed) {
  // Right motor forward
  digitalWrite(motorIn1Pin, HIGH);
  digitalWrite(motorIn2Pin, LOW);
  analogWrite(motor1_LEN, constrain(speed, 0, 255));


  // Left motor backward
  digitalWrite(motorIn3Pin, LOW);
  digitalWrite(motorIn4Pin, HIGH);
  analogWrite(motor1_REN, constrain(speed, 0, 255));
}


void turnRight(int speed) {
  // Right motor backward
  digitalWrite(motorIn1Pin, LOW);
  digitalWrite(motorIn2Pin, HIGH);
  analogWrite(motor1_LEN, constrain(speed, 0, 255));


  // Left motor forward
  digitalWrite(motorIn3Pin, HIGH);
  digitalWrite(motorIn4Pin, LOW);
  analogWrite(motor1_REN, constrain(speed, 0, 255));
}
void forwardLeft(int speed, int turnSpeed) {
  int leftMotorSpeed = constrain(speed - abs(turnSpeed) / 2, 0, 255);
  int rightMotorSpeed = constrain(speed, 0, 255);


  // Right motor forward
  digitalWrite(motorIn1Pin, HIGH);
  digitalWrite(motorIn2Pin, LOW);
  analogWrite(motor1_LEN, rightMotorSpeed);


  // Left motor forward (reduced)
  digitalWrite(motorIn3Pin, HIGH);
  digitalWrite(motorIn4Pin, LOW);
  analogWrite(motor1_REN, leftMotorSpeed);
}


void forwardRight(int speed, int turnSpeed) {
  int leftMotorSpeed = constrain(speed, 0, 255);
  int rightMotorSpeed = constrain(speed - abs(turnSpeed) / 2, 0, 255);


  // Right motor forward (reduced)
  digitalWrite(motorIn1Pin, HIGH);
  digitalWrite(motorIn2Pin, LOW);
  analogWrite(motor1_LEN, rightMotorSpeed);


  // Left motor forward
  digitalWrite(motorIn3Pin, HIGH);
  digitalWrite(motorIn4Pin, LOW);
  analogWrite(motor1_REN, leftMotorSpeed);
}


void backwardLeft(int speed, int turnSpeed) {
  int leftMotorSpeed = constrain(speed - abs(turnSpeed) / 2, 0, 255);
  int rightMotorSpeed = constrain(speed, 0, 255);


  // Right motor backward
  digitalWrite(motorIn1Pin, LOW);
  digitalWrite(motorIn2Pin, HIGH);
  analogWrite(motor1_LEN, rightMotorSpeed);


  // Left motor backward (reduced)
  digitalWrite(motorIn3Pin, LOW);
  digitalWrite(motorIn4Pin, HIGH);
  analogWrite(motor1_REN, leftMotorSpeed);
}


void backwardRight(int speed, int turnSpeed) {
  int leftMotorSpeed = constrain(speed, 0, 255);
  int rightMotorSpeed = constrain(speed - abs(turnSpeed) / 2, 0, 255);


  // Right motor backward (reduced)
  digitalWrite(motorIn1Pin, LOW);
  digitalWrite(motorIn2Pin, HIGH);
  analogWrite(motor1_LEN, rightMotorSpeed);


  // Left motor backward
  digitalWrite(motorIn3Pin, LOW);
  digitalWrite(motorIn4Pin, HIGH);
  analogWrite(motor1_REN, leftMotorSpeed);
}




void brakeMotors() {
  digitalWrite(motorIn1Pin, LOW);
  digitalWrite(motorIn2Pin, LOW);
  digitalWrite(motorIn3Pin, LOW);
  digitalWrite(motorIn4Pin, LOW);
  analogWrite(motor1_LEN, 0);
  analogWrite(motor1_REN, 0);
}



