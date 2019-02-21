float GetIrHeatright(int w=0x07){
  float temp;
  uint16_t ret;
  Wire3.beginTransmission(0x5A); //device Slave address
  Wire3.write(byte(w));             // request object temp in C
  Wire3.endTransmission(false);     // stop transmitting
  Wire3.requestFrom(0x5A, 3);// send data n-bytes read //(uint8_t)
  ret = Wire3.read(); // receive DATA
  ret |= Wire3.read() << 8; // left shift data by 8 Bits (taken from Adafuit MLX lib,IDK)
  temp=ret;
  temp *= .02;  
  temp  -= 273.15;
  return temp;
}
float GetIrHeatleft(int w=0x07){//Check the readme for a des.
  float temp;
  uint16_t ret;
  Wire2.beginTransmission(0x5A); 
  Wire2.write(byte(w));               
  Wire2.endTransmission(false);     
  Wire2.requestFrom(0x5A, 3); 
  ret = Wire2.read(); 
  ret |= Wire2.read() << 8;
  temp=ret;
  temp *= .02;
  temp  -= 273.15;
  return temp;
}

int getCurrentOrintation(){
    return compass.readHeading();
}

int getZaxis(){
  int16_t x,y,z,t;
  compass.readRaw(&x,&y,&z,&t);
  return z;
}

int GetDist(NewPing sonarN){
    return sonarN.ping_cm();  
}
 
void sensorDebug(){
         Serial.print("Distance on A0: ");
         Serial.println(GetDist(left_us));
         Serial.print("Distance on A1: ");
         Serial.println(GetDist(center_us));
         Serial.print("Distance on A2: ");
         Serial.println(GetDist(right_us));
         
         Serial.print("Heat on A9A8 (left): ");
         Serial.println(GetIrHeatleft());
         Serial.print("Heat on D21D20 (right): ");
         Serial.println(GetIrHeatright());

         Serial.print("IR Value: ");
         Serial.println(analogRead(A3));
}

