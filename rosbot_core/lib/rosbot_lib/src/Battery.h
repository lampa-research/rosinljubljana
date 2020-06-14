#ifndef BATTERY_H
#define BATTERY_H

#include "Arduino.h"
#include "Pinout.h"

/**
 * @brief Battery class.
 * 
 */
class Battery
{
public:
    Battery();
    float getVoltage();
    float getAverageVoltage(uint32_t ms);

private:
};

#endif