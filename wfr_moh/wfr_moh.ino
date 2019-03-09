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

MPU6050 accc;
HMC5883L mag;
bool bmp;

Servo deploy_servo;
Servo cam;
float StartwallTemp;
volatile int accelReadings[10];
volatile int base_accelReadings[10];
volatile int accelReadings_curInd;
bool gotoVic=0;
bool enableTimesuff=1; //enables TimerOne CheckForVicimsAndDropKits() Interrupt also needed for LOPD
bool StartCheckingForVics; //if set to one will start using CheckForVicimsAndDropKits every 0.5 Seconds
volatile bool VizvictimIsDetected;
volatile int cpos=4; //contains current position of the cam Servo,2=right,0=left,1=Forward
volatile int vtype=4; //contains the Viz victims type,2=H,0=U,1=S
volatile unsigned long previousMillisCheckForImpTStuff = 0;        // will store last time LED was updated

#define LED_PIN 13 //change Me 
#define max_dist 400
#define speed_default 255//100
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

  Wire.begin(); 
  Wire2.begin(); 
  Serial.begin(9600);

  Wire.beginTransmission(0x77);
  int error = Wire.endTransmission();
  if  (error==0){
    Serial.println("Setting Up 10DOF sensors");
    accc.initialize(); //see README
    accc.setI2CBypassEnabled(true);
    bmp085Init(0);    // Set Baseline @ sea level	
    mag.initialize();
    mag.setDataRate(50);
    Serial.println("10DOF Ready");
	  Serial.println("Gathring Data for LOPD system");
    runLOPD();
  }else{
    bmp=false;
    Serial.println("10DOF Not detected at 0x77");
  }
  Serial.println("Ready ...");
  while(digitalRead(A11)==1){delay(50);}
  Serial.println("Starting...");
  StartCheckingForVics=enableTimesuff;
  delay(1000);
}

void loop(){
  Serial.println("LOOP");
  //turn(90,1);
  //delay(1000);
  drive_forward();
  //delay(3000);
  //turn(90,0);
}
void p(){
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
