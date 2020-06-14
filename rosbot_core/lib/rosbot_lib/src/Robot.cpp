#include "Robot.h"

void IRAM_ATTR ISR_L_A()
{
    robot.motor_left.setEncoderCountA();
}

void IRAM_ATTR ISR_L_B()
{
    robot.motor_left.setEncoderCountB();
}

void IRAM_ATTR ISR_R_A()
{
    robot.motor_right.setEncoderCountA();
}

void IRAM_ATTR ISR_R_B()
{
    robot.motor_right.setEncoderCountB();
}

Robot::Robot()
{
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
    motor_left.begin(LEFT, 100, true, &ISR_L_A, &ISR_L_B);
    motor_right.begin(RIGHT, 100, false, &ISR_R_A, &ISR_R_B);
    Serial.begin(115200);
}

void Robot::spinOnce()
{
    ulong current_time = micros();
    float dt = (current_time - _last_update) / 1000000.0;
    _last_update = current_time;
    // set motor speeds
    robot.motor_left.setSpeed(_speed_linear_ref - _speed_angular_ref * WHEELBASE / 2.0);
    robot.motor_right.setSpeed(_speed_linear_ref + _speed_angular_ref * WHEELBASE / 2.0);
    // get motor speeds
    float speed_left = robot.motor_left.getSpeed();
    float speed_right = robot.motor_right.getSpeed();
    // calculate odometry data
    speed_linear = (speed_right + speed_left) / 2.0;
    speed_angular = (speed_right - speed_left) / WHEELBASE;
    position_x += cos(orientation_z) * speed_linear * dt;
    position_y += sin(orientation_z) * speed_linear * dt;
    orientation_z = fmod(orientation_z + speed_angular * dt + PI / 2, PI) - PI / 2;
}

void Robot::setSpeed(float speed_linear, float speed_angular)
{
    _speed_linear_ref = speed_linear;
    _speed_angular_ref = speed_angular;
}

Robot robot = Robot();
