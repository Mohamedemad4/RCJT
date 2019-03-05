void pause(){
  while(digitalRead(A11)==1){delay(50);}
}
void(* resetFunc) (void) = 0; //declare reset function @ address 0
bool isNotWithinRange(int range,int l1,int l2){
  if ((fabs(l1-l2)>range)){
    return 1;
  }
  return 0;

}
bool isThisWall(NewPing sonar){
    if(GetDist(sonar)>30){
      return 0;
    }
    return 1;
}

bool CheckForVicimsAndDropKits(){
  if (digitalRead(24)==0){
    digitalWrite(24,1);          //drive the pin HIGH to confirm;
    return checkVizWallsandDropKits();
    }
  if (!isNotWithinRange(28,GetIrHeatleft(),40)){
    if(isThisWall(left_us)){
      drop_kit();
      return 1;
    }
  }
  if (!isNotWithinRange(28,GetIrHeatright(),40)){
    if(isThisWall(right_us)){
      drop_kit();
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
          drop_kit(nKits);
          return 1;
      }
    }
    else if (cpos==0){
      if(isThisWall(left_us)){
          drop_kit(nKits);
          return 1;
      }
    }
    else if (cpos==2){
      if(isThisWall(right_us)){
        drop_kit(nKits);
        return 1;
      }
    }

    return 0;
}

void VizVictimINT(){
    if (digitalRead(22)==1 && digitalRead(23)==1){
    }
    if (digitalRead(22)==1 &&digitalRead(23)==0){
        Serial.println("H");
        vtype=2;
    }
    if (digitalRead(22)==0 && digitalRead(23)==1){
        Serial.println("U");   
        vtype=0;
    }
    if (digitalRead(22)==0 && digitalRead(23)==0){
        Serial.println("S");
        vtype=1;
    }
}