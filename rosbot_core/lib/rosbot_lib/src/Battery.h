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
    /**
     * @brief Construct a new Battery object.
     * 
     */
    Battery();
    /**
     * @brief Returns the current battery voltage.
     * The normal range for battery voltage is between 3.7V and 4.2V.
     * @return float Current battery voltage.
     */
    float getVoltage();

private:
};

#endif