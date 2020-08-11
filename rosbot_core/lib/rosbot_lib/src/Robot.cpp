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
    Serial.begin(115200);
    Wire.begin(SDA, SCL);

    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);

    motor_left.init(LEFT, true, &ISR_L_A, &ISR_L_B);
    motor_right.init(RIGHT, false, &ISR_R_A, &ISR_R_B);
}

void Robot::syncSetup()
{
    if (eeprom.getMOTOR_PID_CUSTOM("right") == 1)
    {
        motor_right.setSpeedPIDGains(eeprom.getMOTOR_P("right"), eeprom.getMOTOR_I("right"), eeprom.getMOTOR_D("right"));
    }
    else
    {
        motor_right.resetSpeedPIDGains();
    }

    if (eeprom.getMOTOR_PID_CUSTOM("left") == 1)
    {
        motor_left.setSpeedPIDGains(eeprom.getMOTOR_P("left"), eeprom.getMOTOR_I("left"), eeprom.getMOTOR_D("left"));
    }
    else
    {
        motor_left.resetSpeedPIDGains();
    }

    //robot.buzzer.beep(2000, 200);
    //delay(200);
    //robot.buzzer.beep(2000, 200);

    return;
}

void Robot::spinOnce()
{
    refreshSpeed();
    refreshPosition();
    motor_left.spinOnce();
    motor_right.spinOnce();
    imu.update();
}

void Robot::setSpeed(float speed_linear, float speed_angular)
{
    float speed_diff = speed_angular * ROBOT_WHEELBASE / 2;
    motor_left.setSpeed(speed_linear - speed_diff);
    motor_right.setSpeed(speed_linear + speed_diff);
    return;
}

float Robot::getRotation()
{
    return _rotation_z;
}

float Robot::getPositionX()
{
    return _position_x;
}

float Robot::getPositionY()
{
    return _position_y;
}

float Robot::getSpeedLinear()
{
    return _speed_linear;
}

float Robot::getSpeedAngular()
{
    return _speed_angular;
}

void Robot::refreshSpeed()
{
    float speed_left = robot.motor_left.getSpeed();
    float speed_right = robot.motor_right.getSpeed();
    float speed_diff = speed_right - speed_left;

    _speed_linear = speed_left + speed_diff / 2.0f;
    _speed_angular = speed_diff / ROBOT_WHEELBASE;
}

void Robot::refreshPosition()
{
    int L = robot.motor_left.getEncoderCountPosition();
    int R = robot.motor_right.getEncoderCountPosition();
    float dX = 0.0f;
    float dY = 0.0f;
    int dir_L = 0;
    int dir_R = 0;
    int L_count = abs(L);
    int R_count = abs(R);
    if (L_count > 0)
    {
        dir_L = L / L_count;
    }
    if (R_count > 0)
    {
        dir_R = R / R_count;
    }
    while (L_count > 0 || R_count > 0)
    {
        if (L_count > 0)
        {
            L_count--;
            _rotation_z = _rotation_z - ROBOT_ROTATION_INCREMENT * dir_L;
            float rotation_mid = _rotation_z + ROBOT_ROTATION_INCREMENT / 2.0 * dir_L;
            dX = cos(rotation_mid) * (ROBOT_TRANSLATION_INCREMENT)*dir_L;
            dY = sin(rotation_mid) * (ROBOT_TRANSLATION_INCREMENT)*dir_L;
            _position_x = _position_x + dX;
            _position_y = _position_y + dY;
        }

        if (R_count > 0)
        {
            R_count--;
            _rotation_z = _rotation_z + ROBOT_ROTATION_INCREMENT * dir_R;
            float rotation_mid = _rotation_z - ROBOT_ROTATION_INCREMENT / 2.0 * dir_L;
            dX = cos(rotation_mid) * ROBOT_TRANSLATION_INCREMENT * dir_R;
            dY = sin(rotation_mid) * ROBOT_TRANSLATION_INCREMENT * dir_R;
            _position_x = _position_x + dX;
            _position_y = _position_y + dY;
        }
    }

    if (_rotation_z > PI)
    {
        _rotation_z = _rotation_z - 2 * PI;
    }
    else if (_rotation_z <= -PI)
    {
        _rotation_z = _rotation_z + 2 * PI;
    }
}

void Robot::setLidarStarted(bool started)
{
    _lidar_started = started;
}

bool Robot::lidarStarted()
{
    return _lidar_started;
}

void Robot::setLidarBacklash(float backlash)
{
    _lidar_backlash = backlash;
}

float Robot::getLidarBacklash()
{
    return _lidar_backlash;
}

void Robot::setLidarAngle(int angle)
{
    _lidar_angle = angle;
}

int Robot::getLidarAngle()
{
    return _lidar_angle;
}

bool Robot::isMoving()
{
    if (fabs(getSpeedLinear()) < 0.0001 && fabs(getSpeedAngular()) < 0.0001)
    {
        return false;
    }
    else
    {
        return true;
    }
}

Robot robot = Robot();
