
/*
  MPU60X0.cpp - Library for interfacing with MPU60X0 chip.
  Created by Andrew James Turner, May 25, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include <MPU6050.h>
#include <Wire.h> 


MPU60X0::MPU6050(void)
{
	Wire.begin();

	wakeUp();
	
	_accelRange = getData(ACCEL_CONFIG);
	_accelRange = _accelRange & 0b00011000;

	_gyroRange = getData(GYRO_CONFIG);
	_gyroRange = _gyroRange & 0b00011000;
}


int MPU6050::wakeUp(void){
  
	uint8_t sleepBit;
	const uint8_t SLEEP = 0;
  
	// set sleep bit to zero
	Wire.beginTransmission(device_address);
	Wire.write(PWR_MGMT_1);
	Wire.write(&SLEEP, 1);
	Wire.endTransmission(true);

	// get the sleep bit
	Wire.requestFrom(device_address, 1, true);
	sleepBit = Wire.read();
 
	// check to see if woke up
	if(sleepBit == 0){
		return 1;
	}
	else{
		return 0;
	} 
}


/*
  fetches one byte of data from the given register
*/
uint8_t MPU6050::getData(int reg){
  
  uint8_t data;
   
  Wire.beginTransmission(device_address);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom(device_address, 1, true);
   
  data =  Wire.read();
   
  return data;
}


float MPU6050::getAccelX(void){
  
	uint8_t lowerByte;
	uint8_t upperByte; 
	int16_t accel;
	  
	lowerByte = getData(ACCEL_XOUT_L);
	upperByte = getData(ACCEL_XOUT_H);

	accel = (int16_t)upperByte;
	accel <<= 8;
	accel |= lowerByte;

	if(_accelRange == 0)
		return (float)accel / 16384;
	else if(_accelRange == 1)
		return (float)accel / 8192;
	else if(_accelRange == 2)
		return (float)accel / 4096;
	else
		return (float)accel / 2048;
}

float MPU6050::getAccelY(void){
  
	uint8_t lowerByte;
	uint8_t upperByte; 
	int16_t accel;

	lowerByte = getData(ACCEL_YOUT_L);
	upperByte = getData(ACCEL_YOUT_H);

	accel = (int16_t)upperByte;
	accel <<= 8;
	accel |= lowerByte;

	if(_accelRange == 0)
		return (float)accel / 16384;
	if(_accelRange == 1)
		return (float)accel / 8192;
	if(_accelRange == 2)
		return (float)accel / 4096;
	else
		return (float)accel / 2048;
}


float MPU6050::getAccelZ(void){
  
	uint8_t lowerByte;
	uint8_t upperByte; 
	int16_t accel;

	lowerByte = getData(ACCEL_ZOUT_L);
	upperByte = getData(ACCEL_ZOUT_H);

	accel = (int16_t)upperByte;
	accel <<= 8;
	accel |= lowerByte;

	if(_accelRange == 0)
		return (float)accel / 16384;
	if(_accelRange == 1)
		return (float)accel / 8192;
	if(_accelRange == 2)
		return (float)accel / 4096;
	else
		return (float)accel / 2048;
}

float MPU6050::getGyroX(void){
  
	uint8_t lowerByte;
	uint8_t upperByte; 
	int16_t gyro;

	lowerByte = getData(GYRO_XOUT_L);
	upperByte = getData(GYRO_XOUT_H);

	gyro = (int16_t)upperByte;
	gyro <<= 8;
	gyro |= lowerByte;
  
	if(_gyroRange == 0)
		return (float)gyro / 131;
	if(_gyroRange == 1)
		return (float)gyro / 65.5;
	if(_gyroRange == 2)
		return (float)gyro / 32.8;
	else
		return (float)gyro / 16.4;
}


