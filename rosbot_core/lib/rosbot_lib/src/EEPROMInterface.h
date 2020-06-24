#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

#include "Arduino.h"
#include <EEPROM.h>

#define EEPROM_SIZE 192
#define YES "y"
#define NO "n"
#define QUIT "q"
#define SSID_ADDRESS 0
#define PASS_ADDRESS 64
#define ROS_MASTER_ADDRESS 128
#define STRING_BUFFER_SIZE 64
#define STRING_MAX_SIZE 62

class EEPROMInterface
{
public:
    EEPROMInterface();
    void init();
    void setup();

    String getSSID();
    String getPASS();
    String getROSMaster();

private:
    String _readLineSerial();
    void _setupWiFi(String data_type);
    void _writeEEPROM(int address, String s);
    String _readEEPROM(int address);

    bool _quit_setup = false;

    String _SSID = "";
    String _PASS = "";
    String _ROS_MASTER = "";
};

#endif