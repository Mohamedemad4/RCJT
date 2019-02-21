#include <Wire.h>
#include <QMC5883L.h>
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>
#include <math.h>
#include <SoftwareWire.h>


//Left Sensor connected to A8,A9
//Right Sensor connected to Digital pins 20,21
SoftwareWire Wire2( A8, A9);// SDA,SCL
SoftwareWire Wire3( A15, A14);// SDA,SCL

QMC5883L compass;

Servo deploy_servo;
Servo cam;
volatile int cpos=4; //contains current position of the cam Servo

#define max_dist 400
#define speed_default 155
#define speed_max 255
NewPing left_us(A0,A0,max_dist);
NewPing center_us(A1,A1,max_dist);
NewPing right_us(A2,A2,max_dist);

AF_DCMotor fleft(2, MOTOR12_1KHZ); 	
AF_DCMotor fright(1, MOTOR12_1KHZ);

AF_DCMotor bleft(3, MOTOR34_1KHZ); 
AF_DCMotor bright(4, MOTOR34_1KHZ); 


void setup(){  
  //Push Button
  pinMode(A11,INPUT_PULLUP);
  pinMode(A12,1);

  //IR Color Sensor
  pinMode(A3, INPUT);

  deploy_servo.attach(10);
  deploy_servo.write(130);
  
  digitalWrite(A12,0);
  
  cam.attach(9);
  pinMode(22,INPUT_PULLUP);
  pinMode(23,INPUT_PULLUP);
  pinMode(24,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(18), checkForIns, CHANGE);

  Wire.begin(); 
  Wire2.begin(); 
  Wire3.begin();
  Serial.begin(9600);
	 
  compass.init();
	 compass.setSamplingRate(50);

  setSpeeds(speed_default,speed_default,
      speed_default,speed_default);
  while(digitalRead(A11)==1){delay(50);}
  Serial.println("Starting...");
  delay(1000);
}
  
void loop(){//each iteration should take up a tile TODO::
  unsigned long currentMillis = millis();
  unsigned long previousMillis = 0;        // will store last time LED was updated
 
  if(!isThisWall(center_us)){
   drive_forward(); 
  }
  if (GetDist(right_us)>10){
    turn_right();
  }
  if (currentMillis - previousMillis >= 1000) { //run this function every 1000ms
    previousMillis = currentMillis;
    CheckForVicimsAndDropKits(); //returns 1 after first success
  }
}
