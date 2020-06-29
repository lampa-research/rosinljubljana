/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2012 Jeff Rowberg
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/
#ifndef IMU_H
#define IMU_H

#include "Arduino.h"
#include "Pinout.h"

#include <Wire.h>


/**
 * @brief IMU class.
 * 
 */
class Imu
{
public:
    Imu();

    void Calibrrate(); // offsets are saved to the imu

    void getMotion6(float* ax_ms2, float* ay_ms2, float* az_ms2, float* gx_rads, float* gy_rads, float* gz_rads);

    void getMotion6Raw(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
    void getAccelerationRaw(int16_t* x, int16_t* y, int16_t* z);
    int16_t getAccelerationXRaw();
    int16_t getAccelerationYRaw();
    int16_t getAccelerationZRaw();

    float getTemperature();

    void getRotationRaw(int16_t* x, int16_t* y, int16_t* z);
    int16_t getRotationXRaw();
    int16_t getRotationYRaw();
    int16_t getRotationZRaw();

private: 
    char LBRACKET = '[';
    char RBRACKET = ']';
    char COMMA    = ',';
    char BLANK    = ' ';
    char PERIOD   = '.';

    int iAx = 0;
    int iAy = 1;
    int iAz = 2;
    int iGx = 3;
    int iGy = 4;
    int iGz = 5;

    int usDelay = 3150;   // empirical, to hold sampling to 200 Hz
    int NFast =  1000;    // the bigger, the better (but slower)
    int NSlow = 10000;    // ..
    int LinesBetweenHeaders = 5;
    int LowValue[6];
    int HighValue[6];
    int Smoothed[6];
    int LowOffset[6];
    int HighOffset[6];
    int Target[6];
    int LinesOut;
    int N;

    void _SetOffsets(int TheOffsets[6]);
    void _PullBracketsIn();
    void _PullBracketsOut();
    void _ShowProgress();
    void _SetAveraging(int NewN);
    void _GetSmoothed();
    void _ForceHeader();

    //
    //      MPU6050 lib
    //
    uint8_t devAddr = 0x68;
    uint8_t buffer[14];
    void _initialize();
    void _setClockSource(uint8_t source);
    void _setFullScaleGyroRange(uint8_t range);
    void _setFullScaleAccelRange(uint8_t range);
    void _setSleepEnabled(bool enabled);
    bool _testConnection();
    uint8_t _getDeviceID();

    int16_t _getXAccelOffset();
    void _setXAccelOffset(int16_t offset);
    int16_t _getYAccelOffset();
    void _setYAccelOffset(int16_t offset);
    int16_t _getZAccelOffset();
    void _setZAccelOffset(int16_t offset);
    int16_t _getXGyroOffset();
    void _setXGyroOffset(int16_t offset);
    int16_t _getYGyroOffset();
    void _setYGyroOffset(int16_t offset);
    int16_t _getZGyroOffset();
    void _setZGyroOffset(int16_t offset);

    void _CalibrateGyro(uint8_t Loops = 15); // Fine tune after setting offsets with less Loops.
    void _CalibrateAccel(uint8_t Loops = 15);// Fine tune after setting offsets with less Loops.
    void _PID(uint8_t ReadAddress, float kP,float kI, uint8_t Loops);  // Does the math
    void _PrintActiveOffsets(); // See the results of the Calibration
    void _resetFIFO();
    void _resetDMP();

    // 
    //      I2Cdev lib
    //
    int8_t _readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data, uint16_t timeout=1000);
    int8_t _readBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t *data, uint16_t timeout=1000);
    int8_t _readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data, uint16_t timeout=1000);
    int8_t _readBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data, uint16_t timeout=1000);
    int8_t _readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout=1000);
    int8_t _readWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data, uint16_t timeout=1000);
    int8_t _readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout=1000);
    int8_t _readWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data, uint16_t timeout=1000);

    bool _writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
    bool _writeBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t data);
    bool _writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
    bool _writeBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data);
    bool _writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
    bool _writeWord(uint8_t devAddr, uint8_t regAddr, uint16_t data);
    bool _writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);
    bool _writeWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data);


};
#endif