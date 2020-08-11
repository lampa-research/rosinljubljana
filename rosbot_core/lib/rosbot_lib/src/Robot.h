#ifndef ROBOT_H
#define ROBOT_H

#include <Wire.h>
#include "Arduino.h"
#include "Battery.h"
#include "Button.h"
#include "Buzzer.h"
#include "Constants.h"
#include "EEPROM_Interface.h"
#include "Led.h"
#include "Lidar.h"
#include "IMU.h"
#include "Motor.h"
#include "Pinout.h"
#include "Setup.h"

class Robot
{
public:
    Robot();
    Battery battery = Battery();
    Button button = Button();
    // Buzzer buzzer = Buzzer();
    Led led = Led();
    Lidar lidar = Lidar();
    IMU imu = IMU();
    Motor motor_left = Motor();
    Motor motor_right = Motor();

    EEPROM_Interface eeprom = EEPROM_Interface();
    Setup setup = Setup(eeprom, /*buzzer,*/ button, imu);
    void syncSetup();

    void spinOnce();

    void setSpeed(float speed_linear, float speed_angular);
    void refreshSpeed();
    void refreshPosition();
    float getRotation();
    float getPositionX();
    float getPositionY();
    float getSpeedAngular();
    float getSpeedLinear();
    void setLidarStarted(bool started);
    bool lidarStarted();
    void setLidarBacklash(float backlash);
    float getLidarBacklash();
    void setLidarAngle(int angle);
    int getLidarAngle();
    bool isMoving();

private:
    float _rotation_z = 0.0f;
    float _position_x = 0.0f;
    float _position_y = 0.0f;
    float _speed_linear = 0.0f;
    float _speed_angular = 0.0f;

    bool _lidar_started = false;
    float _lidar_backlash = 0.06;
    int _lidar_angle = 90;
};

extern Robot robot;

#endif