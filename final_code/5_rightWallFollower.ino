void endofcode(){
  while(1){DEBUG("END OF CODE ;;;");}}
void s(){
  //right wall follower 
      while(GetDist(center_us)>15 && GetDist(left_us)>7 && GetDist(right_us)>7){
        drive_forward();
        }
 
          //!!!dont forget to calibrate the us_  in the maze!!!
          
         if(GetDist(center_us)<=15  ){  //found a wall infront of you!
              DEBUG("found WALL");
              DEBUG_INT(GetDist(center_us));
            if(GetDist(left_us)>=GetDist(right_us)){
              turn(90,0);
             //turn_left();
             DEBUG("right_us");
             DEBUG_INT(GetDist(right_us));
             //delay(1700);
             //motor_stop();
             //delay(50);
            }
          

            else if(GetDist(right_us)>GetDist(left_us)){// turn left if there is a wall on the right
            DEBUG("left_us");
            DEBUG_INT(GetDist(left_us));
            turn(90,1);
            //  turn_right();
             // delay(1700);
              motor_stop();
              delay(50);
              }

                         align_and_emergency();
                         trap_cond();
//                         turn(90,1);
      }

}
void aas(){
  drive_forward();
  delay(2000);
  turn_right();
  delay(SERVO_90_DELAY);
  motor_stop();
  while(1){}
}
