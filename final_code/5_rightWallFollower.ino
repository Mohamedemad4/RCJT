void rightWallfollower(){
  //right wall follower 
      while(GetDist(center_us)>10 && GetDist(left_us)>7 && GetDist(right_us)>7){
        drive_forward();
        }
 
          //!!!dont forget to calibrate the us_  in the maze!!!
          
         if(GetDist(center_us)<=10  ){  //found a wall infront of you!
            if(GetDist(right_us)<=5 && GetDist(center_us)<=10){
              turn(90,0);
            }
          if(GetDist(right_us)>=GetDist(left_us)){//turn right if there isn't a wall on the right
            turn(90,1);
            motor_stop();
            delay(100);
 
          }

            else if(GetDist(left_us)>GetDist(right_us)){// turn left if there is a wall on the right
              turn(90,0);
              motor_stop();
              delay(100);
              }
         }

        
           align_and_emergency();
           trap_cond();
}