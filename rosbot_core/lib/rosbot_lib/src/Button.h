#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"
#include "Pinout.h"

/**
 * @brief Button class.
 * 
 */
class Button
{
public:
    Button();
    bool pressed();
    void wait();

private:
};

#endif