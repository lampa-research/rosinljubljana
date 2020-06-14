#ifndef LED_H
#define LED_H

#include "Arduino.h"
#include "Pinout.h"

/**
 * @brief Led class.
 * 
 */
class Led
{
public:
    Led();
    void on();
    void off();

private:
};

#endif