#include <Wire.h>
#include <Servo.h>
#include <math.h>

#include "NewPing.h"
#include "SoftwareWire.h"
#include "HMC5883L.h"
#include "bmp085.h"
#include "I2Cdev.h"
#include "MPU6050.h"

#include <EEPROM.h>

//Left Sensor connected to A4,A5
//Right Sensor connected to Digital pins 20,21
SoftwareWire Wire2( A4, A5);// SDA,SCL

MPU6050 accc;
HMC5883L mag;
bool bmp;

#define X_COLS 24
#define Y_COLS 24

#define enableTimesuff 0 //enables  CheckForVicimsAndDropKits()  needed for LOPD ,Use me instead of setting StartCheckingForVics
#define gotoVic 1 //enable going to victims on sight

#define IR_Sensor_PIN A3
#define LED_PIN 13 //change Me 
#define max_dist 400

#define ONE_TILE_DELAY 200
#define SERVO_45_DELAY 65
#define SERVO_SPEED_FOR 180
#define SERVO_SPEED_BACK 0
#define SERVO_STOP_VAL 90


Servo deploy_servo;

float StartwallTemp;
volatile int accelReadings[10];
volatile int base_accelReadings[10];
volatile int accelReadings_curInd;
volatile bool VizvictimIsDetected;
volatile bool StartCheckingForVics;
volatile int run_check_start_tile;
volatile int cpos=4; //contains current position of the cam Servo,2=right,0=left,1=Forward
volatile int vtype=4; //contains the Viz victims type,2=H,0=U,1=S
volatile unsigned long previousMillisCheckForImpTStuff = 0;

volatile int orientation=0; // 0 N , 1 E , 2 S , 3 W,assume f from starting pos = N
volatile int posX=0;// assume 0,0 on start position for Now(change to the center of the maze)
volatile int posY=0; //also change it from check_start_tile();

/*
0=Wall,1=unvistedTile,2=VictimTile,3=Trap Tile,4=visited tile
*/
volatile int grid_matrix [X_COLS][Y_COLS];

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

  fright.attach(10);
  fleft.attach(12);
  bright.attach(11);
  bleft.attach(13);

  deploy_servo.attach(9);
  deploy_servo.write(60);

  for (int i=0; i < Y_COLS; i++) {
    for (int j=0; j < X_COLS; j++) {
      grid_matrix[i][j] =6; //fill it with a value we don't use;
    }
  }
  grid_matrix[0][0]=4; //set the init position to zero,since we will always work from a corner
  
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
  while(digitalRead(A11)==1){delay(50);}
  DEBUG("Starting...");
  StartCheckingForVics=enableTimesuff;
  delay(1000); 
}

void SaveMatrixToEEPROM()
{
   int address=0;
   DEBUG("QuickSaving....");
   for (int i = 0; i < X_COLS; i++) {
       for (int j = 0; j < Y_COLS; j++) {
          EEPROM.update(address,grid_matrix[i][j]);
          address+=2;
       }
   }
}

void LoadFromEEPROM(){
   int address=0;
   DEBUG("Restoring....");
   for (int i = 0; i < X_COLS; i++)  {
       for (int j = 0; j < Y_COLS; j++) {
          grid_matrix[i][j]=EEPROM.read(address);
          address+=2;
       }
   }
}
void loop(){
  //rightWallfollower();
  drive_forward();
  delay(2000);
  drive_backward();
  delay(2000);
  turn_right();
  delay(2000);
  turn_left();
  delay(2000);
  motor_stop();
  while(1){}
  
}
