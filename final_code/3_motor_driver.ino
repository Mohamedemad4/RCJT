void turn(int dc,bool pos){ // todo:fall back on delays
  //pos=1 turns to the left
  //remeber to keep scanning while turning since we somewhat depend on finding MLX victims while turning
  DEBUG("Turn");
  delay_based_turn(dc,pos);
}

void delay_based_turn(int dc,bool pos){
    DEBUG("delay_based_turn");
    DEBUG_INT(pos);
    DEBUG_INT(dc);
  if (dc==90 && pos==1){
      turn_left();
      delay(SERVO_90_DELAY);
    }
  if (dc==90 && pos==0){
      turn_right();
      delay(SERVO_90_DELAY);
    }
  if(dc==180 && pos==0){
    turn_right();
    delay(SERVO_90_DELAY*2);
    }
  if(dc==180 && pos==1){
    turn_left();
    delay(SERVO_90_DELAY*2);
    }
    motor_stop();
    
}

void motor_stop(){
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
  fright.write(SERVO_SPEED_FOR_RIGHT);
  bright.write(SERVO_SPEED_FOR_RIGHT);
  fleft.write(SERVO_SPEED_FOR_LEFT);
  bleft.write(SERVO_SPEED_FOR_LEFT);
  checkForimpTimeStuff();
}

void drive_backward(){
  DEBUG("drive_backward");
  fright.write(SERVO_SPEED_BACK_RIGHT);
  bright.write(SERVO_SPEED_BACK_RIGHT);
  fleft.write(SERVO_SPEED_BACK_LEFT);
  bleft.write(SERVO_SPEED_BACK_LEFT);
  checkForimpTimeStuff();
}

void turn_left(){
  DEBUG("turn_left");
  fright.write(SERVO_SPEED_FOR_RIGHT);
  bright.write(SERVO_SPEED_FOR_RIGHT);
  fleft.write(SERVO_SPEED_BACK_LEFT);
  bleft.write(SERVO_SPEED_BACK_LEFT);
  checkForimpTimeStuff();
}

void turn_right(){
  DEBUG("turn_right");
  fright.write(SERVO_SPEED_BACK_RIGHT);
  bright.write(SERVO_SPEED_BACK_RIGHT);
  fleft.write(SERVO_SPEED_FOR_LEFT);
  bleft.write(SERVO_SPEED_FOR_LEFT);
  checkForimpTimeStuff();
}
void drop_kit(int nKits=1){
    DEBUG("drop_kit");
    append_value(posX,posY,2); //set current tile as a victims tile
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
      deploy_servo.write(140);
      delay(500);
      deploy_servo.write(60);
    }else{
      delay(100);
      deploy_servo.write(140);
      delay(500);
      deploy_servo.write(60);
      delay(100);
      deploy_servo.write(140);
      delay(500);
      deploy_servo.write(60);
   }
   StartCheckingForVics=1;// imagine how hillarouis that rec would look
}


void trap_cond(){
    if(digitalRead(IR_Sensor_PIN)==1){//if a trap is found 
      motor_stop();
      append_value(posX,posY,3);
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
       delay(100);
     }
     while(GetDist(left_us)<=7){//aligment left
       turn_right();
       delay(100);
     }
}
