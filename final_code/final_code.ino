#include <Wire.h>
#include <Servo.h>
#include <math.h>

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

float StartwallTemp;
volatile int accelReadings[10];
volatile int base_accelReadings[10];
volatile int accelReadings_curInd;
bool gotoVic=0;
bool enableTimesuff=1; //enables TimerOne CheckForVicimsAndDropKits() Interrupt also needed for LOPD ,Use me instead of setting StartCheckingForVics 
bool StartCheckingForVics; //if set to one will start using CheckForVicimsAndDropKits every 0.5 Seconds
volatile bool VizvictimIsDetected;
volatile int cpos=4; //contains current position of the cam Servo,2=right,0=left,1=Forward
volatile int vtype=4; //contains the Viz victims type,2=H,0=U,1=S
volatile unsigned long previousMillisCheckForImpTStuff = 0;

volatile int orientation=0; // 0 N , 1 E , 2 S , 3 W,assume f from starting pos = N
volatile int posX=10;// assume 0,0 on start position
volatile int posY=10;

/*
0=Wall,1=unvistedTile,2=VictimTile,3=Trap Tile,4=visited tile
*/
volatile int grid_matrix [40][40];

#define IR_Sensor_PIN A3
#define LED_PIN 13 //change Me 
#define max_dist 400

#define ONE_TILE_DELAY 200
#define SERVO_45_DELAY 65
#define SERVO_SPEED_FOR 180
#define SERVO_SPEED_BACK 0
#define SERVO_STOP_VAL 90

NewPing left_us(A0,A0,max_dist);
NewPing center_us(A1,A1,max_dist);
NewPing right_us(A2,A2,max_dist);

Servo fright;
Servo fleft;
Servo bright;
Servo bleft;

void(* resetFunc) (void) = 0; //declare reset function @ address 0,crash the machine
void DEBUG(const char* msg){
  Serial.println(msg);
  Serial1.println(msg);
}
void setup(){  
  //Push Button
  pinMode(A11,INPUT_PULLUP);
  pinMode(A10,1);

  //IR Color Sensor
  pinMode(IR_Sensor_PIN, INPUT);

  fright.attach(13);
  fleft.attach(10);
  bright.attach(9);
  bleft.attach(12);

  deploy_servo.attach(11);
  deploy_servo.write(130);

  grid_matrix[0][0]=1; //set the init position to zero,since we will always work from a corner
    
  digitalWrite(A10,0);
  
  // for the 2 Digital comm pins
  pinMode(22,INPUT_PULLUP); 
  pinMode(23,INPUT_PULLUP);
  // for the Interrupt pins
  pinMode(18,INPUT_PULLUP);
  pinMode(19,INPUT_PULLUP);
  pinMode(15,INPUT_PULLUP);
  pinMode(14,INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(18), vicLocINT, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), VizVictimINT, CHANGE);
  attachInterrupt(digitalPinToInterrupt(15), Pause, CHANGE);
  attachInterrupt(digitalPinToInterrupt(14), resetFunc, CHANGE);

  Wire.begin(); 
  Wire2.begin(); 
  Serial.begin(9600);
  Serial1.begin(9600);

  Wire.beginTransmission(0x77);
  int error = Wire.endTransmission();
  if  (error==0){
    DEBUG("Setting Up 10DOF sensors");
    accc.initialize(); //see README
    accc.setI2CBypassEnabled(true);
    bmp085Init(0);    // Set Baseline @ sea level	
    mag.initialize();
    mag.setDataRate(50);
    DEBUG("10DOF Ready");
	  DEBUG("Gathring Data for LOPD system");
    runLOPD();
  }else{
    bmp=false;
    DEBUG("10DOF Not detected at 0x77");
  }
  DEBUG("Ready ...");
  //while(digitalRead(A11)==1){delay(50);}
  DEBUG("Starting...");
  //StartCheckingForVics=enableTimesuff;
  delay(1000);
  update_matrix();
  PrintMatrix(); 
}

void loop(){
//  DEBUG("LOOP");
//  rightWallfollower();
sensorDebug();
delay(1000);
}
