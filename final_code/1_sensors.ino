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
         DEBUG_RAW("Distance on left_us: ");
         DEBUG_INT(GetDist(left_us));
         DEBUG_RAW("Distance on center_us: ");
         DEBUG_INT(GetDist(center_us));
         DEBUG_RAW("Distance on right_us ");
         DEBUG_INT(GetDist(right_us));
         
         DEBUG_RAW("Heat on A4A5 (left): ");
         DEBUG_INT(GetIrHeatleft());
         DEBUG_RAW("Heat on D21D20 (right): ");
         DEBUG_INT(GetIrHeatright());
          
         DEBUG_RAW("Color IR Value: ");
         DEBUG_INT(digitalRead(A3));
  
         DEBUG_RAW("Compass: ");
         DEBUG_INT(getCompHeading());
  
         DEBUG_RAW("Alt: ");
         DEBUG_INT(GetAlt());
        
         DEBUG_RAW("is the Pi detected?: ");  
         DEBUG_INT(PiIsActive);

         DEBUG("");
         DEBUG_RAW("Last victim type Is: ");
         DEBUG_INT(vtype);
         DEBUG_RAW("Last victim location: ");
         DEBUG_INT(cpos);
}
