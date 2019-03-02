#include <Wire.h>
#include <Servo.h>
#include <math.h>

#include "AFMotor.h"
#include "NewPing.h"
#include "SoftwareWire.h"
#include "HMC5883L.h"
#include "bmp085.h"
#include "I2Cdev.h"
#include "MPU6050.h"

//Left Sensor connected to A8,A9
//Right Sensor connected to Digital pins 20,21
SoftwareWire Wire2( A4, A5);// SDA,SCL

MPU6050 accc ;
HMC5883L mag;

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
  pinMode(A10,1);

  //IR Color Sensor
  pinMode(A3, INPUT);

  deploy_servo.attach(10);
  deploy_servo.write(130);
  
  digitalWrite(A10,0);
  
  cam.attach(9);
  pinMode(22,INPUT_PULLUP);
  pinMode(23,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(18), ServoINT, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), VizVictimINT, CHANGE);

  Wire.begin(); 
  Wire2.begin(); 
  
  accc.initialize(); //see README
  accc.setI2CBypassEnabled(true);
  bmp085Init(0);    // Set Baseline @ sea level	
  mag.initialize();
  Serial.begin(9600);
	 
  setSpeeds(speed_default,speed_default,
      speed_default,speed_default);
	

  while(digitalRead(A11)==1){delay(50);}
  Serial.println("Starting...");
  delay(1000);
}

void loop(){//each iteration should take up a tile TODO::
sensorDebug();
delay(1000);
}
