#include <SoftwareWire.h>
#include <Wire.h>

//Left Sensor connected to A8,A9
//Right Sensor connected to Digital pins 20,21
SoftwareWire Wire2( A8, A9);// SDA,SCL

void setup()
{
  Serial.begin(9600);
  Wire.begin(); 
  Wire2.begin();
}

float GetIrHeatright(){
  float temp;
  uint16_t ret;
  Wire.beginTransmission(0x5A); //device Slave address
  Wire.write(0x07);             // request object temp in C
  Wire.endTransmission(false);     // stop transmitting
  Wire.requestFrom(0x5A, (uint8_t)3);// send data n-bytes read
  ret = Wire.read(); // receive DATA
  ret |= Wire.read() << 8; // left shift data by 8 Bits (taken from Adafuit MLX lib,IDK)
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
void loop()
{
  Serial.println(GetIrHeatleft());
  Serial.println(GetIrHeatright());
  delay(2000);

}
