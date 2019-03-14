void turn(int dc,bool pos){ // todo:fall back on delays
  //pos=1 turns to the right
  //remeber to keep scanning while turning since we somewhat depend on finding MLX victims while turning
  DEBUG("Turn");
  if(mag.testConnection() && ONaVictimStile==0){ //electromagnitc interference from HVs
    int c_status=compass_based_turn(dc,pos);
    if (c_status==0){
      delay_based_turn(dc,pos);
    }
  }else{
    delay_based_turn(dc,pos);
  }
}

bool compass_based_turn(int dc,bool pos){
  int c;
  int CcompHeading;
  CcompHeading=getCompHeading();
  if (CcompHeading==370){
    return 0;
  }
  if (pos){
    c=CcompHeading+dc;
    if (c>360){
      c=c-360;
    }
  }else{
    c=fabs(CcompHeading-dc);
  }
  DEBUG("compass_based_turn");
  DEBUG_INT(pos);
  DEBUG_INT(dc);
  gotoVic=0; //so it doesn't execute turn() while turning,and can still scan for HVs (discuss)
  unsigned long start = millis();
  while(isNotWithinRange(3,c,getCompHeading())){
    if (pos){
      turn_right();
    }else{
      turn_left();
    }
    if((millis()-start)>500){ //give it 500Ms to work
    DEBUG("Took too long,reseting");
      if (pos){
        turn_right();
        delay(500); //reset POS
      }else{
        turn_left();
        delay(500);
      }
      return 0;
    }
    checkForimpTimeStuff();
  }
  DEBUG("adjusting Orintation");
  if(dc==90){
    adjust_orient(pos);
  }
  if (dc==180){
    adjust_orient(pos);
    adjust_orient(pos);
  }
  return 1;
}

void delay_based_turn(int dc,bool pos){
    DEBUG("delay_based_turn");
    DEBUG_INT(pos);
    DEBUG_INT(dc);
    if (pos==1){
    if (dc==180){
      turn_45_to_the_right_wheels();
      turn_45_to_the_right_wheels();
      turn_45_to_the_right_wheels();
      turn_45_to_the_right_wheels();
     }
     if (dc==90){
      turn_45_to_the_right_wheels();
      turn_45_to_the_right_wheels();
     }
    }
  else{
    if (dc==180){
      turn_45_to_the_left_wheels();
      turn_45_to_the_left_wheels();
      turn_45_to_the_left_wheels();
      turn_45_to_the_left_wheels();
     }
     if(dc==90){
       turn_45_to_the_left_wheels();
       turn_45_to_the_left_wheels();
    }
  }
  DEBUG("adjusting Orintation");
  if(dc==90){
    adjust_orient(pos);
  }
  if (dc==180){
    adjust_orient(pos);
    adjust_orient(pos);
  }
}

void motor_stop(){
  DEBUG("STOP");
  fright.write(SERVO_STOP_VAL);
  bright.write(SERVO_STOP_VAL);
  fleft.write(SERVO_STOP_VAL);
  bleft.write(SERVO_STOP_VAL);
}

void turn_45_to_the_left_wheels(){
  turn_left();
  delay(SERVO_45_DELAY);
  motor_stop();
}

void turn_45_to_the_right_wheels(){
  turn_right();
  delay(SERVO_45_DELAY);
  motor_stop();
}
void drive_one_tile_f(){
  drive_forward();
  delay(ONE_TILE_DELAY); //to be configed
  motor_stop();
  update_location(1);
}

void drive_one_tile_b(){
  drive_forward();
  delay(ONE_TILE_DELAY); //to be configed
  motor_stop();
  update_location(2);
}
void drive_forward(){
  DEBUG("drive_forward");
  fright.write(SERVO_SPEED_FOR);
  bright.write(SERVO_SPEED_FOR);
  fleft.write(SERVO_SPEED_FOR);
  bleft.write(SERVO_SPEED_FOR);
  checkForimpTimeStuff();
}

void drive_backward(){
  DEBUG("drive_backward");
  fright.write(SERVO_SPEED_BACK);
  bright.write(SERVO_SPEED_BACK);
  fleft.write(SERVO_SPEED_BACK);
  bleft.write(SERVO_SPEED_BACK);
  checkForimpTimeStuff();
}

void turn_left(){
  DEBUG("turn_left");
  fright.write(SERVO_SPEED_BACK);
  bright.write(SERVO_SPEED_BACK);
  fleft.write(SERVO_SPEED_FOR);
  bleft.write(SERVO_SPEED_FOR);
  checkForimpTimeStuff();
}

void turn_right(){
  DEBUG("turn_right");
  fright.write(SERVO_SPEED_FOR);
  bright.write(SERVO_SPEED_FOR);
  fleft.write(SERVO_SPEED_BACK);
  bleft.write(SERVO_SPEED_BACK);
  checkForimpTimeStuff();
}

void drop_kit(int nKits=1){
    DEBUG("drop_kit");
    ONaVictimStile=1;
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

void trap_cond(){
    if(digitalRead(IR_Sensor_PIN)==1){//if a trap is found 
      motor_stop();
      delay(200);
      drive_backward();
      delay(300);
      turn(180,1);
      if(GetDist(left_us)>GetDist(right_us)){//turn left if left is greater than right
        turn(90,0);
        }
      else if(GetDist(left_us)<GetDist(right_us)){//turn right if right is greater than left
        turn(90,1);
        }
      }
}

void align_and_emergency(){
   if(GetDist(center_us)<=7 && GetDist(right_us)<=7 && GetDist(left_us)<=7){  //emergyncy if the robot was traped in a 3 walled tile 
     turn(180,0);
   }
     //!!!dont forget to calibrate the delay  in the maze!!!
   while(GetDist(right_us)<=7){//aligment right
       turn_left();
       delay(50);
     }
     while(GetDist(left_us)<=7){//aligment left
       turn_right();
       delay(50);
     }
}