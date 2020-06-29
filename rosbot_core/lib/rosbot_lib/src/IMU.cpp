#include "IMU.h"

/**
 * @brief Construct a new Imu:: Imu object
 * Configures the MPU6050 IMU i2c communication.
 */
Imu::Imu() {
    Wire.begin(SDA,SCL);
    // initialize device
    Serial.println("Initializing I2C devices...");
    _initialize();
    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(_testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void Imu::getMotion6(float* ax_ms2, float* ay_ms2, float* az_ms2, float* gx_rads, float* gy_rads, float* gz_rads) {
    int16_t ax, ay, az, gx, gy, gz;
    _readBytes(devAddr, 0x3B, 14, buffer);
    ax = (((int16_t)buffer[0]) << 8) | buffer[1];
    ay = (((int16_t)buffer[2]) << 8) | buffer[3];
    az = (((int16_t)buffer[4]) << 8) | buffer[5];
    gx = (((int16_t)buffer[8]) << 8) | buffer[9];
    gy = (((int16_t)buffer[10]) << 8) | buffer[11];
    gz = (((int16_t)buffer[12]) << 8) | buffer[13];
    *ax_ms2 = (ax/16384.0)*9.81;
    *ay_ms2 = (ay/16384.0)*9.81;
    *az_ms2 = (az/16384.0)*9.81;
    *gx_rads = (gx/131.0)*PI/180.0;
    *gy_rads = (gy/131.0)*PI/180.0;
    *gz_rads = (gz/131.0)*PI/180.0;
}


//
//      IMU_Zero.ino
//
void Imu::Calibrrate() {
    _CalibrateAccel(6);
    _CalibrateGyro(6);
    Serial.println("\nat 600 Readings");
    _PrintActiveOffsets();
    Serial.println();
    _CalibrateAccel(1);
    _CalibrateGyro(1);
    Serial.println("700 Total Readings");
    _PrintActiveOffsets();
    Serial.println();
    _CalibrateAccel(1);
    _CalibrateGyro(1);
    Serial.println("800 Total Readings");
    _PrintActiveOffsets();
    Serial.println();
    _CalibrateAccel(1);
    _CalibrateGyro(1);
    Serial.println("900 Total Readings");
    _PrintActiveOffsets();
    Serial.println();    
    _CalibrateAccel(1);
    _CalibrateGyro(1);
    Serial.println("1000 Total Readings");
    _PrintActiveOffsets();
    Serial.println("\n\n Any of the above offsets will work nice \n\n Lets proof the PID tuning using another method:"); 

    for (int i = iAx; i <= iGz; i++) {
        Target[i] = 0; // must fix for ZAccel 
        HighOffset[i] = 0;
        LowOffset[i] = 0;
    }
    Target[iAz] = 16384;
    _SetAveraging(NFast);

    _PullBracketsOut();
    _PullBracketsIn();

    Serial.println("-------------- done --------------");    
}

void Imu::_SetAveraging(int NewN) {
    N = NewN;
    Serial.print("averaging ");
    Serial.print(N);
    Serial.println(" readings each time");
}

void Imu::_PullBracketsOut() {
    boolean Done = false;
    int NextLowOffset[6];
    int NextHighOffset[6];

    Serial.println("expanding:");
    _ForceHeader();
 
    while (!Done) {
        Done = true;
        _SetOffsets(LowOffset);
        _GetSmoothed();
        for (int i = iAx; i <= iGz; i++) {
            LowValue[i] = Smoothed[i];
            if (LowValue[i] >= Target[i]) {
                Done = false;
                NextLowOffset[i] = LowOffset[i] - 1000;
            }
            else {
                NextLowOffset[i] = LowOffset[i];
            }
        }      
        _SetOffsets(HighOffset);
        _GetSmoothed();
        for (int i = iAx; i <= iGz; i++) {
            HighValue[i] = Smoothed[i];
            if (HighValue[i] <= Target[i]) {
                Done = false;
                NextHighOffset[i] = HighOffset[i] + 1000;
            }
            else {
                NextHighOffset[i] = HighOffset[i];
            }
        }
        _ShowProgress();
        for (int i = iAx; i <= iGz; i++) {
            LowOffset[i] = NextLowOffset[i];   // had to wait until ShowProgress done
            HighOffset[i] = NextHighOffset[i]; // ..
        }
    }
}

void Imu::_PullBracketsIn() {
    boolean AllBracketsNarrow;
    boolean StillWorking;
    int NewOffset[6];
    
    Serial.println("\nclosing in:");
    AllBracketsNarrow = false;
    _ForceHeader();
    StillWorking = true;
    while (StillWorking) {
        StillWorking = false;
        if (AllBracketsNarrow && (N == NFast)) {
            _SetAveraging(NSlow);
        }
        else {
            AllBracketsNarrow = true;
        }
        for (int i = iAx; i <= iGz; i++) {
            if (HighOffset[i] <= (LowOffset[i]+1)) {
                NewOffset[i] = LowOffset[i];
            }
            else {
                StillWorking = true;
                NewOffset[i] = (LowOffset[i] + HighOffset[i]) / 2;
                
                if (HighOffset[i] > (LowOffset[i] + 10)) {
                    AllBracketsNarrow = false;
                }
            }
        }
        
        _SetOffsets(NewOffset);
        _GetSmoothed();
        for (int i = iAx; i <= iGz; i++) {
            if (Smoothed[i] > Target[i]) {
                HighOffset[i] = NewOffset[i];
                HighValue[i] = Smoothed[i];
            }
            else {
                LowOffset[i] = NewOffset[i];
                LowValue[i] = Smoothed[i];
            } 
        } 
        _ShowProgress();
    }
}

void Imu::_ForceHeader() { LinesOut = 99; }
    
void Imu::_GetSmoothed() {
    int16_t RawValue[6];
    int i;
    long Sums[6];
    for (i = iAx; i <= iGz; i++)
        { Sums[i] = 0; }
    //    unsigned long Start = micros();

    for (i = 1; i <= N; i++) { 
        // get sums
        getMotion6Raw(&RawValue[iAx], &RawValue[iAy], &RawValue[iAz], 
                                &RawValue[iGx], &RawValue[iGy], &RawValue[iGz]);
        if ((i % 500) == 0)
            Serial.print(PERIOD);
        delayMicroseconds(usDelay);
        for (int j = iAx; j <= iGz; j++)
            Sums[j] = Sums[j] + RawValue[j];
        } // get sums
    //    unsigned long usForN = micros() - Start;
    //    Serial.print(" reading at ");
    //    Serial.print(1000000/((usForN+N/2)/N));
    //    Serial.println(" Hz");
    for (i = iAx; i <= iGz; i++)
        { Smoothed[i] = (Sums[i] + N/2) / N ; }
} // GetSmoothed

void Imu::_SetOffsets(int TheOffsets[6]) {
    _setXAccelOffset(TheOffsets [iAx]);
    _setYAccelOffset(TheOffsets [iAy]);
    _setZAccelOffset(TheOffsets [iAz]);
    _setXGyroOffset (TheOffsets [iGx]);
    _setYGyroOffset (TheOffsets [iGy]);
    _setZGyroOffset (TheOffsets [iGz]);
}

void Imu::_ShowProgress() {
    if (LinesOut >= LinesBetweenHeaders) {
        Serial.println("\tXAccel\t\t\tYAccel\t\t\t\tZAccel\t\t\tXGyro\t\t\tYGyro\t\t\tZGyro");
        LinesOut = 0;
    }
    Serial.print(BLANK);
    for (int i = iAx; i <= iGz; i++) {
        Serial.print(LBRACKET);
        Serial.print(LowOffset[i]),
        Serial.print(COMMA);
        Serial.print(HighOffset[i]);
        Serial.print("] --> [");
        Serial.print(LowValue[i]);
        Serial.print(COMMA);
        Serial.print(HighValue[i]);
        if (i == iGz) {
            Serial.println(RBRACKET);
        }
        else {
            Serial.print("]\t");
        }
    }
    LinesOut++;
}


//
//      MPU6050 lib
//
void Imu::_initialize() {
    _setClockSource(0x01);
    _setFullScaleGyroRange(0x00);
    _setFullScaleAccelRange(0x00);
    _setSleepEnabled(false);
}
void Imu::_setClockSource(uint8_t source) {
    _writeBits(devAddr, 0x6B, 2, 3, source); // ( ,MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, )
}
void Imu::_setFullScaleGyroRange(uint8_t range) {
    _writeBits(devAddr, 0x1B, 4, 2, range); // ( , MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, )
}
void Imu::_setFullScaleAccelRange(uint8_t range) {
    _writeBits(devAddr, 0x1C, 4, 2, range); // ( , MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, )
}
void Imu::_setSleepEnabled(bool enabled) {
    _writeBit(devAddr, 0x6B, 6, enabled); // ( , MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, )
}
bool Imu::_testConnection() {
    return _getDeviceID() == 0x34;
}
uint8_t Imu::_getDeviceID() {
    _readBits(devAddr, 0x75, 6, 6, buffer); // ( , MPU6050_RA_WHO_AM_I, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, )
    return buffer[0];
}

int16_t Imu::_getXAccelOffset() {
	uint8_t SaveAddress = ((_getDeviceID() < 0x38 )? 0x06:0x77); // MPU6050,MPU9150 Vs MPU6500,MPU9250
	_readBytes(devAddr, SaveAddress, 2, buffer);
	return (((int16_t)buffer[0]) << 8) | buffer[1];
}
void Imu::_setXAccelOffset(int16_t offset) {
	uint8_t SaveAddress = ((_getDeviceID() < 0x38 )? 0x06:0x77); // MPU6050,MPU9150 Vs MPU6500,MPU9250
	_writeWord(devAddr, SaveAddress, offset);
}
int16_t Imu::_getYAccelOffset() {
	uint8_t SaveAddress = ((_getDeviceID() < 0x38 )? 0x08:0x7A); // MPU6050,MPU9150 Vs MPU6500,MPU9250
	_readBytes(devAddr, SaveAddress, 2, buffer);
	return (((int16_t)buffer[0]) << 8) | buffer[1];
}
void Imu::_setYAccelOffset(int16_t offset) {
	uint8_t SaveAddress = ((_getDeviceID() < 0x38 )? 0x08:0x7A); // MPU6050,MPU9150 Vs MPU6500,MPU9250
	_writeWord(devAddr, SaveAddress, offset);
}
int16_t Imu::_getZAccelOffset() {
	uint8_t SaveAddress = ((_getDeviceID() < 0x38 )? 0x0A:0x7D); // MPU6050,MPU9150 Vs MPU6500,MPU9250
	_readBytes(devAddr, SaveAddress, 2, buffer);
	return (((int16_t)buffer[0]) << 8) | buffer[1];
}
void Imu::_setZAccelOffset(int16_t offset) {
	uint8_t SaveAddress = ((_getDeviceID() < 0x38 )? 0x0A:0x7D); // MPU6050,MPU9150 Vs MPU6500,MPU9250
	_writeWord(devAddr, SaveAddress, offset);
}
int16_t Imu::_getXGyroOffset() {
    _readBytes(devAddr, 0x13, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
void Imu::_setXGyroOffset(int16_t offset) {
    _writeWord(devAddr, 0x13, offset);
}
int16_t Imu::_getYGyroOffset() {
    _readBytes(devAddr, 0x15, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
void Imu::_setYGyroOffset(int16_t offset) {
    _writeWord(devAddr, 0x15, offset);
}
int16_t Imu::_getZGyroOffset() {
    _readBytes(devAddr, 0x17, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
void Imu::_setZGyroOffset(int16_t offset) {
    _writeWord(devAddr, 0x17, offset);
}

/** Get raw 6-axis motion sensor readings (accel/gyro).
 * Retrieves all currently available motion sensor values.
 * @param ax 16-bit signed integer container for accelerometer X-axis value
 * @param ay 16-bit signed integer container for accelerometer Y-axis value
 * @param az 16-bit signed integer container for accelerometer Z-axis value
 * @param gx 16-bit signed integer container for gyroscope X-axis value
 * @param gy 16-bit signed integer container for gyroscope Y-axis value
 * @param gz 16-bit signed integer container for gyroscope Z-axis value
 * @see getAcceleration()
 * @see getRotation()
 * @see MPU6050_RA_ACCEL_XOUT_H
 */
void Imu::getMotion6Raw(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz) {
    _readBytes(devAddr, 0x3B, 14, buffer);
    *ax = (((int16_t)buffer[0]) << 8) | buffer[1];
    *ay = (((int16_t)buffer[2]) << 8) | buffer[3];
    *az = (((int16_t)buffer[4]) << 8) | buffer[5];
    *gx = (((int16_t)buffer[8]) << 8) | buffer[9];
    *gy = (((int16_t)buffer[10]) << 8) | buffer[11];
    *gz = (((int16_t)buffer[12]) << 8) | buffer[13];
}
/** Get 3-axis accelerometer readings.
 * These registers store the most recent accelerometer measurements.
 * Accelerometer measurements are written to these registers at the Sample Rate
 * as defined in Register 25.
 *
 * The accelerometer measurement registers, along with the temperature
 * measurement registers, gyroscope measurement registers, and external sensor
 * data registers, are composed of two sets of registers: an internal register
 * set and a user-facing read register set.
 *
 * The data within the accelerometer sensors' internal register set is always
 * updated at the Sample Rate. Meanwhile, the user-facing read register set
 * duplicates the internal register set's data values whenever the serial
 * interface is idle. This guarantees that a burst read of sensor registers will
 * read measurements from the same sampling instant. Note that if burst reads
 * are not used, the user is responsible for ensuring a set of single byte reads
 * correspond to a single sampling instant by checking the Data Ready interrupt.
 *
 * Each 16-bit accelerometer measurement has a full scale defined in ACCEL_FS
 * (Register 28). For each full scale setting, the accelerometers' sensitivity
 * per LSB in ACCEL_xOUT is shown in the table below:
 *
 * <pre>
 * AFS_SEL | Full Scale Range | LSB Sensitivity
 * --------+------------------+----------------
 * 0       | +/- 2g           | 8192 LSB/mg
 * 1       | +/- 4g           | 4096 LSB/mg
 * 2       | +/- 8g           | 2048 LSB/mg
 * 3       | +/- 16g          | 1024 LSB/mg
 * </pre>
 *
 * @param x 16-bit signed integer container for X-axis acceleration
 * @param y 16-bit signed integer container for Y-axis acceleration
 * @param z 16-bit signed integer container for Z-axis acceleration
 * @see MPU6050_RA_GYRO_XOUT_H
 */
void Imu::getAccelerationRaw(int16_t* x, int16_t* y, int16_t* z) {
    _readBytes(devAddr, 0x3B, 6, buffer);
    *x = (((int16_t)buffer[0]) << 8) | buffer[1];
    *y = (((int16_t)buffer[2]) << 8) | buffer[3];
    *z = (((int16_t)buffer[4]) << 8) | buffer[5];
}
/** Get X-axis accelerometer reading.
 * @return X-axis acceleration measurement in 16-bit 2's complement format
 * @see getMotion6()
 * @see MPU6050_RA_ACCEL_XOUT_H
 */
int16_t Imu::getAccelerationXRaw() {
    _readBytes(devAddr, 0x3B, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
/** Get Y-axis accelerometer reading.
 * @return Y-axis acceleration measurement in 16-bit 2's complement format
 * @see getMotion6()
 * @see MPU6050_RA_ACCEL_YOUT_H
 */
int16_t Imu::getAccelerationYRaw() {
    _readBytes(devAddr, 0x3D, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
/** Get Z-axis accelerometer reading.
 * @return Z-axis acceleration measurement in 16-bit 2's complement format
 * @see getMotion6()
 * @see MPU6050_RA_ACCEL_ZOUT_H
 */
int16_t Imu::getAccelerationZRaw() {
    _readBytes(devAddr, 0x3F, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}

/** Get current internal temperature.
 * @return Temperature reading in degC
 * @see MPU6050_RA_TEMP_OUT_H
 */
float Imu::getTemperature() {
    _readBytes(devAddr, 0x41, 2, buffer);
    int16_t temp = (((int16_t)buffer[0]) << 8) | buffer[1];
    return (temp/340.0) +36.53;
}

/** Get 3-axis gyroscope readings.
 * These gyroscope measurement registers, along with the accelerometer
 * measurement registers, temperature measurement registers, and external sensor
 * data registers, are composed of two sets of registers: an internal register
 * set and a user-facing read register set.
 * The data within the gyroscope sensors' internal register set is always
 * updated at the Sample Rate. Meanwhile, the user-facing read register set
 * duplicates the internal register set's data values whenever the serial
 * interface is idle. This guarantees that a burst read of sensor registers will
 * read measurements from the same sampling instant. Note that if burst reads
 * are not used, the user is responsible for ensuring a set of single byte reads
 * correspond to a single sampling instant by checking the Data Ready interrupt.
 *
 * Each 16-bit gyroscope measurement has a full scale defined in FS_SEL
 * (Register 27). For each full scale setting, the gyroscopes' sensitivity per
 * LSB in GYRO_xOUT is shown in the table below:
 *
 * <pre>
 * FS_SEL | Full Scale Range   | LSB Sensitivity
 * -------+--------------------+----------------
 * 0      | +/- 250 degrees/s  | 131 LSB/deg/s
 * 1      | +/- 500 degrees/s  | 65.5 LSB/deg/s
 * 2      | +/- 1000 degrees/s | 32.8 LSB/deg/s
 * 3      | +/- 2000 degrees/s | 16.4 LSB/deg/s
 * </pre>
 *
 * @param x 16-bit signed integer container for X-axis rotation
 * @param y 16-bit signed integer container for Y-axis rotation
 * @param z 16-bit signed integer container for Z-axis rotation
 * @see getMotion6()
 * @see MPU6050_RA_GYRO_XOUT_H
 */
void Imu::getRotationRaw(int16_t* x, int16_t* y, int16_t* z) {
    _readBytes(devAddr, 0x43, 6, buffer);
    *x = (((int16_t)buffer[0]) << 8) | buffer[1];
    *y = (((int16_t)buffer[2]) << 8) | buffer[3];
    *z = (((int16_t)buffer[4]) << 8) | buffer[5];
}
/** Get X-axis gyroscope reading.
 * @return X-axis rotation measurement in 16-bit 2's complement format
 * @see getMotion6()
 * @see MPU6050_RA_GYRO_XOUT_H
 */
int16_t Imu::getRotationXRaw() {
    _readBytes(devAddr, 0x43, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
/** Get Y-axis gyroscope reading.
 * @return Y-axis rotation measurement in 16-bit 2's complement format
 * @see getMotion6()
 * @see MPU6050_RA_GYRO_YOUT_H
 */
int16_t Imu::getRotationYRaw() {
    _readBytes(devAddr, 0x45, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
/** Get Z-axis gyroscope reading.
 * @return Z-axis rotation measurement in 16-bit 2's complement format
 * @see getMotion6()
 * @see MPU6050_RA_GYRO_ZOUT_H
 */
int16_t Imu::getRotationZRaw() {
    _readBytes(devAddr, 0x47, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}

/**
  @brief      Fully calibrate Gyro from ZERO in about 6-7 Loops 600-700 readings
*/
void Imu::_CalibrateGyro(uint8_t Loops ) {
  double kP = 0.3;
  double kI = 90;
  float x;
  x = (100 - map(Loops, 1, 5, 20, 0)) * .01;
  kP *= x;
  kI *= x;
  
  _PID( 0x43,  kP, kI,  Loops);
}

/**
  @brief      Fully calibrate Accel from ZERO in about 6-7 Loops 600-700 readings
*/
void Imu::_CalibrateAccel(uint8_t Loops ) {

	float kP = 0.3;
	float kI = 20;
	float x;
	x = (100 - map(Loops, 1, 5, 20, 0)) * .01;
	kP *= x;
	kI *= x;
	_PID( 0x3B, kP, kI,  Loops);
}

void Imu::_PID(uint8_t ReadAddress, float kP,float kI, uint8_t Loops){
	uint8_t SaveAddress = (ReadAddress == 0x3B)?((_getDeviceID() < 0x38 )? 0x06:0x77):0x13;

	int16_t  Data;
	float Reading;
	int16_t BitZero[3];
	uint8_t shift =(SaveAddress == 0x77)?3:2;
	float Error, PTerm, ITerm[3];
	int16_t eSample;
	uint32_t eSum ;
	Serial.write('>');
	for (int i = 0; i < 3; i++) {
		_readWords(devAddr, SaveAddress + (i * shift), 1, (uint16_t *)&Data); // reads 1 or more 16 bit integers (Word)
		Reading = Data;
		if(SaveAddress != 0x13){
			BitZero[i] = Data & 1;										 // Capture Bit Zero to properly handle Accelerometer calibration
			ITerm[i] = ((float)Reading) * 8;
			} else {
			ITerm[i] = Reading * 4;
		}
	}
	for (int L = 0; L < Loops; L++) {
		eSample = 0;
		for (int c = 0; c < 100; c++) {// 100 PI Calculations
			eSum = 0;
			for (int i = 0; i < 3; i++) {
				_readWords(devAddr, ReadAddress + (i * 2), 1, (uint16_t *)&Data); // reads 1 or more 16 bit integers (Word)
				Reading = Data;
				if ((ReadAddress == 0x3B)&&(i == 2)) Reading -= 16384;	//remove Gravity
				Error = -Reading;
				eSum += abs(Reading);
				PTerm = kP * Error;
				ITerm[i] += (Error * 0.001) * kI;				// Integral term 1000 Calculations a second = 0.001
				if(SaveAddress != 0x13){
					Data = round((PTerm + ITerm[i] ) / 8);		//Compute PID Output
					Data = ((Data)&0xFFFE) |BitZero[i];			// Insert Bit0 Saved at beginning
				} else Data = round((PTerm + ITerm[i] ) / 4);	//Compute PID Output
				_writeWords(devAddr, SaveAddress + (i * shift), 1, (uint16_t *)&Data);
			}
			if((c == 99) && eSum > 1000){						// Error is still to great to continue 
				c = 0;
				Serial.write('*');
			}
			if((eSum * ((ReadAddress == 0x3B)?.05: 1)) < 5) eSample++;	// Successfully found offsets prepare to  advance
			if((eSum < 100) && (c > 10) && (eSample >= 10)) break;		// Advance to next Loop
			delay(1);
		}
		Serial.write('.');
		kP *= .75;
		kI *= .75;
		for (int i = 0; i < 3; i++){
			if(SaveAddress != 0x13) {
				Data = round((ITerm[i] ) / 8);		//Compute PID Output
				Data = ((Data)&0xFFFE) |BitZero[i];	// Insert Bit0 Saved at beginning
			} else Data = round((ITerm[i]) / 4);
			_writeWords(devAddr, SaveAddress + (i * shift), 1, (uint16_t *)&Data);
		}
	}
	_resetFIFO();
	_resetDMP();
}

#define printfloatx(Name,Variable,Spaces,Precision,EndTxt) { Serial.print(F(Name)); {char S[(Spaces + Precision + 3)];Serial.print(F(" ")); Serial.print(dtostrf((float)Variable,Spaces,Precision ,S));}Serial.print(F(EndTxt)); }//Name,Variable,Spaces,Precision,EndTxt
void Imu::_PrintActiveOffsets() {
	uint8_t AOffsetRegister = (_getDeviceID() < 0x38 )? 0x06:0x77;
	int16_t Data[3];
	//Serial.print(F("Offset Register 0x"));
	//Serial.print(AOffsetRegister>>4,HEX);Serial.print(AOffsetRegister&0x0F,HEX);
	Serial.print(F("\n//           X Accel  Y Accel  Z Accel   X Gyro   Y Gyro   Z Gyro\n//OFFSETS   "));
	if(AOffsetRegister == 0x06)	_readWords(devAddr, AOffsetRegister, 3, (uint16_t *)Data);
	else {
		_readWords(devAddr, AOffsetRegister, 1, (uint16_t *)Data);
		_readWords(devAddr, AOffsetRegister+3, 1, (uint16_t *)Data+1);
		_readWords(devAddr, AOffsetRegister+6, 1, (uint16_t *)Data+2);
	}
	//	A_OFFSET_H_READ_A_OFFS(Data);
	printfloatx("", Data[0], 5, 0, ",  ");
	printfloatx("", Data[1], 5, 0, ",  ");
	printfloatx("", Data[2], 5, 0, ",  ");
	_readWords(devAddr, 0x13, 3, (uint16_t *)Data);
	//	XG_OFFSET_H_READ_OFFS_USR(Data);
	printfloatx("", Data[0], 5, 0, ",  ");
	printfloatx("", Data[1], 5, 0, ",  ");
	printfloatx("", Data[2], 5, 0, "\n");
}

void Imu::_resetFIFO() {
    _writeBit(devAddr, 0x6A, 2, true); // ( , MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_FIFO_RESET_BIT, )
}
void Imu::_resetDMP() {
    _writeBit(devAddr, 0x6A, 3, true); // ( , MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_DMP_RESET_BIT, )
}


//
//      I2Cdev lib
//
/** Read a single bit from a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param bitNum Bit position to read (0-15)
 * @param data Container for single bit value
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t Imu::_readBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t *data, uint16_t timeout) {
    uint16_t b;
    uint8_t count = _readWord(devAddr, regAddr, &b, timeout);
    *data = b & (1 << bitNum);
    return count;
}

/** Read multiple bits from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param bitStart First bit position to read (0-7)
 * @param length Number of bits to read (not more than 8)
 * @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t Imu::_readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data, uint16_t timeout) {
    // 01101001 read byte
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    //    010   masked
    //   -> 010 shifted
    uint8_t count, b;
    if ((count = _readByte(devAddr, regAddr, &b, timeout)) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        b &= mask;
        b >>= (bitStart - length + 1);
        *data = b;
    }
    return count;
}

/** Read multiple bits from a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param bitStart First bit position to read (0-15)
 * @param length Number of bits to read (not more than 16)
 * @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Status of read operation (1 = success, 0 = failure, -1 = timeout)
 */
int8_t Imu::_readBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data, uint16_t timeout) {
    // 1101011001101001 read byte
    // fedcba9876543210 bit numbers
    //    xxx           args: bitStart=12, length=3
    //    010           masked
    //           -> 010 shifted
    uint8_t count;
    uint16_t w;
    if ((count = _readWord(devAddr, regAddr, &w, timeout)) != 0) {
        uint16_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        w &= mask;
        w >>= (bitStart - length + 1);
        *data = w;
    }
    return count;
}

/** Read single byte from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param data Container for byte value read from device
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t Imu::_readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout) {
    return _readBytes(devAddr, regAddr, 1, data, timeout);
}

/** Read single word from a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param data Container for word value read from device
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t Imu::_readWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data, uint16_t timeout) {
    return _readWords(devAddr, regAddr, 1, data, timeout);
}

/** Read multiple bytes from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr First register regAddr to read from
 * @param length Number of bytes to read
 * @param data Buffer to store read data in
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Number of bytes read (-1 indicates failure)
 */
int8_t Imu::_readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout) {
    int8_t count = 0;
    uint32_t t1 = millis();

    // Arduino v1.0.1+, Wire library
    // Adds official support for repeated start condition, yay!

    // I2C/TWI subsystem uses internal buffer that breaks with large data requests
    // so if user requests more than BUFFER_LENGTH bytes, we have to do it in
    // smaller chunks instead of all at once
    for (uint8_t k = 0; k < length; k += min((int)length, 32)) {
        Wire.beginTransmission(devAddr);
        Wire.write(regAddr);
        Wire.endTransmission();
        Wire.beginTransmission(devAddr);
        Wire.requestFrom(devAddr, (uint8_t)min(length - k, 32));

        for (; Wire.available() && (timeout == 0 || millis() - t1 < timeout); count++) {
            data[count] = Wire.read();
        }
    }

    // check for timeout
    if (timeout > 0 && millis() - t1 >= timeout && count < length) count = -1; // timeout

    return count;
}

/** Read multiple words from a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr First register regAddr to read from
 * @param length Number of words to read
 * @param data Buffer to store read data in
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Number of words read (-1 indicates failure)
 */
int8_t Imu::_readWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data, uint16_t timeout) {

    int8_t count = 0;
    uint32_t t1 = millis();

    // Arduino v1.0.1+, Wire library
    // Adds official support for repeated start condition, yay!

    // I2C/TWI subsystem uses internal buffer that breaks with large data requests
    // so if user requests more than BUFFER_LENGTH bytes, we have to do it in
    // smaller chunks instead of all at once
    for (uint8_t k = 0; k < length * 2; k += min(length * 2, 32)) {
        Wire.beginTransmission(devAddr);
        Wire.write(regAddr);
        Wire.endTransmission();
        Wire.beginTransmission(devAddr);
        Wire.requestFrom(devAddr, (uint8_t)(length * 2)); // length=words, this wants bytes

        bool msb = true; // starts with MSB, then LSB
        for (; Wire.available() && count < length && (timeout == 0 || millis() - t1 < timeout);) {
            if (msb) {
                // first byte is bits 15-8 (MSb=15)
                data[count] = Wire.read() << 8;
            } else {
                // second byte is bits 7-0 (LSb=0)
                data[count] |= Wire.read();
                count++;
            }
            msb = !msb;
        }

        Wire.endTransmission();
    }

    if (timeout > 0 && millis() - t1 >= timeout && count < length) count = -1; // timeout

    return count;
}

/** write a single bit in an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitNum Bit position to write (0-7)
 * @param value New bit value to write
 * @return Status of operation (true = success)
 */
bool Imu::_writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data) {
    uint8_t b;
    _readByte(devAddr, regAddr, &b);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    return _writeByte(devAddr, regAddr, b);
}

/** write a single bit in a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitNum Bit position to write (0-15)
 * @param value New bit value to write
 * @return Status of operation (true = success)
 */
bool Imu::_writeBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t data) {
    uint16_t w;
    _readWord(devAddr, regAddr, &w);
    w = (data != 0) ? (w | (1 << bitNum)) : (w & ~(1 << bitNum));
    return _writeWord(devAddr, regAddr, w);
}

/** Write multiple bits in an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitStart First bit position to write (0-7)
 * @param length Number of bits to write (not more than 8)
 * @param data Right-aligned value to write
 * @return Status of operation (true = success)
 */
bool Imu::_writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) {
    //      010 value to write
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    // 00011100 mask byte
    // 10101111 original value (sample)
    // 10100011 original & ~mask
    // 10101011 masked | value
    uint8_t b;
    if (_readByte(devAddr, regAddr, &b) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        b &= ~(mask); // zero all important bits in existing byte
        b |= data; // combine data with existing byte
        return _writeByte(devAddr, regAddr, b);
    } else {
        return false;
    }
}

/** Write multiple bits in a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitStart First bit position to write (0-15)
 * @param length Number of bits to write (not more than 16)
 * @param data Right-aligned value to write
 * @return Status of operation (true = success)
 */
bool Imu::_writeBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data) {
    //              010 value to write
    // fedcba9876543210 bit numbers
    //    xxx           args: bitStart=12, length=3
    // 0001110000000000 mask word
    // 1010111110010110 original value (sample)
    // 1010001110010110 original & ~mask
    // 1010101110010110 masked | value
    uint16_t w;
    if (_readWord(devAddr, regAddr, &w) != 0) {
        uint16_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        w &= ~(mask); // zero all important bits in existing word
        w |= data; // combine data with existing word
        return _writeWord(devAddr, regAddr, w);
    } else {
        return false;
    }
}

/** Write single byte to an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register address to write to
 * @param data New byte value to write
 * @return Status of operation (true = success)
 */
bool Imu::_writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data) {
    return _writeBytes(devAddr, regAddr, 1, &data);
}

/** Write single word to a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register address to write to
 * @param data New word value to write
 * @return Status of operation (true = success)
 */
bool Imu::_writeWord(uint8_t devAddr, uint8_t regAddr, uint16_t data) {
    return _writeWords(devAddr, regAddr, 1, &data);
}

/** Write multiple bytes to an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr First register address to write to
 * @param length Number of bytes to write
 * @param data Buffer to copy new data from
 * @return Status of operation (true = success)
 */
bool Imu::_writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* data) {

    uint8_t status = 0;

    Wire.beginTransmission(devAddr);
    Wire.write((uint8_t) regAddr); // send address

    for (uint8_t i = 0; i < length; i++) {
        Wire.write((uint8_t) data[i]);
    }    
    status = Wire.endTransmission();

    return status == 0;
}

/** Write multiple words to a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr First register address to write to
 * @param length Number of words to write
 * @param data Buffer to copy new data from
 * @return Status of operation (true = success)
 */
bool Imu::_writeWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t* data) {
    uint8_t status = 0;
    
        Wire.beginTransmission(devAddr);
        Wire.write(regAddr); // send address

    for (uint8_t i = 0; i < length; i++) { 
        Wire.write((uint8_t)(data[i] >> 8));    // send MSB
        Wire.write((uint8_t)data[i]);         // send LSB
    }    
    status = Wire.endTransmission();    

    return status == 0;
}
