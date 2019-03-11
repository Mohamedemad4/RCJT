void Pause(){
  noInterrupts();
  DEBUG("PAUSE");
  while(digitalRead(A11)==1){delay(50);}
  interrupts();
}

void SeeIfLOP(){
  int SomearbRange=10;
  //for now we are using avrgs//deal with it 
  if (isNotWithinRange(SomearbRange,average(base_accelReadings,10),average(accelReadings,10))){
    DEBUG("LOPD");
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
        DEBUG("H");
        vtype=2;
        VizvictimIsDetected=1;
    }
    if (digitalRead(22)==0 && digitalRead(23)==1){
        DEBUG("U");   
        vtype=0;
        VizvictimIsDetected=1;
    }
    if (digitalRead(22)==0 && digitalRead(23)==0){
        DEBUG("S");
        vtype=1;
        VizvictimIsDetected=1;
    }
}

void vicLocINT(){
    if (digitalRead(22)==1 && digitalRead(23)==1){
    }
    if (digitalRead(22)==1 &&digitalRead(23)==0){
        DEBUG("Right");
        cpos=2;
    }
    if (digitalRead(22)==0 && digitalRead(23)==1){
        DEBUG("left");   
        cpos=0;
    }
    if (digitalRead(22)==0 && digitalRead(23)==0){
        DEBUG("Forward");
        cpos=1;
    }
}

void checkForLOPD(){
  if (accc.testConnection()==true){
    accelReadings[accelReadings_curInd]=GetAccXpY();
    if (accelReadings_curInd<10){
      accelReadings_curInd++;
    }else if(accelReadings_curInd==10){
      accelReadings_curInd=0;
      SeeIfLOP(); //to much global vars for my taste
    }
  }
}

void runLOPD(){
  int i=0;
  for (i;i<10;i++){
    base_accelReadings[accelReadings_curInd]=GetAccXpY(); //TODO:make me more fancy with 2D arrays
    if (accelReadings_curInd<10){
     accelReadings_curInd++;
    }else if(accelReadings_curInd==10){
     accelReadings_curInd=0;
   }
   delay(500);
  }
  accelReadings_curInd=0;
}

void checkForimpTimeStuff(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisCheckForImpTStuff >= 500 && StartCheckingForVics) {//is True every 0.5S
    previousMillisCheckForImpTStuff = currentMillis;
    DEBUG("checkForimpTimeStuff()");
    checkForLOPD();
    CheckForVicimsAndDropKits();
  }
}