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

volatile char cpos;

#define max_dist 400
#define speed_default 155
#define speed_max 255
NewPing sonar0(A0,A0,max_dist);
NewPing sonar1(A1,A1,max_dist);
NewPing sonar2(A2,A2,max_dist);

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
  
  cam.attach(13);
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
  
void loop(){
  
  while(GetDist(sonar1)>15){
    drive_forward();
    }
    
 while(GetDist(sonar1)<=20){
  if(GetDist(sonar0)>GetDist(sonar2)){
    turn_left();
    delay(500);
    }

    else if (GetDist(sonar2)>GetDist(sonar0)){
      turn_right();
      delay(500);
      }
  }

  while(GetDist(sonar1)<=20 && (GetDist(sonar1)<=15 || GetDist(sonar2)<=15)){
    drive_backward();
    delay(500);
    
    if(GetDist(sonar0)>GetDist(sonar2)){
    turn_left();
    delay(500);
    }

    else if (GetDist(sonar2)>GetDist(sonar0)){
      turn_right();
      delay(500);
      }
  }
}
void vicDetect(){
    if (digitalRead(24)==0){
        Serial.println("victim Found!");
        Serial.println(cpos);
        digitalWrite(24,1); //drive the pin HIGH to confirm;
    }
}
