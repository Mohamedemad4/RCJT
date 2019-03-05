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
#include "TimerOne.h"

//Left Sensor connected to A8,A9
//Right Sensor connected to Digital pins 20,21
SoftwareWire Wire2( A4, A5);// SDA,SCL

MPU6050 accc ;
HMC5883L mag;

Servo deploy_servo;
Servo cam;
bool gotoVic;
volatile bool VizvictimIsDetected;
volatile int cpos=4; //contains current position of the cam Servo,2=right,0=left,1=Forward
volatile int vtype=4; //contains the Viz victims type,2=H,0=U,1=S
#define LED_PIN 13 //change Me 
#define max_dist 400
#define speed_default 100
#define speed_max 155
NewPing left_us(A0,A0,max_dist);
NewPing center_us(A1,A1,max_dist);
NewPing right_us(A2,A2,max_dist);

AF_DCMotor fleft(2, MOTOR12_1KHZ); 	
AF_DCMotor fright(1, MOTOR12_1KHZ);

AF_DCMotor bleft(3, MOTOR34_1KHZ); 
AF_DCMotor bright(4, MOTOR34_1KHZ); 

void(* resetFunc) (void) = 0; //declare reset function @ address 0,crash the machine
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
  // for the 2 Digital comm pins
  pinMode(22,INPUT_PULLUP); 
  pinMode(23,INPUT_PULLUP);
  // for the Interrupt pins
  pinMode(18,INPUT_PULLUP);
  pinMode(19,INPUT_PULLUP);
  pinMode(15,INPUT_PULLUP);
  pinMode(14,INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(18), ServoINT, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), VizVictimINT, CHANGE);
  attachInterrupt(digitalPinToInterrupt(15), Pause, CHANGE);
  attachInterrupt(digitalPinToInterrupt(14), resetFunc, CHANGE);
  
  Timer1.initialize(500000); // in uS
  Timer1.attachInterrupt(CheckForVicimsAndDropKits); // run 2 times every  seconds

  Wire.begin(); 
  Wire2.begin(); 
  
  accc.initialize(); //see README
  accc.setI2CBypassEnabled(true);
  bmp085Init(0);    // Set Baseline @ sea level	
  mag.initialize();
  //mag.setDataRat();setDataRate
  Serial.begin(9600);
	 
  setSpeeds(speed_default,speed_default,
      speed_default,speed_default);
	
  Serial.println("Ready ...");
  while(digitalRead(A11)==1){delay(50);}
  Serial.println("Starting...");
  delay(1000);
}
void lop(){
  sensorDebug();
  delay(500);
}
void loop(){
  turn(90,1);
  delay(1000);
  drive_forward();
  delay(3000);
  turn(90,0);
  while (true){}
}
void p(){//each iteration should take up a tile TODO::
  //right wall follower 
      while(GetDist(center_us)>15){
          drive_forward();
        }
 
          //!!!dont forget to calibrate the us_  in the maze!!!
          
         if(GetDist(center_us)<=15  ){  //found a wall infront of you!
          
          if(GetDist(right_us)>=7){//turn right if there isn't a wall on the right
            turn(90,1);

          }

            else if(GetDist(right_us)<7){// turn left if there is a wall on the right
              turn(90,0);
              }
         }

         if(GetDist(center_us)<=7 && GetDist(right_us)<=7 && GetDist(left_us)<=7){  //emergyncy if the robot was traped in a 3 walled tile 
            turn(180,0);
          }

          if(GetDist(right_us)>=7){//always right
              turn(90,1);
            }


            //!!!dont forget to calibrate the delay  in the maze!!!
          while(GetDist(right_us)<=7){//aligment right
              turn_left();
              delay(50);
            }


            while(GetDist(left_us)<=7){//aligment left
              turn_right();
              delay(50);
            }
            
            if(digitalRead(A3)==1){//if a trap is found 
              motor_stop();
              delay(200);
              drive_backward();
              delay(300);

              if(GetDist(left_us)>GetDist(right_us)){//turn left if left is greater than right
                turn(90,0);
                }

              else if(GetDist(left_us)<GetDist(right_us)){//turn right if right is greater than left
                turn(90,1);
                }
              }
}
