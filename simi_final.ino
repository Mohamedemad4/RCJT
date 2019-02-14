/*Pinout
A0
A1
A2
10 Servo
*/

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>
#include <math.h>


Adafruit_MLX90614 mlx_r = Adafruit_MLX90614();
Adafruit_MLX90614 mlx_l = Adafruit_MLX90614();

Servo deploy_servo;
 
#define max_dist 400
#define speed_default 155
#define speed_max 255
NewPing sonar0(A0,A0,max_dist);
NewPing sonar1(A1,A1,max_dist);
NewPing sonar2(A2,A2,max_dist);

AF_DCMotor fleft(2, MOTOR12_1KHZ); //2
AF_DCMotor fright(1, MOTOR12_1KHZ); //4

AF_DCMotor bleft(3, MOTOR34_1KHZ); //1
AF_DCMotor bright(4, MOTOR34_1KHZ); //2





int isNotWithinRange(int range,int l1,int l2){
  if ((fabs(l1-l2)>range)){
    return 1;
  }
  return 0;

}

  

int GetDist(NewPing sonarN){
    return sonarN.ping_cm();  
}
 
void sonarDebug(){
         Serial.print("Distance on A0: ");
         Serial.println(GetDist(sonar0));
         Serial.print("Distance on A1: ");
         Serial.println(GetDist(sonar1));
         Serial.print("Distance on A2: ");
         Serial.println(GetDist(sonar2));
}

void setup(){
  mlx_r.begin();
  mlx_l.begin();
  
  deploy_servo.attach(10);
  deploy_servo.write(130);
  pinMode(A9,INPUT_PULLUP);
  pinMode(A8,1);
  digitalWrite(A8,0);
  
  Serial.begin(9600);
  setSpeeds(speed_default,speed_default,
      speed_default,speed_default);
  while (digitalRead(A8)==1){
    delay(50);
  }
  delay(1000);
  Serial.println("Starting...");
  while(digitalRead(A9)==1){delay(50);}
}



void deploy(){
      deploy_servo.write(180);
      delay(500);
      deploy_servo.write(130);


        
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

int ReadHeat(){
  mlx_l.
  }
