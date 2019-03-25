void Pause(){
  noInterrupts();
  DEBUG("PAUSE");
  motor_stop();
  while(digitalRead(15)==1){delay(50);}
  interrupts();
}

void SeeIfLOP(){
  int SomearbRange=10;
  //for now we are using avrgs//deal with it 
  /*if (isNotWithinRange(SomearbRange,average(base_accelReadings,10),average(accelReadings,10))){
    DEBUG("LOPD");
  }*/
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
    if(GetDist(sonar)>10){
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
     DEBUG_INT(digitalRead(22));
     DEBUG_INT(digitalRead(23));
    if (digitalRead(22)==1 && digitalRead(23)==1){
      DEBUG("PI just sent activation signal");
      PiIsActive=1;
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
  for (int i=0;i<10;i++){
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

void check_start_tile(){
  if(run_check_start_tile==10){
    if(posX ==0 && posY==0){
      DEBUG("WE are on the start tile");
      motor_stop();
      delay(10000);
    }
  }else{
    run_check_start_tile++;
  }
  DEBUG_INT(run_check_start_tile);
}
void checkForimpTimeStuff(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisCheckForImpTStuff >= 500 && StartCheckingForVics) {//is True every 0.5S
    previousMillisCheckForImpTStuff = currentMillis;
    DEBUG("checkForimpTimeStuff()");
    checkForLOPD();
    CheckForVicimsAndDropKits();
    #if USEMATRIX==1
      check_start_tile();
      SaveMatrixToEEPROM();
    #endif
  }
}

void DEBUG_RAW(const char* msg){
  Serial.print(msg);
}

void DEBUG_INT(unsigned long int intMsg){
  Serial.println(intMsg);
}

int count_tiles(NewPing Sonar){
    //doesn't count the tile we are on
    int distance=GetDist(Sonar);
    int i=0;
    for (;distance<=30;i++){
        distance=distance-30;
    }
    DEBUG_RAW("Tiles on Sonar are: ");
    if(isThisWall(Sonar)){
        DEBUG_INT(0);
        return 0;
    }
    if (distance<7){
        DEBUG_INT(i);
        return i;
    }
    DEBUG_INT(i+1);
    return i+1;
}

void adjust_orient(int pos){
    //pos=1 right   
    DEBUG_RAW("Prev. orientation was ");
    DEBUG_INT(orientation);
    if (orientation==0 && pos==1){
        orientation=1; 
    }
    if (orientation==0 && pos==0){
        orientation=2;
    }
    if(orientation==1 && pos==1){
        orientation=2;
    }
    if(orientation==1 && pos==0){
        orientation=0;
    }

    if(orientation==2 && pos==0){
        orientation=3;
    }
    if(orientation==2 && pos==1){
        orientation=1;
    }

    if(orientation==3 && pos==0){
        orientation=2;
    }
    if(orientation==3 && pos==1){
        orientation=0;
    }
    DEBUG_RAW("CURRENT orientation is: ");
    DEBUG_INT(orientation);
}

void append_value(int ind1,int ind2,int val){
    if (grid_matrix[ind1][ind2]==4 && grid_matrix[ind1][ind2]==3 && grid_matrix[ind1][ind2]==2){ //don't overwrite trap tiles,visited tiles,victim tiles
        return;
    }
    if(grid_matrix[ind1][ind2]==0){
      return; //fix ME fucker,don't look at walls and overwrite them from the side
    }
    grid_matrix[ind1][ind2]=val;
}

void SaveMatrixToEEPROM()
{
   int address=0;
   DEBUG("QuickSaving....");
   for (int i = 0; i < X_COLS; i++) {
       for (int j = 0; j < Y_COLS; j++) {
          EEPROM.update(address,grid_matrix[i][j]);
          address+=2;
       }
   }
}

void LoadFromEEPROM(){
   int address=0;
   DEBUG("Restoring....");
   for (int i = 0; i < X_COLS; i++)  {
       for (int j = 0; j < Y_COLS; j++) {
          grid_matrix[i][j]=EEPROM.read(address);
          address+=2;
       }
   }
}
