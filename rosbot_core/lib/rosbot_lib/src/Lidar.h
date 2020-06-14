#ifndef LIDAR_H
#define LIDAR_H

#include "Arduino.h"
#include "Pinout.h"

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

    S_DIST_ADC_MAP _distAdcMap[26] = {
        {0.083, 2937},
        {0.090, 2840},
        {0.100, 2653},
        {0.110, 2431},
        {0.120, 2222},
        {0.130, 2031},
        {0.140, 1855},
        {0.150, 1700},
        {0.160, 1615},
        {0.170, 1490},
        {0.180, 1417},
        {0.190, 1322},
        {0.200, 1256},
        {0.210, 1205},
        {0.220, 1130},
        {0.230, 1085},
        {0.240, 1050},
        {0.250, 1005},
        {0.260, 959},
        {0.270, 925},
        {0.280, 903},
        {0.290, 875},
        {0.300, 840},
        {0.310, 819},
        {0.320, 799},
        {0.330, 777},
    };
};

#endif