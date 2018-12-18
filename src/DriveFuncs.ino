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
  setSpeeds(speed_default,speed_default,
      speed_default,speed_default);
  fleft.run(BACKWARD);
  fright.run(FORWARD);
  bleft.run(BACKWARD);
  bright.run(FORWARD);
}

void turn_right(){
  setSpeeds(speed_default,speed_default,
      speed_default,speed_default);
  fleft.run(FORWARD);
  fright.run(BACKWARD);
  bleft.run(FORWARD);
  bright.run(BACKWARD);
}
