void Pause(){
  while(digitalRead(A11)==1){delay(50);}
}

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

void VizVictimINT(){
    if (digitalRead(22)==1 && digitalRead(23)==1){
    }
    if (digitalRead(22)==1 &&digitalRead(23)==0){
        Serial.println("H");
        vtype=2;
        VizvictimIsDetected=1;
    }
    if (digitalRead(22)==0 && digitalRead(23)==1){
        Serial.println("U");   
        vtype=0;
        VizvictimIsDetected=1;
    }
    if (digitalRead(22)==0 && digitalRead(23)==0){
        Serial.println("S");
        vtype=1;
        VizvictimIsDetected=1;
    }
}
