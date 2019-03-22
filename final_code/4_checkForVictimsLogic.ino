void CheckForVicimsAndDropKits(){
  if (StartCheckingForVics==0){
     return;
    }
  if (VizvictimIsDetected==1){
    VizvictimIsDetected=0;       //confirm
    DEBUG("VizvictimIsDetected");
    checkVizWallsandDropKits();
    return;
    }
  if (!isNotWithinRange(25,GetIrHeatleft(),42)){ //see if there is even anything
     DEBUG("Heated VICTIM is in the left");
    if(isThisWall(left_us)){ //check walls
      turn(90,1);
      drop_kit(1);  
      return;
    }if(!isThisWall(left_us) && gotoVic){
      turn(90,0);
      return;
    }
  }
  if (!isNotWithinRange(25,GetIrHeatright(),42)){
    DEBUG("Heated VICTIM is in the Right");
    if(isThisWall(right_us)){
      turn(90,0);
      drop_kit(1);
      return ;
    }if(!isThisWall(right_us) && gotoVic){
      turn(90,1);
      return ;
    }
  }
  return;
}

bool checkVizWallsandDropKits(){
  int nKits;
  if (vtype==2){ //H
      nKits=2;
      DEBUG("Victim is an H");
  }
  if(vtype==1){ //S
    nKits=1;
    DEBUG("Victim is an S");
  }
  if(vtype==0){ //U
    nKits=0;
    DEBUG("Victim is a U ");
  }
  if (cpos==1){
      DEBUG("VICTIM is in the front");
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
      DEBUG("Victim Is to the left");
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
      DEBUG("VICTIM is in the right");
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
