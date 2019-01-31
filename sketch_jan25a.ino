/*Pinout
A0
A1
A2
10 Servo
*/
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

Servo name_servo;
 
#define max_dist 500
#define speed_default 255
NewPing sonar0(A0,A0,max_dist);
NewPing sonar1(A1,A1,max_dist);
NewPing sonar2(A2,A2,max_dist);

AF_DCMotor bleft(3, MOTOR12_64KHZ); //1
AF_DCMotor bright(4, MOTOR12_64KHZ); //2
  
AF_DCMotor fleft(2, MOTOR12_64KHZ); //2
AF_DCMotor fright(1, MOTOR12_64KHZ); //4

void setSpeeds(int fleft_s ,int fright_s ,int bleft_s , int bright_s ){
  fleft.setSpeed(fleft_s);
  fright.setSpeed(fright_s);
  bleft.setSpeed(bleft_s);
  bright.setSpeed(bright_s);
}
void motor_stop(){
  fleft.run(RELEASE);
  fright.run(RELEASE);
  bleft.run(RELEASE);
  bright.run(RELEASE);
}

void drive_forward(){
  fleft.run(FORWARD);
  fright.run(FORWARD);
  bleft.run(FORWARD);
  bright.run(FORWARD);  
}

void drive_backward(){
  fleft.run(BACKWARD);
  fright.run(BACKWARD);
  bleft.run(BACKWARD);
  bright.run(BACKWARD);
}

void turn_left(){
  setSpeeds(speed_default,speed_default,
      speed_default,speed_default);
  fleft.run(BACKWARD);
  fright.run(FORWARD);
  bleft.run(BACKWARD);
  bright.run(FORWARD);
}

void turn_right(){
  setSpeeds(speed_default,speed_default,
      speed_default,speed_default);
  fleft.run(FORWARD);
  fright.run(BACKWARD);
  bleft.run(FORWARD);
  bright.run(BACKWARD);

}
void setup(){
  name_servo.attach(10);
  Serial.begin(9600);
    setSpeeds(speed_default,speed_default,
      speed_default,speed_default);
  delay(2000);
  
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
void loopppp(){
  sonarDebug();
  delay(1000);
}
void tloop(){
  Serial.println("Starting");
  drive_forward();
  delay(600);
  turn_right();
  delay(500);
  turn_left();
  delay(500);
  drive_backward();
  delay(500);
  motor_stop();
}
int left;
int center;
int right;

void looppppppppp(){
  drive_forward();
  delay(5);
  left=GetDist(sonar0);
  center=GetDist(sonar1);
  right=GetDist(sonar2); 
  
  if ((center<20) && (right>left)){
    motor_stop();
    turn_right();
    delay(300);
    drive_forward();
  }
  if ((center<20) && (left>right)){
      motor_stop();
    turn_left();
    delay(300);
    drive_forward();
  }   
     
  if (left>right){
      motor_stop();
        turn_left();
        delay(5);
      }
     if (left<right){
        motor_stop();
        turn_right();
        delay(5);
     }  
  motor_stop();
}

void looppp(){
  left=GetDist(sonar0);
  center=GetDist(sonar1);
  right=GetDist(sonar2); 

  if (center<=10)  { 
    if (right > left) { 
       turn_right(); 
      } 
    if (left>right) {
       turn_left();
     }
   }
   if (left <= 15) {
      if (center > right)  {
           drive_forward();
         }
      if (right>center)  {
          turn_right();
         }
    }
    if (right<=15)  {
      if (center>left) {
           drive_forward();     
       }  
    }
    if (left>center) {
      turn_left(); 
     }
     delay(50);
 }
 void loop(){
   left=GetDist(sonar0);
  center=GetDist(sonar1);
  right=GetDist(sonar2);
  //drive forward
  if(center > 15){
    drive_forward();
  }
  if(left<right){
    turn_right();
  }
  if (left>right){
    turn_left();
  }
  delay(1000);
}
