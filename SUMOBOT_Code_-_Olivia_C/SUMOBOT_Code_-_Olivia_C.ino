//Name: Olivia Chan
//Date: April 19, 2023

//Declaration Section
//Photoresistors
int ldr1; //Value from photoresistor 1 (front ldr)
int ldr2; //Value from photoresistor 2 (back ldr)

//Motor Driver
const int forwardLeft = 9; //Pin for left wheel forward rotation
const int backwardLeft = 6; //Pin for left wheel backward rotation
const int forwardRight = 10; //Pin for right wheel forward rotation
const int backwardRight = 11; //Pin for right wheel backward rotation

//Ultrasonic Sensors
unsigned int distance1; //Distance measured by ultrasonic sensor 1
unsigned int distance2; //Distance measured by ultrasonic sensor 2
unsigned int distance3; //Distance measured by ultrasonic sensor 3

//Other
boolean objectHere = false; // Checks to make sure other object is pushed out of ring

//Setup
void setup()
{
  //Ultrasonic Sensors
  pinMode(13, OUTPUT); //trig pin 1
  pinMode(12, INPUT); //echo pin 1
  pinMode(5, OUTPUT); //trig pin 2
  pinMode(4, INPUT); //echo pin 2
  pinMode(3, OUTPUT); //trig pin 3
  pinMode(2, INPUT); //echo pin 3

  //Motor Pins
  pinMode(forwardLeft, OUTPUT);
  pinMode(backwardLeft, OUTPUT);
  pinMode(forwardRight, OUTPUT);
  pinMode(backwardRight, OUTPUT);

  Serial.begin(9600);
}

//function loop
void loop()
{
  photoresistor();
  distance1 = readUltrasonicDistance(5, 4); //left distance sensor
  distance2 = readUltrasonicDistance(13, 12); //front distance sensor
  distance3 = readUltrasonicDistance(3, 2); //right distance sensor

  if (ldr1 > 30) 
  {
    moveBackward(); //When front boundary reached, move backward
    delay(3000);
  }
  else if (ldr2 > 30) //When back boundary reached, move forward
  {
    moveForward();
    delay(3000);
  }
  else {
    if (distance2 < distance1 && distance2 < distance3 && distance2 < 1000 && distance2 != 0)
    {
      objectHere = true;
      moveForward(); //Move straight ahead when something detected towards front
    }
    else if (distance1 < distance2 && distance1 < distance3 && distance1 < 1000 && distance1 != 0) //Left turn when something detected towards left
    {
      objectHere = false;
      rotateLeft();
      delay(1100);
    }
    else if (distance3 < distance2 && distance3 < distance1 && distance3 < 1000 && distance3 != 0) //Right turn when something detected towards right
    {
      objectHere = false;
      rotateRight();
      delay(1100);
    }
    else if (objectHere) {
      moveForward();
    }
    else
    {
      rotateSlow();//Bot rotates until object is found
    }
  }
}

//function restart
void restart()
{
  analogWrite(forwardLeft, 0);
  analogWrite(backwardLeft, 0);
  analogWrite(forwardRight, 0);
  analogWrite(backwardRight, 0);
}

//function moveForward
void moveForward()
{
  analogWrite(forwardLeft, 40);
  analogWrite(backwardLeft, 0);
  analogWrite(forwardRight, 40);
  analogWrite(backwardRight, 0);
}

//function rotateSlow
void rotateSlow()
{
  analogWrite(forwardLeft, 30);
  analogWrite(backwardLeft, 0);
  analogWrite(forwardRight, 0);
  analogWrite(backwardRight, 30);
}

//function moveBackward
void moveBackward()
{
  analogWrite(forwardLeft, 0);
  analogWrite(backwardLeft, 40);
  analogWrite(forwardRight, 0);
  analogWrite(backwardRight, 40);
}

//function rotateLeft
void rotateLeft()
{
  analogWrite(forwardLeft, 20);
  analogWrite(backwardLeft, 0);
  analogWrite(forwardRight, 0);
  analogWrite(backwardRight, 20);
}

//function rotateRight
void rotateRight()
{
  analogWrite(forwardLeft, 0);
  analogWrite(backwardLeft, 40);
  analogWrite(forwardRight, 40);
  analogWrite(backwardRight, 0);
}

//function photoresistor
void photoresistor()
{
  ldr1 = analogRead(A0); 
  ldr2 = analogRead(A2);
}

//function readUltrasonicDistance
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the
  // sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH, 30000);
}
