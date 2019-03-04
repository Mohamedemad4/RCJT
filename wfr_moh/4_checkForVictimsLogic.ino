bool CheckForVicimsAndDropKits(){
  if (VizvictimIsDetected==1){
    VizvictimIsDetected=0;       //confirm
    return checkVizWallsandDropKits();
    }
  if (!isNotWithinRange(28,GetIrHeatleft(),40)){ //see if there is even anything
    if(isThisWall(left_us)){ //check walls
      turn(90,1);
      drop_kit(1);
      return 1;
    }if(!isThisWall(left_us) && gotoVic){
      turn(90,0);
      return 1;
    }
  }
  if (!isNotWithinRange(28,GetIrHeatright(),40)){
    if(isThisWall(right_us)){
      turn(90,0);
      drop_kit(1);
      return 1;
    }if(!isThisWall(right_us) && gotoVic){
      turn(90,0);
      return 1;
    }
  }
  return 0;
}

bool checkVizWallsandDropKits(){
  int nKits;
  if (vtype==2){ //H
      nKits=2;
  }
  if(vtype==1){ //S
    nKits=1;
  }
  if(vtype==0){ //S
    nKits=0;
  }
  if (cpos==1){
      if(isThisWall(center_us)){
          turn(180,1);
          drop_kit(nKits);
          return 1;
      }
      if(!isThisWall(center_us) && gotoVic){
          return 1; // we assume that the robot is already orinted towards the Victim 
          //and therefore will go to the victim and re Run this function 
      }
    }
    else if (cpos==0){
      if(isThisWall(left_us)){
          turn(90,1);
          drop_kit(nKits);
          return 1;
      }if(!isThisWall(left_us) && gotoVic){
        turn(90,0); //we orient ourselves towards the victim and proced to return to loop()
        return 1;
      }
    }
    else if (cpos==2){
      if(isThisWall(right_us)){
        turn(90,0);
        drop_kit(nKits);
        return 1;
      }if(!isThisWall(right_us) && gotoVic){
        turn(90,1); 
        return 1;
      }
    }

    return 0;
}
