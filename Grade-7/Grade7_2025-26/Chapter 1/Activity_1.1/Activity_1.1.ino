// Define input pins for Motor
const int input1 = 7 ;
const int input2 = 8 ;

void setup()
{
  //Set pins 7 & 8 as Output.
  pinMode(input1,OUTPUT) ;
  pinMode(input2,OUTPUT) ;
}

void loop()
{
  //Making Clockwise motion , set input1 = High , input2 = Low
  digitalWrite(input1,HIGH) ;
  digitalWrite(input2,LOW) ;
  //Clockwise for 3 secs
  delay(3000) ;
  //To STOP, set input1= LOW, input2= LOW
  digitalWrite(input1,LOW) ;
  digitalWrite(input2,LOW) ;
  delay(1000) ;
  //Making Anti - Clockwise motion, set input1 = LOW , input2 = HIGH
  digitalWrite(input1,LOW) ;
  digitalWrite(input2,HIGH) ;
  //Anti - Clockwise for 3 secs
  delay(3000) ;
  //To STOP, set input1= LOW, input2= LOW
  digitalWrite(input1,LOW) ;
  digitalWrite(input2,LOW) ;
  delay(1000) ;
}

