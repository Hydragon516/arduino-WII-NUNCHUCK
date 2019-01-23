/**
 * \file arduino_WII_NUNCHUCK.ino
 * \author Hydragon516 <hydragon516@gmail.com>
 * \date 9 January 2019
 *
 * \brief Using wii nunchuck with arduino.
 *
 * \section License
 * The author has placed this work in the Public Domain, thereby relinquishing
 * all copyrights. Everyone is free to use, modify, republish, sell or give away
 * this work without prior consent from anybody.
 */
 
#include <Wire.h>
#define ZERO_AX 530  
#define ZERO_AY 530
#define ZERO_AZ 530
#define WII_NUNCHUCK_I2C_ADDRESS 0x52

int counter;
uint8_t data[6];

void setup(){ 
  Serial.begin(9600);
 
  Wire.begin();
  Wire.beginTransmission(WII_NUNCHUCK_I2C_ADDRESS);
  Wire.write(0xFB);
  Wire.write(0x00);
  Wire.endTransmission();
//You may need this code
/*Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
  Wire.write(0xF0);
  Wire.write(0x55);
  Wire.endTransmission();*/
} 

void loop(){ 
  
    Wire.requestFrom(WII_NUNCHUCK_I2C_ADDRESS, 6);
    counter = 0;
   
    while(Wire.available()){
      data[counter++] = Wire.read();
    }
    
    Wire.beginTransmission(WII_NUNCHUCK_I2C_ADDRESS);
    Wire.write(0x00);
    Wire.endTransmission();
    
    if(counter >= 5){
      int SX = data[0];
      int SY = data[1];
      double AX = ((data[2] << 2) + ((data[5] >> 2) & 0x03) - ZERO_AX);
      double AY = ((data[3] << 2) + ((data[5] >> 4) & 0x03) - ZERO_AY);
      double AZ = ((data[4] << 2) + ((data[5] >> 6) & 0x03) - ZERO_AZ);
      int BC =(data[5] >> 1) & 0x01;
      int BZ = data[5] & 0x01;
 
      Serial.print(BC);
      Serial.print("   ");
      Serial.print(BZ);
      Serial.print("   ");
      Serial.print(SX);
      Serial.print("   ");
      Serial.print(SY);
      Serial.print("   ");
      Serial.print(AX);
      Serial.print("   ");
      Serial.print(AY);
      Serial.print("   ");
      Serial.print(AZ);
      Serial.println("   ");
  
      delay(20);
    }
}
