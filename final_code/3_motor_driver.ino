void turn(int dc,bool pos){ // todo:fall back on delays
  //pos=1 turns to the right
  //remeber to keep scanning while turning since we somewhat depend on finding MLX victims while turning
  DEBUG("Turn");
  if (pos==1){
    if (dc==180){
      turn_45_to_the_right_wheels();
      turn_45_to_the_right_wheels();
      turn_45_to_the_right_wheels();
      turn_45_to_the_right_wheels();
     }
     if (dc==90){
      adjust_orient(1);
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
       adjust_orient(0);
       turn_45_to_the_left_wheels();
       turn_45_to_the_left_wheels();
    }
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
void drive_one_tile(){
  drive_forward();
  delay(200); //to be configed
  motor_stop();
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

