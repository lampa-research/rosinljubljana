#ifndef ROBOT_H
#define ROBOT_H

#include <Wire.h>
#include "Arduino.h"
#include "Battery.h"
#include "Button.h"
#include "Buzzer.h"
#include "Constants.h"
#include "EEPROMInterface.h"
#include "Led.h"
#include "Lidar.h"
#include "IMU.h"
#include "Motor.h"
#include "Pinout.h"

class Robot
{
public:
    Robot();
    EEPROMInterface eeprom = EEPROMInterface();
    Battery battery = Battery();
    Button button = Button();
    Buzzer buzzer = Buzzer();
    Led led = Led();
    Lidar lidar = Lidar();
    // Imu imu = Imu();
    Motor motor_left = Motor();
    Motor motor_right = Motor();

    void spinOnce();

    void setSpeed(float speed_linear, float speed_angular);
    void refreshSpeed();
    void refreshPosition();
    float getRotation();
    float getPositionX();
    float getPositionY();
    float getSpeedAngular();
    float getSpeedLinear();
    void initSerialCommunication();
    void checkSerialCommunication();

    void setLidarStarted(bool started);
    bool lidarStarted();

private:
    float _rotation_z = 0.0f;
    float _position_x = 0.0f;
    float _position_y = 0.0f;
    float _speed_linear = 0.0f;
    float _speed_angular = 0.0f;

    bool _lidar_started = false;
};

extern Robot robot;

#endif