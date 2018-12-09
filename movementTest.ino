//Simple movment test for the robot
#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor bright(4, MOTOR12_64KHZ);
AF_DCMotor bleft(3, MOTOR12_64KHZ);

AF_DCMotor fright(1, MOTOR12_64KHZ);
AF_DCMotor fleft(2, MOTOR12_64KHZ);


Servo name_servo;               // Define any servo name

void setup(){
	name_servo.attach(10);          // Define the servo signal pins
	Serial.begin(9600);
	fleft.setSpeed(255);
	fright.setSpeed(255);
	bleft.setSpeed(255);
	bright.setSpeed(255);
}

void loop(){
	int servo_position = 0 ;
    drive_forward();
 	for (servo_position = 0; servo_position <=180; servo_position +=1){
	 	   name_servo.write(servo_position);
	 	   delay(10);
 	}
 	motor_stop();
    for (servo_position=180; servo_position >= 0; servo_position -=1){
    	name_servo.write(servo_position);
    	delay(10);
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