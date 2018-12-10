//Simple movment test for the robot
#include <AFMotor.h>
#include <Servo.h>

int speed=100;
AF_DCMotor bright(4, MOTOR12_64KHZ);
AF_DCMotor bleft(3, MOTOR12_64KHZ);

AF_DCMotor fright(1, MOTOR12_64KHZ);
AF_DCMotor fleft(2, MOTOR12_64KHZ);

Servo name_servo;               // Define any servo name

void setup(){
	pinMode(A1, 1);
    pinMode(A0, 1);
    pinMode(A2,1);
	name_servo.attach(10);          // Define the servo signal pins
	Serial.begin(9600);
	fleft.setSpeed(speed);
	fright.setSpeed(speed);
	bleft.setSpeed(speed);
	bright.setSpeed(speed);
}

int GetCurrentDist(int pingPin){
  digitalWrite(pingPin, LOW);
  delay(2);
  digitalWrite(pingPin, HIGH);
  delay(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  return microsecondsToCentimeters(pulseIn(pingPin, HIGH));
}



long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}



void loop(){
	int servo_position = 0 ;
    drive_forward();
 	for (servo_position = 0; servo_position <=180; servo_position +=1){
	 	   name_servo.write(servo_position);
	 	   delay(10);
	 	   Serial.print("Distance on A0: ");
	 	   Serial.println(GetCurrentDist(A0));
	 	   Serial.print("Distance on A1: ");
	 	   Serial.println(GetCurrentDist(A1));
	 	   Serial.print("Distance on A2: ");
	 	   Serial.println(GetCurrentDist(A2));
 	}
 	motor_stop();
    for (servo_position=180; servo_position >= 0; servo_position -=1){
    	name_servo.write(servo_position);
    	delay(10);
	 	Serial.print("Distance on A0: ");
	 	Serial.println(GetCurrentDist(A0));
	 	Serial.print("Distance on A1: ");
	 	Serial.println(GetCurrentDist(A1));
	 	Serial.print("Distance on A2: ");
	 	Serial.println(GetCurrentDist(A2));
  	}
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
	fleft.run(BACKWARD);
	fright.run(FORWARD);
	bleft.run(BACKWARD);
	bright.run(FORWARD);
}

void turn_right(){
	fleft.run(FORWARD);
	fright.run(BACKWARD);
	bleft.run(FORWARD);
	bright.run(BACKWARD);
}
