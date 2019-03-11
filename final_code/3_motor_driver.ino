void turn(int dc,bool pos){ // todo:fall back on delays
  //pos=1 turns to the right
  //remeber to keep scanning while turning since we somewhat depend on finding MLX victims while turning
  int c;
  int CcompHeading;
  DEBUG("Turn");
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

void motor_stop(){
  DEBUG("STOP");
}

void drive_forward(){
  DEBUG("drive_forward");
  checkForimpTimeStuff();
}

void drive_backward(){
  DEBUG("drive_backward");
  checkForimpTimeStuff();
}

void turn_left(){
  DEBUG("turn_left");
  checkForimpTimeStuff();
}

void turn_right(){
  DEBUG("turn_right");
  checkForimpTimeStuff();
}

void drop_kit(int nKits=1){
    DEBUG("drop_kit");
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

