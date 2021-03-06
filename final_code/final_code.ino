/*
 * WORKINGGG CODE RM1 redmi
Team Name: Alaah
Farah Rushdy
Mohamed emad
Fady Nader
*/
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
#define USEMATRIX 0
#define X_COLS 24
#define Y_COLS 24

#define left 0
#define center 1
#define right 2
#define back 3

#define north 0
#define east 1
#define south 2
#define west 3


#define enableTimestuff 1 //enables  CheckForVicimsAndDropKits()  needed for LOPD ,Use me instead of setting StartCheckingForVics
#define gotoVic 1 //enable going to victims on sight

#define IR_Sensor_PIN 28
#define LED_PIN 24  
#define max_dist 30

#define ONE_TILE_DELAY 200
#define SERVO_90_DELAY 700
#define SERVO_45_DELAY 500 //65
#define SERVO_SPEED_FOR 180
#define SERVO_SPEED_BACK 0

#define SERVO_SPEED_BACK_RIGHT 0//90//180
#define SERVO_SPEED_FOR_RIGHT 180//90//0

#define SERVO_SPEED_BACK_LEFT 180//90//0
#define SERVO_SPEED_FOR_LEFT 0//90//180

#define SERVO_STOP_VAL 90


Servo deploy_servo;

float StartwallTemp;
volatile int accelReadings[10];
volatile int base_accelReadings[10];
volatile int accelReadings_curInd;
volatile bool VizvictimIsDetected;
volatile bool PiIsActive;
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
volatile int endRange=1035;
volatile int startRange=27;
NewPing left_us(51,51,max_dist);
NewPing center_us(49,49,max_dist);
NewPing right_us(47,47,max_dist);

Servo fright;
Servo fleft;
Servo bright;
Servo bleft;

float GetIrHeatleft(int w=0x07){//Check the readme for a des.
  float temp;
  uint16_t ret;
  Wire2.beginTransmission(0x5A); 
  Wire2.write(byte(w));               
  Wire2.endTransmission(false);     
  Wire2.requestFrom(0x5A, 3); 
  ret = Wire2.read(); 
  ret |= Wire2.read() << 8;
  temp=ret;
  temp *= .02;
  temp  -= 273.15;
  return temp;
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0,crash the machine
void DEBUG(const char* msg){
  Serial.println(msg);
  Serial1.println(msg);
}
int vic1;
int vic2;
int vic3;
void calibration1(){vic1=GetIrHeatleft();}
void calibration2(){vic2=GetIrHeatleft();}
void calibration3(){vic3=GetIrHeatleft();}

void setup(){  
  //Push Button
  pinMode(A11,INPUT_PULLUP);
  pinMode(A10,1);

  //IR Color Sensor
  pinMode(IR_Sensor_PIN, INPUT);
  pinMode(LED_PIN,1);
  digitalWrite(LED_PIN,0);
  fright.attach(10);
  fleft.attach(12);
  bright.attach(13);//2t3akas
  bleft.attach(11);//2t3akas

  deploy_servo.attach(9);
  deploy_servo.write(60);
  #if USEMATRIX==1
    for (int i=0; i < Y_COLS; i++) {
      for (int j=0; j < X_COLS; j++) {
        grid_matrix[i][j] =6; //fill it with a value we don't use;
      }
    }
    grid_matrix[0][0]=4; //set the init position to zero,since we will always work from a corner
  #endif
  digitalWrite(A10,0);
  
  // for the 2 Digital comm pins  
  pinMode(22,INPUT);//_PULLUP); 
  pinMode(23,INPUT);//_PULLUP);
  // for the Interrupt pins
  pinMode(19,INPUT_PULLUP);
  pinMode(15,INPUT_PULLUP);
  pinMode(18,INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(18), vicLocINT, CHANGE); //12GPIO pi after GND pin from the USB side used to specify location  
  attachInterrupt(digitalPinToInterrupt(19), VizVictimINT, CHANGE); //found victim and pi detect pin goes to 16gp b4 GND on rpi

  Wire.begin(); 
  Wire2.begin(); 
  Serial.begin(9600);
  //Serial1.begin(9600);

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
/*  DEBUG("calibration Mode victim 1");
  while(digitalRead(15)==1){delay(50);}
  calibration1();
  delay(2000);
  DEBUG("calibration Mode victim 2");
  while(digitalRead(15)==1){delay(50);}
  calibration2();
  delay(2000);
  DEBUG("calibration Mode victim 3");
  while(digitalRead(15)==1){delay(50);}
  calibration3();
  int avrgTemp=vic1+vic2+vic3/3;
  Serial.print("avrgTemp: "); 
  Serial.println(avrgTemp);*/

  DEBUG("Ready ...");
  //while(digitalRead(15)==1){delay(50);}
  
  DEBUG("Starting...");
  //attachInterrupt(digitalPinToInterrupt(15), Pause, CHANGE); //button
  StartCheckingForVics=enableTimestuff;
  delay(1000); 
} 


void loop(){
damn();
//sensorDebug();
//delay(1000);
//rat();
 /*drive_forward()  ;
 turn(90,1);
 delay(3000);
 turn(90,0);
 delay(3000);*/
 /* delay(1000);
  turn(90,1);
  delay(3000);
  turn(90,0);
  delay(3000);*/
}
