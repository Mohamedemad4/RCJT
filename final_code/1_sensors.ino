float GetIrHeatright(int w=0x07){
  float temp;
  uint16_t ret;
  Wire.beginTransmission(0x5A); //device Slave address
  Wire.write(byte(w));             // request object temp in C
  Wire.endTransmission(false);     // stop transmitting
  Wire.requestFrom(0x5A, 3);// send data n-bytes read //(uint8_t)
  ret = Wire.read(); // receive DATA
  ret |= Wire.read() << 8; // left shift data by 8 Bits (taken from Adafuit MLX lib,IDK)
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

float getCompHeading(){
   if (mag.testConnection()==false){
     return 370;
   }
   /* To calculate heading in degrees. 0 degree indicates North */
   int16_t mx, my, mz;
   mag.getHeading(&mx, &my, &mz);
   float heading = atan2(my, mx);   
   if(heading < 0)
     heading += 2 * M_PI;
   return heading * 180/M_PI;
}

float GetAlt(){
  if (bmp==false){
    return 0;
  }
  float temp,p,a;
  bmp085Measure(&temp,&p,&a);
  return a;
}

int GetDist(NewPing sonarN){
    return sonarN.ping_cm();  
}

int16_t GetAccXpY(){
  if (accc.testConnection()==false){
    return 0;
  }
  return accc.getAccelerationX();//+accc.getAccelerationY();
} 
void sensorDebug(){
         Serial.print("Distance on A0: ");
         Serial.println(GetDist(left_us));
         Serial.print("Distance on A1: ");
         Serial.println(GetDist(center_us));
         Serial.print("Distance on A2: ");
         Serial.println(GetDist(right_us));
         
         Serial.print("Heat on A4A5 (left): ");
         Serial.println(GetIrHeatleft());
         Serial.print("Heat on D21D20 (right): ");
         Serial.println(GetIrHeatright());

          
         Serial.print("Color IR Value: ");
         Serial.println(digitalRead(A3));
  
         Serial.print("Compass: ");
         Serial.println(getCompHeading());
  
         Serial.print("Alt: ");
         Serial.println(GetAlt());
}
