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
 
#define max_dist 100
#define speed_default 100
NewPing sonar0(A0,A0,max_dist);
NewPing sonar1(A1,A1,max_dist);
NewPing sonar2(A2,A2,max_dist);

int servo_position = 0 ;


AF_DCMotor bleft(3, MOTOR12_64KHZ); //1
AF_DCMotor bright(4, MOTOR12_64KHZ); //2
  
AF_DCMotor fleft(2, MOTOR12_64KHZ); //2
AF_DCMotor fright(1, MOTOR12_64KHZ); //4

void setup(){
	name_servo.attach(10);
	Serial.begin(9600);
    setSpeeds(speed_default,speed_default,
      speed_default,speed_default);
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



void Sdebug(){
sonarDebug();
delay(1000);
}
void aloop(){
delay(2000);
drive_forward();
delay(500);
turn_right();
delay(100);
}
void loop(){
	delay(6000);
	Serial.println("Starting");
	drive_forward();
	delay(6000);
	Serial.println("Starting!");
	motor_stop();
}

void Servoloop(){
  for (servo_position = 0; servo_position <=180; servo_position +=1){
    name_servo.write(servo_position);
    Serial.println(GetDist(sonar0));
  }
  for (servo_position=180; servo_position >= 0; servo_position -=1){
    name_servo.write(servo_position);
    delay(10);
  }
}
