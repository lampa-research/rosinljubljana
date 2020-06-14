#include "Arduino.h"
#include "Battery.h"

/**
 * @brief Construct a new Battery object.
 * 
 */
Battery::Battery()
{
}

/**
 * @brief Returns the current battery voltage.
 * The normal range for battery voltage is between 3.7V and 4.2V.
 * @return float Current battery voltage.
 */
float Battery::getVoltage()
{
    return analogRead(VBAT) * 2.0 * 3.30 / 4095.0;
}

/**
 * @brief Returns the battery voltage, averages over a specified period.
 * 
 * @param ms Period in milliseconds.
 * @return float Average battery voltage.
 */
float Battery::getAverageVoltage(uint32_t ms)
{
    uint32_t start = millis();
    float voltage = 0.0;
    uint32_t count = 0;
    while (millis() - start < ms)
    {
        voltage += getVoltage();
        count++;
    }
    return voltage / count;
}
