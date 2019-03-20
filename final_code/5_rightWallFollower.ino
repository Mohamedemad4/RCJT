void rightWallfollower(){
  //right wall follower 
      while(GetDist(center_us)>25){
        drive_forward();
        }
 
          //!!!dont forget to calibrate the us_  in the maze!!!
          
         if(GetDist(center_us)<=25  ){  //found a wall infront of you!
          
          if(GetDist(right_us)>=5){//turn right if there isn't a wall on the right
            turn_right();
            delay(600);
            //turn(90,1);
          }

            else if(GetDist(right_us)<5){// turn left if there is a wall on the right
              turn_left();
              delay(600);
              //turn(90,0);
              }
         }

          
            align_and_emergency();
            trap_cond();
}
void leftWallfollower(){
  //right wall follower 
      while(GetDist(center_us)>25){
        drive_forward();
        }
 
          //!!!dont forget to calibrate the us_  in the maze!!!
          
         if(GetDist(center_us)<=25  ){  //found a wall infront of you!
          
          if(GetDist(left_us)>=5){//turn right if there isn't a wall on the right
            //turn_right();
            //delay(600);
            turn(90,0);
          }

            else if(GetDist(right_us)<5){// turn left if there is a wall on the right
              //turn_left();
              //delay(600);
              turn(90,1);
              }
         }

          
            align_and_emergency();
            trap_cond();
}