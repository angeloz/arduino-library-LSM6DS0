#include <LSM6DS0.h>


#define address LSM6DS0_XG_MEMS_ADDRESS


void LSM6DS0::init()
{
	/* Conversion mode selection */
	writeReg(LSM6DS0_XG_CTRL_REG1_G, uint8_t(0x78));
	/* Output data rate selection */
	writeReg(LSM6DS0_XG_CTRL_REG4,uint8_t(0x38));
	writeReg(LSM6DS0_XG_CTRL_REG6_XL,uint8_t(0x60));
	writeReg(LSM6DS0_XG_CTRL_REG5_XL,uint8_t(0x38));
}

int16_t LSM6DS0::gyro_getAxesXRaw(void)
{
	return readReg(LSM6DS0_XG_OUT_X_L_G | (1 << 7),(byte)2);
}

int16_t LSM6DS0::gyro_getAxesYRaw(void)
{
	return readReg(LSM6DS0_XG_OUT_Y_L_G | (1 << 7),(byte)2);
}

int16_t LSM6DS0::gyro_getAxesZRaw(void)
{
	return readReg(LSM6DS0_XG_OUT_Z_L_G | (1 << 7),(byte)2);
}

int16_t LSM6DS0::gyro_getAxesX(void)
{
	int16_t mx = readReg(LSM6DS0_XG_OUT_X_L_G | (1 << 7),(byte)2);
	float sensitivity = getGyroScale();
	return mx * sensitivity;
}

int16_t LSM6DS0::gyro_getAxesY(void)
{
	int16_t my = readReg(LSM6DS0_XG_OUT_Y_L_G | (1 << 7),(byte)2);
	float sensitivity = getGyroScale();
	return my * sensitivity;
}

int16_t LSM6DS0::gyro_getAxesZ(void)
{
  	int16_t mz = readReg(LSM6DS0_XG_OUT_Z_L_G | (1 << 7),(byte)2);
	float sensitivity = getGyroScale();
	return mz * sensitivity;
}

int16_t LSM6DS0::acc_getAxesXRaw(void)
{
	return readReg(LSM6DS0_XG_OUT_X_L_XL | (1 << 7),(byte)2);
}

int16_t LSM6DS0::acc_getAxesYRaw(void)
{
	return readReg(LSM6DS0_XG_OUT_Y_L_XL | (1 << 7),(byte)2);
}

int16_t LSM6DS0::acc_getAxesZRaw(void)
{
	return readReg(LSM6DS0_XG_OUT_Z_L_XL | (1 << 7),(byte)2);
}

int16_t LSM6DS0::acc_getAxesX(void)
{
	int16_t mx = readReg(LSM6DS0_XG_OUT_X_L_XL | (1 << 7),(byte)2);
	float sensitivity = getAccScale();
	return mx * sensitivity;
}

int16_t LSM6DS0::acc_getAxesY(void)
{
	int16_t my = readReg(LSM6DS0_XG_OUT_Y_L_XL | (1 << 7),(byte)2);
	float sensitivity = getAccScale();
	return my * sensitivity;
}

int16_t LSM6DS0::acc_getAxesZ(void)
{
  	int16_t mz = readReg(LSM6DS0_XG_OUT_Z_L_XL | (1 << 7),(byte)2);
	float sensitivity = getAccScale();
	return mz * sensitivity;
}

float LSM6DS0::getGyroScale(void){

  	float sensitivity=0;
	Wire.beginTransmission(address);
	Wire.write(LSM6DS0_XG_CTRL_REG1_G);
	Wire.endTransmission();
	Wire.requestFrom(address, (byte)1);
	uint8_t scale = Wire.read();
	Wire.endTransmission();
    Serial.println(scale);
    switch(scale)
      {
		case LSM6DS0_G_FS_245:
			sensitivity = 8.75;
			break;
		case LSM6DS0_G_FS_500:
			sensitivity = 17.50;
			break;
		case LSM6DS0_G_FS_2000:
			sensitivity = 70;
			break;
     }
	 return sensitivity;
}

float LSM6DS0::getAccScale(void){

  	float sensitivity=0;
	Wire.beginTransmission(address);
	Wire.write(LSM6DS0_XG_CTRL_REG6_XL);
	Wire.endTransmission();
	Wire.requestFrom(address, (byte)1);
	uint8_t acc_scale = Wire.read();
	Wire.endTransmission();
    Serial.println(acc_scale);
    switch(acc_scale)
      {
		case LSM6DS0_XL_FS_2G:
			sensitivity = 0.061;
			break;
		case LSM6DS0_XL_FS_4G:
			sensitivity = 0.122;
			break;
		case LSM6DS0_XL_FS_8G:
			sensitivity = 0.244;
			break;
     }
	 return sensitivity;
}
// writes register
void LSM6DS0::writeReg(int reg, byte value)
{
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

int16_t LSM6DS0::readReg(int reg, byte num)
{
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(address, num);
  while (Wire.available() < num);
  uint8_t ml = Wire.read();
  uint8_t mh = Wire.read();
  return (int16_t)(mh << 8 | ml);
}
