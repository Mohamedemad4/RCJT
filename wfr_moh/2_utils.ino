void Pause(){
  noInterrupts();
  while(digitalRead(A11)==1){delay(50);}
  interrupts();
}

void SeeIfLOP(){
  int SomearbRange=10;
  //for now we are using avrgs//deal with it 
  if (isNotWithinRange(SomearbRange,average(base_accelReadings,10),average(accelReadings,10))){
    Serial.println("LOP");
  }
}
bool isNotWithinRange(int range,int l1,int l2){
  if ((fabs(l1-l2)>range)){
    return 1;
  }
  return 0;

}

float average (int * array, int len)  // assuming array is int.
{
  long sum = 0L ;  // sum will be larger than an item, long for safety.
  for (int i = 0 ; i < len ; i++)
    sum += array [i] ;
  return  ((float) sum) / len ;  // average will be fractional, so float may be appropriate.
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
