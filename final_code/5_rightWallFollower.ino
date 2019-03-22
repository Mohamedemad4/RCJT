void rat(){
 while(GetDist(center_us)>=7){
        drive_forward();
        //delay(50);
 }
 if(GetDist(center_us)<7){
   do_the_heavyLifting();
 } 
 align_and_emergency();
}
void do_the_heavyLifting(){
if(GetDist(right_us)>GetDist(left_us)){
  turn(90,1);
  motor_stop();
  delay(100);
}
else if(GetDist(right_us)<GetDist(left_us)){
  turn(90,0);
  motor_stop();
  delay(100);
}
}


//1 = left ,0=right
void damn (){
  while(GetDist(center_us)>10){
    drive_forward();
    }

 if(GetDist(center_us)<=10){
  
  if(GetDist(right_us)>=GetDist(left_us)){
    turn(90,0);
    }

  else if(GetDist(right_us)<GetDist(left_us)){
    turn(90,1);
      }
    }


    if(GetDist(center_us)<10 && GetDist(right_us)<=5 && GetDist(left_us)<=5){}
//alignment 

while(GetDist(right_us)<5){
  turn_left();
  delay(100);
  }

while(GetDist(left_us)<5){
  turn_right();
  delay(100);
  }

}
