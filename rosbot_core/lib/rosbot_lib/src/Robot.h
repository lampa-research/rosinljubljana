#ifndef ROBOT_H
#define ROBOT_H

#include "Arduino.h"
#include "Pinout.h"
#include "Battery.h"
#include "Button.h"
#include "Buzzer.h"
#include "Led.h"
#include "Lidar.h"
#include "Motor.h"

#define WHEELBASE 0.0825

class Robot
{
public:
    Robot();
    Battery battery = Battery();
    Button button = Button();
    Buzzer buzzer = Buzzer();
    Led led = Led();
    Lidar lidar = Lidar();
    Motor motor_left = Motor();
    Motor motor_right = Motor();

    void spinOnce();
    void setSpeed(float speed_linear, float speed_angular);
    float speed_linear = 0.0;
    float speed_angular = 0.0;
    float position_x = 0.0;
    float position_y = 0.0;
    float orientation_z = 0.0;

private:
    float _speed_linear_ref = 0.0;
    float _speed_angular_ref = 0.0;
    ulong _last_update = 0;
};

extern Robot robot;

#endif