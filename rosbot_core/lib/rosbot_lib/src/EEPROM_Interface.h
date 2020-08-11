#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

#include "Arduino.h"
#include <EEPROM.h>

#define STRING_MAX_SIZE 30
#define STRING_BUFFER_SIZE 32

#define EEPROM_SIZE 128

//String
#define SSID_ADDRESS 0
#define PASS_ADDRESS 32
#define ROS_MASTER_ADDRESS 64

//bool 1-byte
#define MOTOR_RIGHT_PID_CUSTOM_ADDRESS 96
#define MOTOR_LEFT_PID_CUSTOM_ADDRESS 97

//float 4-byte
#define MOTOR_RIGHT_P_ADDRESS 98
#define MOTOR_RIGHT_I_ADDRESS 102
#define MOTOR_RIGHT_D_ADDRESS 106

#define MOTOR_LEFT_P_ADDRESS 110
#define MOTOR_LEFT_I_ADDRESS 114
#define MOTOR_LEFT_D_ADDRESS 118

#define LIDAR_BACKLASH_ADDRESS 122
#define LIDAR_ANGLE_ADDRESS 126

class EEPROM_Interface
{
public:
    EEPROM_Interface();
    void init();

    String getSSID();
    String getPASS();
    String getROSMaster();
    void setSSID(String new_SSID);
    void setPASS(String new_PASS);
    void setROSMaster(String new_server_IP);

    char getMOTOR_PID_CUSTOM(String motor);
    float getMOTOR_P(String motor);
    float getMOTOR_I(String motor);
    float getMOTOR_D(String motor);

    void setMOTOR_PID_CUSTOM(String motor, char new_MOTOR_PID_CUSTOM);
    void setMOTOR_P(String motor, float new_MOTOR_P);
    void setMOTOR_I(String motor, float new_MOTOR_I);
    void setMOTOR_D(String motor, float new_MOTOR_D);

    float getLIDAR_Backlash();
    int getLIDAR_Angle();

    void setLIDAR_Backlash(float new_LIDAR_Backlash);
    void setLIDAR_Angle(int new_LIDAR_Angle);

private:
    void _writeEEPROM(int address, String s);
    String _readEEPROM(int address);

    void _writeEEPROM_int(int address, int i);
    int _readEEPROM_int(int address);

    void _writeEEPROM_float(int address, float f);
    float _readEEPROM_float(int address);

    String _SSID = "";
    String _PASS = "";
    String _ROS_MASTER = "";

    char _MOTOR_RIGHT_PID_CUSTOM = 0;
    char _MOTOR_LEFT_PID_CUSTOM = 0;

    float _MOTOR_RIGHT_P = 0.0f;
    float _MOTOR_RIGHT_I = 0.0f;
    float _MOTOR_RIGHT_D = 0.0f;

    float _MOTOR_LEFT_P = 0.0f;
    float _MOTOR_LEFT_I = 0.0f;
    float _MOTOR_LEFT_D = 0.0f;

    float _LIDAR_Backlash = 0.0f;
    int _LIDAR_Angle = 0;
};

#endif