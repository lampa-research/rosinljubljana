#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"
#include "Pinout.h"

#define LEFT 0
#define RIGHT 1

class Motor
{
public:
    Motor(int motor);
    float getVoltage();
    void setVoltage(float u);
    float getSpeed();
    void setSpeed(float w);
    void setSpeedGains(float kp, float ki, float kd);
    void setSpeedILimit(float limit);
    void resetI();
    float getDistance();
    void resetDistance();
    float getDistanceRad();

private:
    int _motor = 0;
    float _kp = 0.15;
    float _ki = 0.70;
    float _kd = 0.00;
    float _errorIntegral = 0.0;
    float _errorIntegralLimit = 2.0;
    float _errorPrevious = 0.0;
};

#endif
