void turn(int dc,bool pos){
  //pos=1 turns to the right
  int c;
  int CcompHeading;
  CcompHeading=getCompHeading();
  if (pos){
    c=CcompHeading+dc;
    if (c>360){
      c=c-360;
    }
  }else{
    c=fabs(CcompHeading-dc);
  }
while(isNotWithinRange(3,c,getCompHeading())){
  if (pos){
    turn_right();
  }else{
    turn_left();
  }
}
motor_stop();

}
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
    setSpeeds(speed_default,speed_default, speed_default,speed_default);
  fleft.run(FORWARD);
  fright.run(FORWARD);
  bleft.run(FORWARD);
  bright.run(FORWARD);  
}

void drive_backward(){
    setSpeeds(speed_max,speed_max,speed_max,speed_max);
  fleft.run(BACKWARD);
  fright.run(BACKWARD);
  bleft.run(BACKWARD);
  bright.run(BACKWARD);
}

void turn_left(){
  setSpeeds(speed_max,speed_max,speed_max,speed_max);
  fleft.run(BACKWARD);
  fright.run(FORWARD);
  bleft.run(BACKWARD);
  bright.run(FORWARD);
}

void turn_right(){
  setSpeeds(speed_max,speed_max,
      speed_max,speed_max);
  fleft.run(FORWARD);
  fright.run(BACKWARD);
  bleft.run(FORWARD);
  bright.run(BACKWARD);
}

void drop_kit(){
    motor_stop();
    delay(100);
    deploy_servo.write(180);
    delay(500);
    deploy_servo.write(130);

}

void ServoINT(){
    if (digitalRead(22)==1 && digitalRead(23)==1){
    }
    if (digitalRead(22)==1 &&digitalRead(23)==0){
        Serial.println("Right");
        cpos=2;
        cam.write(160);
    }
    if (digitalRead(22)==0 && digitalRead(23)==1){
        Serial.println("left");   
        cpos=0;
        cam.write(20);
    }
    if (digitalRead(22)==0 && digitalRead(23)==0){
        Serial.println("Forward");
        cpos=1;
        cam.write(90);
    }
}
