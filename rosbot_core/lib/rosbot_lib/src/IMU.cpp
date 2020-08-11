#include "IMU.h"

IMU::IMU()
{
}

void IMU::begin()
{
  writeMPU6050(MPU6050_SMPLRT_DIV, 0x00);
  writeMPU6050(MPU6050_CONFIG, 0x00);
  writeMPU6050(MPU6050_GYRO_CONFIG, 0x08);
  writeMPU6050(MPU6050_ACCEL_CONFIG, 0x00);
  writeMPU6050(MPU6050_PWR_MGMT_1, 0x01);
  update();
  angleGyroX = 0;
  angleGyroY = 0;
  angleX = getAccAngleX();
  angleY = getAccAngleY();
  preInterval = millis();
}

void IMU::writeMPU6050(byte reg, byte data)
{
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

byte IMU::readMPU6050(byte reg)
{
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(reg);
  Wire.endTransmission(true);
  Wire.requestFrom(MPU6050_ADDR, 1);
  byte data = Wire.read();
  return data;
}

void IMU::setGyroOffsets(float x, float y, float z)
{
  gyroXoffset = x;
  gyroYoffset = y;
  gyroZoffset = z;
}

void IMU::calcGyroOffsets(bool console)
{
  float x = 0, y = 0, z = 0;
  int16_t rx, ry, rz;

  if (console)
  {
    Serial.println();
    Serial.println("========================================");
    Serial.println("MPU6050 Calibration\n");
    Serial.println("Place the ROBOT on a hard surface (e.g. table top).");
    Serial.println("DO NOT MOVE the ROBOT while calibration is in progress.\n");
    Serial.println("Calibration will start in 5 seconds.\n");
    delay(5000);
    Serial.println("Calibration START\n");
    Serial.println("Calculating gyro offsets.");
  }
  for (int i = 0; i < 3000; i++)
  {
    if (console && i % 1000 == 0)
    {
      Serial.print(".");
    }
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom((int)MPU6050_ADDR, 6);

    rx = Wire.read() << 8 | Wire.read();
    ry = Wire.read() << 8 | Wire.read();
    rz = Wire.read() << 8 | Wire.read();

    x += ((float)rx) / 65.5;
    y += ((float)ry) / 65.5;
    z += ((float)rz) / 65.5;
  }
  gyroXoffset = x / 3000;
  gyroYoffset = y / 3000;
  gyroZoffset = z / 3000;

  if (console)
  {
    Serial.println();
    Serial.println("Calibration SUCCESSFUL");
    Serial.print("X : ");
    Serial.println(gyroXoffset, 9);
    Serial.print("Y : ");
    Serial.println(gyroYoffset, 9);
    Serial.print("Z : ");
    Serial.println(gyroZoffset, 9);
    Serial.println("========================================\n");
  }
}

void IMU::update()
{
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom((int)MPU6050_ADDR, 14);

  rawAccX = Wire.read() << 8 | Wire.read();
  rawAccY = Wire.read() << 8 | Wire.read();
  rawAccZ = Wire.read() << 8 | Wire.read();
  rawTemp = Wire.read() << 8 | Wire.read();
  rawGyroX = Wire.read() << 8 | Wire.read();
  rawGyroY = Wire.read() << 8 | Wire.read();
  rawGyroZ = Wire.read() << 8 | Wire.read();

  temp = (rawTemp + 12412.0) / 340.0;

  accX = ((float)rawAccX) / 16384.0;
  accY = ((float)rawAccY) / 16384.0;
  accZ = ((float)rawAccZ) / 16384.0;

  angleAccX = atan2(accY, accZ + abs(accX)) * 360 / 2.0 / PI;
  angleAccY = atan2(accX, accZ + abs(accY)) * 360 / -2.0 / PI;

  gyroX = ((float)rawGyroX) / 65.5;
  gyroY = ((float)rawGyroY) / 65.5;
  gyroZ = ((float)rawGyroZ) / 65.5;

  gyroX -= gyroXoffset;
  gyroY -= gyroYoffset;
  gyroZ -= gyroZoffset;

  interval = (millis() - preInterval) * 0.001;

  angleGyroX += gyroX * interval;
  angleGyroY += gyroY * interval;
  angleGyroZ += gyroZ * interval;

  angleX = (gyroCoef * (angleX + gyroX * interval)) + (accCoef * angleAccX);
  angleY = (gyroCoef * (angleY + gyroY * interval)) + (accCoef * angleAccY);
  angleZ = angleGyroZ;

  preInterval = millis();
}