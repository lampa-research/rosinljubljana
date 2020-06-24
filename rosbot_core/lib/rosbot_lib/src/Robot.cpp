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

    motor_left.init(LEFT, true, &ISR_L_A, &ISR_L_B);
    motor_right.init(RIGHT, false, &ISR_R_A, &ISR_R_B);
}

void Robot::spinOnce()
{
    refreshSpeed();
    refreshPosition();
    motor_left.spinOnce();
    motor_right.spinOnce();
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
            dX = cos(rotation_mid) * (-ROBOT_TRANSLATION_INCREMENT) * dir_L;
            dY = sin(rotation_mid) * (-ROBOT_TRANSLATION_INCREMENT) * dir_L;
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

void Robot::checkSerialCommunication()
{
    if (Serial.available() > 0)
    {
        char c = Serial.read();
        if (c == '#')
        {
            Serial.flush();

            robot.eeprom.setup();
        }
        else if (c == '?')
        {
            Serial.flush();

            Serial.println("\n--- WiFi data ---\n");

            Serial.print("WiFi SSID: ");
            Serial.println(robot.eeprom.getSSID());
            Serial.print("Password: ");
            Serial.println(robot.eeprom.getPASS());
            Serial.print("Server IP: ");
            Serial.println(robot.eeprom.getROSMaster());
            Serial.flush();
        }
    }
}

void Robot::initSerialCommunication()
{
    Serial.begin(115200);
    delay(1000);
    for (int i = 0; i < 10; i++)
    {
        Serial.println("");
    }
    Serial.println("\n*** Welcome to ROSin Ljubljana. ***\n");
    eeprom.init();
}

Robot robot = Robot();
