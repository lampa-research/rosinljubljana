#ifndef LIDAR_H
#define LIDAR_H

#include "Arduino.h"
#include "Pinout.h"
#include "Constants.h"

/**
 * @brief Lidar class.
 * 
 */
class Lidar
{
public:
    Lidar();
    float getDistance();
    float getDistanceAverage(int measurements);
    void setPosition(int angle);
    int currentPosition();
    void nextPosition(int step);

private:
    int _usToDuty(int us) { return map(us, 0, 20000, 0, 65535); }
    int _dutyToUs(int duty) { return map(duty, 0, 65535, 0, 20000); }
    int _usToAngle(int us) { return map(us, 544, 2400, 0, 180); }
    int _angleToUs(int angle) { return map(angle, 0, 180, 544, 2400); }

    float _adcToDist(float adcVal);
    float _distance = 0.0;
    int _servoVal = 0;
    int _servoDir = 1;
    float _adcVal = 0.0f;

    struct S_DIST_ADC_MAP
    {
        float distance;
        float adcVal;
    };

    S_DIST_ADC_MAP _distAdcMap[30] = {
        {0.083, 2648},
        {0.093, 2562},
        {0.103, 2378},
        {0.113, 2189},
        {0.123, 1972},
        {0.133, 1828},
        {0.143, 1676},
        {0.153, 1535},
        {0.163, 1456},
        {0.173, 1343},
        {0.183, 1281},
        {0.193, 1192},
        {0.203, 1137},
        {0.213, 1090},
        {0.223, 1019},
        {0.233, 978},
        {0.243, 942},
        {0.253, 908},
        {0.263, 866},
        {0.273, 835},
        {0.283, 812},
        {0.333, 690},
        {0.433, 557},
        {0.533, 452},
        {0.633, 381},
        {0.733, 330},
        {0.833, 294},
        {0.933, 266},
        {1.033, 242},
        {1.133, 228}};
};

#endif