#include <MPU60X0.h>
#include <Wire.h>

MPU60X0 mpu60X0;

void setup()
{   
  Serial.begin(9600);
}


void loop()
{
   Serial.println(mpu60X0.getAccelX());
}
