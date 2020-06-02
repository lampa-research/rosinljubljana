#include "Battery.h"

Battery::Battery()
{
}

float Battery::getVoltage()
{
    return analogRead(VBAT) * 2.0 * 3.30 / 4095.0;
}
