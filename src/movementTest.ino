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
NewPing Sonar0(A0,A0,max_dist);
NewPing Sonar1(A1,A1,max_dist);
NewPing Sonar2(A2,A2,max_dist);

int servo_position = 0 ;


AF_DCMotor bleft(1, MOTOR12_64KHZ);
AF_DCMotor bright(2, MOTOR12_64KHZ);
  
AF_DCMotor fleft(3, MOTOR12_64KHZ);
AF_DCMotor fright(4, MOTOR12_64KHZ);


void setup(){
	name_servo.attach(10);
	Serial.begin(9600);
    setSpeeds(speed_default,speed_default,
      speed_default,speed_default);
}

int GetDist(NewPing sonarN){
    return sonarN.ping_cm();  
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
    Serial.println(GetDist(Sonar0));
  }
  for (servo_position=180; servo_position >= 0; servo_position -=1){
    name_servo.write(servo_position);
    delay(10);
  }
}