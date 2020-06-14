#ifndef BUZZER_H
#define BUZZER_H

#include "Arduino.h"
#include "Pinout.h"

/**
 * @brief Buzzer class.
 * 
 */
class Buzzer
{
public:
    Buzzer();
    void on(double freq);
    void off();
    void beep(double freq, uint32_t ms);

private:
};

#endif