#ifndef MPU60X0_h
#define MPU60X0_h

	#include <math.h>
	#include "Arduino.h"

	#define device_address 	0x68 

	#define ACCEL_CONFIG 	0x1C
	#define GYRO_CONFIG 	0x1B
	
	#define ACCEL_XOUT_H  	0x3B
	#define ACCEL_XOUT_L  	0x3C
	#define ACCEL_YOUT_H  	0x3D
	#define ACCEL_YOUT_L  	0x3E
	#define ACCEL_ZOUT_H  	0x3F
	#define ACCEL_ZOUT_L  	0x40

	#define TEMP_OUT_H  	0x41
	#define TEMP_OUT_L  	0x42

	#define GYRO_XOUT_H 	0x43
	#define GYRO_XOUT_L 	0x44
	#define GYRO_YOUT_H 	0x45
	#define GYRO_YOUT_L 	0x46
	#define GYRO_ZOUT_H 	0x47
	#define GYRO_ZOUT_L 	0x48

	#define PWR_MGMT_1 		0x6B 

	class MPU6050
	{
		public:
			MPU6050(void);
			void begin(void);
			float getAccelX(void);
			float getAccelY(void);
			float getAccelZ(void);
			float getGyroX(void);
			float getGyroY(void);
			float getGyroZ(void);
			float getTemp(void);

			void setAccelRange2G(void);
			void setAccelRange4G(void);
			void setAccelRange8G(void);
			void setAccelRange16G(void);

			void setGyroRange250DegPerSec(void);
			void setGyroRange500DegPerSec(void);
			void setGyroRange1000DegPerSec(void);
			void setGyroRange2000DegPerSec(void);

		private:
			int _accelRange;
			int _gyroRange;
			int wakeUp(void);
			uint8_t getData(int reg);
			void setData(int reg, const uint8_t data);
	};

#endif
