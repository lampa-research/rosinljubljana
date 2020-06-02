#ifndef ROBOT_H
#define ROBOT_H

#include "Arduino.h"
#include "Pinout.h"
#include "Battery.h"

class Robot
{
public:
    Robot();
    Battery battery = Battery();

private:
};

extern Robot robot;

#endif