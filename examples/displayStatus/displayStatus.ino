#include <MPU6050.h>
#include <Wire.h>

MPU6050 mpu6050;

void setup()
{   
  Serial.begin(9600);
}


void loop()
{
   Serial.println(mpu6050.getAccelX());
}
