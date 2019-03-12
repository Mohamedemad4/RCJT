void rightWallfollower(){
  //right wall follower 
      while(GetDist(center_us)>15){
          drive_forward();
        }
 
          //!!!dont forget to calibrate the us_  in the maze!!!
          
         if(GetDist(center_us)<=15  ){  //found a wall infront of you!
          
          if(GetDist(right_us)>=7){//turn right if there isn't a wall on the right
            turn(90,1);

          }

            else if(GetDist(right_us)<7){// turn left if there is a wall on the right
              turn(90,0);
              }
         }

          if(GetDist(right_us)>=7){//always right
              turn(90,1);
            }
            align_and_emergency();
            trap_cond();
}