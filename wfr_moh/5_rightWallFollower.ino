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

         if(GetDist(center_us)<=7 && GetDist(right_us)<=7 && GetDist(left_us)<=7){  //emergyncy if the robot was traped in a 3 walled tile 
            turn(180,0);
          }

          if(GetDist(right_us)>=7){//always right
              turn(90,1);
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
            
            if(digitalRead(A3)==1){//if a trap is found 
              motor_stop();
              delay(200);
              drive_backward();
              delay(300);

              if(GetDist(left_us)>GetDist(right_us)){//turn left if left is greater than right
                turn(90,0);
                }

              else if(GetDist(left_us)<GetDist(right_us)){//turn right if right is greater than left
                turn(90,1);
                }
              }
}