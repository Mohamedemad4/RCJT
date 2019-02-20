int getCurrentOrintation(){
    return compass.readHeading();
}

int getZaxis(){
  int16_t x,y,z,t;
  compass.readRaw(&x,&y,&z,&t);
  return z;
}

float GetIrHeatright(){
  float temp;
  uint16_t ret;
  Wire3.beginTransmission(0x5A); //device Slave address
  Wire3.write(0x07);             // request object temp in C
  Wire3.endTransmission(false);     // stop transmitting
  Wire3.requestFrom(0x5A, (uint8_t)3);// send data n-bytes read
  ret = Wire3.read(); // receive DATA
  ret |= Wire3.read() << 8; // left shift data by 8 Bits (taken from Adafuit MLX lib,IDK)
  temp=ret;
  temp *= .02;
  temp  -= 273.15;
  return temp;
}
float GetIrHeatleft(){
  float temp;
  uint16_t ret;
  Wire2.beginTransmission(0x5A); 
  Wire2.write(byte(0x07));               
  Wire2.endTransmission(false);     
  Wire2.requestFrom(0x5A, (uint8_t)3); 
  ret = Wire2.read(); 
  ret |= Wire2.read() << 8;
  temp=ret;
  temp *= .02;
  temp  -= 273.15;
  return temp;
}


void checkForIns(){
    if (digitalRead(22)==1 && digitalRead(23)==1){
    }
    if (digitalRead(22)==1 &&digitalRead(23)==0){
        Serial.println("Right");
        cpos="r";
        cam.write(160);
    }
    if (digitalRead(22)==0 && digitalRead(23)==1){
        Serial.println("left");   
        cpos="l";
        cam.write(20);
    }
    if (digitalRead(22)==0 && digitalRead(23)==0){
        Serial.println("Forward");
        cpos="f";
        cam.write(90);
    }
}

int isNotWithinRange(int range,int l1,int l2){
  if ((fabs(l1-l2)>range)){
    return 1;
  }
  return 0;

}

int GetDist(NewPing sonarN){
    return sonarN.ping_cm();  
}
 
void sensorDebug(){
         Serial.print("Distance on A0: ");
         Serial.println(GetDist(sonar0));
         Serial.print("Distance on A1: ");
         Serial.println(GetDist(sonar1));
         Serial.print("Distance on A2: ");
         Serial.println(GetDist(sonar2));
         
         Serial.print("Heat on A9A8 (left): ");
         Serial.println(GetIrHeatleft());
         Serial.print("Heat on D21D20 (right): ");
         Serial.println(GetIrHeatright());

         Serial.print("IR Value: ");
         Serial.println(analogRead(A3));
}
