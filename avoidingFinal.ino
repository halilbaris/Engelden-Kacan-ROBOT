#include <Servo.h> //include Servo library 

const int RForward = 0; 
const int RBackward = 180; 
const int LForward = 113; 
const int LBackward = 0; 
const int RNeutral = 73; 
const int LNeutral = 92; //constants for motor speed 
const int trigpin = 13; 
const int echopin = 12; 
const int dangerThresh = 10; //threshold for obstacles (in cm) 
int leftDistance, rightDistance; //distances on either side 
Servo panMotor; 
Servo leftMotor; 
Servo rightMotor; //declare motors 
long duration; //time it takes to recieve PING))) signal 

void setup() 
{ 
rightMotor.attach(11); 
leftMotor.attach(9); 
panMotor.attach(10); //attach motors to proper pins 
panMotor.write(90); //set PING))) pan to center 
} 

void loop() 
{ 
int distanceFwd = ping(); 
if (distanceFwd>dangerThresh) //if path is clear 
{ 
leftMotor.write(LForward); 
rightMotor.write(RForward); //move forward 
} 
else //if path is blocked 
{ 
leftMotor.write(LNeutral); 
rightMotor.write(RNeutral); 
panMotor.write(0); 
delay(500); 
rightDistance = ping(); //scan to the right 
delay(500); 
panMotor.write(180); 
delay(700); 
leftDistance = ping(); //scan to the left 
delay(500); 
panMotor.write(90); //return to center 
delay(100); 
compareDistance();

} 

} 

void compareDistance() 
{ 
if (leftDistance>rightDistance) //if left is less obstructed 
{ 
leftMotor.write(LBackward); 
rightMotor.write(RForward); //turn left 
delay(500); 
} 
else if (rightDistance>leftDistance) //if right is less obstructed 
{ 
leftMotor.write(LForward); 
rightMotor.write(RBackward); //turn right 
delay(500); 
} 
else //if they are equally obstructed 
{ 
leftMotor.write(LForward); 
rightMotor.write(RBackward); //turn 180 degrees 
delay(1000); 
} 
} 

long ping() 
{ 
// Send out PING))) signal pulse 
pinMode(trigpin, OUTPUT); 
pinMode(echopin,INPUT); 
digitalWrite(trigpin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigpin, HIGH); 
delayMicroseconds(10); 
digitalWrite(trigpin, LOW); 

//Get duration it takes to receive echo 

duration = pulseIn(echopin, HIGH); 

//Convert duration into distance 
return duration / 29 / 2; 
} 