float MPU6050::getGyroY(void){
  
	uint8_t lowerByte;
	uint8_t upperByte; 
	int16_t gyro;

	lowerByte = getData(GYRO_YOUT_L);
	upperByte = getData(GYRO_YOUT_H);

	gyro = (int16_t)upperByte;
	gyro <<= 8;
	gyro |= lowerByte;
  
	if(_gyroRange == 0)
		return (float)gyro / 131;
	if(_gyroRange == 1)
		return (float)gyro / 65.5;
	if(_gyroRange == 2)
		return (float)gyro / 32.8;
	else
		return (float)gyro / 16.4;
}

float MPU6050::getGyroZ(void){
  
	uint8_t lowerByte;
	uint8_t upperByte; 
	int16_t gyro;

	lowerByte = getData(GYRO_ZOUT_L);
	upperByte = getData(GYRO_ZOUT_H);

	gyro = (int16_t)upperByte;
	gyro <<= 8;
	gyro |= lowerByte;
  
	if(_gyroRange == 0)
		return (float)gyro / 131;
	if(_gyroRange == 1)
		return (float)gyro / 65.5;
	if(_gyroRange == 2)
		return (float)gyro / 32.8;
	else
		return (float)gyro / 16.4;
}


float MPU6050::getTemp(void){
  
  uint8_t lowerByte;
  uint8_t upperByte;
  int16_t temp;
    
  lowerByte = getData(TEMP_OUT_L);
  upperByte = getData(TEMP_OUT_H);

  temp = (int16_t)upperByte;
  temp <<= 8;
  temp |= lowerByte;
  
  return ((float)temp/340) + 36.53;
}


void MPU6050::setAccelRange2G(void){
  
	uint8_t range = 0b00000000;
  
	setData(ACCEL_CONFIG, range);
  
	_accelRange = getData(ACCEL_CONFIG);
	_accelRange = _accelRange & 0b00011000;
}

void MPU6050::setAccelRange4G(void){
  
	uint8_t range = 0b00001000;
  
	setData(ACCEL_CONFIG, range);
  
	_accelRange = getData(ACCEL_CONFIG);
	_accelRange = _accelRange & 0b00011000;
}

void MPU6050::setAccelRange8G(void){
  
	uint8_t range = 0b00010000;
  
	setData(ACCEL_CONFIG, range);
  
	_accelRange = getData(ACCEL_CONFIG);
	_accelRange = _accelRange & 0b00011000;
}



void MPU6050::setAccelRange16G(void){
  
	uint8_t range = 0b00011000;
  
	setData(ACCEL_CONFIG, range);
  
	_accelRange = getData(ACCEL_CONFIG);
	_accelRange = _accelRange & 0b00011000;
}


void MPU6050::setGyroRange250DegPerSec(void){
  
	uint8_t range = 0b00000000;
  
	setData(ACCEL_CONFIG, range);
  
	_gyroRange = getData(GYRO_CONFIG);
	_gyroRange = _gyroRange & 0b00011000;
}

void MPU6050::setGyroRange500DegPerSec(void){
  
	uint8_t range = 0b00001000;
  
	setData(ACCEL_CONFIG, range);
  
	_gyroRange = getData(GYRO_CONFIG);
	_gyroRange = _gyroRange & 0b00011000;
}


void MPU6050::setGyroRange1000DegPerSec(void){
  
	uint8_t data = 0b00010000;
  
	setData(ACCEL_CONFIG, data);
  
	_gyroRange = getData(GYRO_CONFIG);
	_gyroRange = _gyroRange & 0b00011000;
}


void MPU6050::setGyroRange2000DegPerSec(void){
  
	uint8_t range = 0b00011000;
  
	setData(ACCEL_CONFIG, range);
  
	_gyroRange = getData(GYRO_CONFIG);
	_gyroRange = _gyroRange & 0b00011000;
}


/*
  fetches one byte of data from the given register
*/
void MPU6050::setData(int reg, const uint8_t data){
  
  Wire.beginTransmission(device_address);
  Wire.write(reg);
  Wire.write(&data, 1);
  Wire.endTransmission(true);
}




