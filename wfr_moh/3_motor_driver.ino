void turn(int dc,bool pos){ // todo:fall back on delays
  //pos=1 turns to the right
  int c;
  int CcompHeading;
  CcompHeading=getCompHeading();
  if (CcompHeading==370){
    return;
  }
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
  checkForimpTimeStuff();
}
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
  checkForimpTimeStuff();
}

void drive_backward(){
    setSpeeds(speed_max,speed_max,speed_max,speed_max);
  fleft.run(BACKWARD);
  fright.run(BACKWARD);
  bleft.run(BACKWARD);
  bright.run(BACKWARD);
  checkForimpTimeStuff();
}

void turn_left(){
  setSpeeds(speed_max,speed_max,speed_max,speed_max);
  fleft.run(BACKWARD);
  fright.run(FORWARD);
  bleft.run(BACKWARD);
  bright.run(FORWARD);
  checkForimpTimeStuff();
}

void turn_right(){
  setSpeeds(speed_max,speed_max,
      speed_max,speed_max);
  fleft.run(FORWARD);
  fright.run(BACKWARD);
  bleft.run(FORWARD);
  bright.run(BACKWARD);
  checkForimpTimeStuff();
}

void drop_kit(int nKits=1){
    motor_stop();
    StartCheckingForVics=0;
    int i;
    for (i=0;i<25;i++){ //(100+100)*25=5000Msec
      delay(100);
      digitalWrite(LED_PIN,1);
      delay(100);
      digitalWrite(LED_PIN,0);
    }
    if (nKits==1){
      delay(100);
      deploy_servo.write(180);
      delay(500);
      deploy_servo.write(130);
    }else{
      delay(100);
      deploy_servo.write(180);
      delay(500);
      deploy_servo.write(130);
   }
   StartCheckingForVics=1;// imagine how hillarouis that rec would look
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
