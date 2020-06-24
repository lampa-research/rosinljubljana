#include "EEPROMInterface.h"

/**
 * @brief Construct a new EEPROMInterface object
 * Currently does nothing besides instantiation.
 * 
 */
EEPROMInterface::EEPROMInterface()
{
}

/**
 * @brief Initialises the EEPROM interface and reads the data.
 * 
 */
void EEPROMInterface::init()
{
    Serial.println("Setting up EEPROM");
    if (EEPROM.begin(EEPROM_SIZE))
    {
        Serial.println("Reading default parameters");
        _SSID = _readEEPROM(SSID_ADDRESS);
        _PASS = _readEEPROM(PASS_ADDRESS);
        _ROS_MASTER = _readEEPROM(ROS_MASTER_ADDRESS);
    }
    else
    {
        Serial.println("\n\nERROR: Failed to initialise EEPROM.\n\n");
    }
    Serial.println("\nPress # to enter setup or ? to print saved setup.\n");
}

/**
 * @brief Provides an interface to save WiFi and networking infromation into EEPROM.
 * 
 */
void EEPROMInterface::setup()
{
    _quit_setup = false;

    Serial.println("\n--- Setup WiFi data ---\n");
    _setupWiFi("SSID");
    _setupWiFi("PASS");
    _setupWiFi("server_IP");
    Serial.println("\nPress the USER button to continue.\n");
    Serial.flush();
    return;
}

/**
 * @brief Returns the WiFi SSID, saved in EEPROM.
 * 
 * @return String SSID.
 */
String EEPROMInterface::getSSID()
{
    return _SSID;
}

/**
 * @brief Returns the WiFi password, saved in EEPROM.
 * 
 * @return String WiFi password.
 */
String EEPROMInterface::getPASS()
{
    return _PASS;
}

/**
 * @brief Returns the ROS Master IP (as String), saved in EEPROM.
 * 
 * @return String ROS Master IP
 */
String EEPROMInterface::getROSMaster()
{
    return _ROS_MASTER;
}

void EEPROMInterface::_setupWiFi(String data_type)
{
    if (!_quit_setup)
    {
        if (data_type == "SSID")
        {
            Serial.println("Do you want to change wifi SSID?");
        }
        else if (data_type == "PASS")
        {
            Serial.println("Do you want to change wifi password?");
        }
        else if (data_type == "server_IP")
        {
            Serial.println("Do you want to change ROS master IP?");
        }
        Serial.println("[(y)es or (n)o or (q)uit]");

        bool key = true;
        while (key)
        {
            key = false;
            String input = _readLineSerial();
            if (input == QUIT)
            {
                _quit_setup = true;
                return;
            }
            else if (input == NO)
            {
                return;
            }
            else if (input == YES)
            {
                if (data_type == "SSID")
                {
                    Serial.println("Enter WiFi SSID. (e.g. 'thisIsMyWiFiName')");
                    String new_SSID = _readLineSerial();
                    if (new_SSID.length() > STRING_MAX_SIZE)
                    {
                        Serial.println("Your WiFi's SSID is too long.");
                        key = true;
                    }
                    else
                    {
                        _SSID = new_SSID;
                        _writeEEPROM(SSID_ADDRESS, _SSID);
                    }
                }
                else if (data_type == "PASS")
                {
                    Serial.println("Enter wifi password. (e.g. 'thisIsMyWiFiPassword')");

                    String new_PASS = _readLineSerial();
                    if (new_PASS.length() > STRING_MAX_SIZE)
                    {
                        Serial.println("Your Wifi's password is too long.");
                        key = true;
                    }
                    else
                    {
                        _PASS = new_PASS;
                        _writeEEPROM(PASS_ADDRESS, _PASS);
                    }
                }
                else if (data_type == "server_IP")
                {
                    Serial.println("Enter ROS server IP. (e.g. '192.168.1.2')");

                    String new_server_IP = _readLineSerial();
                    if (new_server_IP.length() > STRING_MAX_SIZE)
                    {
                        Serial.println("Your ROS server IP is too long.");
                        key = true;
                    }
                    else
                    {
                        _ROS_MASTER = new_server_IP;
                        _writeEEPROM(ROS_MASTER_ADDRESS, _ROS_MASTER);
                    }
                }
            }
            else
            {
                Serial.println("Please decide.");
                Serial.println("(y)es or (n)o or (q)uit\n");
                key = true;
            }
        }
    }
}

void EEPROMInterface::_writeEEPROM(int address, String s)
{
    int len = s.length();

    EEPROM.write(address, len);
    EEPROM.commit();

    for (int i = 0; i < len; i++)
    {
        EEPROM.write(address + 1 + i, s.charAt(i));
        EEPROM.commit();
    }

    return;
}

String EEPROMInterface::_readEEPROM(int address)
{
    int len = EEPROM.read(address);
    if (len > STRING_MAX_SIZE)
    {
        return String("");
    }
    char string[STRING_BUFFER_SIZE];

    for (int i = 0; i < len; i++)
    {
        string[i] = EEPROM.read(address + 1 + i);
    }
    string[len] = '\0';

    return String(string);
}

String EEPROMInterface::_readLineSerial()
{
    bool wait = true;
    int i_buffer = 0;
    char input_buffer[STRING_BUFFER_SIZE];

    while (wait)
    {
        delay(100);
        while (Serial.available())
        {
            char c = Serial.read();
            if (c == '\r' || c == '\n')
            {
                input_buffer[i_buffer] = '\0';
                Serial.println("");
                wait = false;
                break;
            }
            else
            {
                Serial.print(c);
                input_buffer[i_buffer] = c;
                i_buffer++;
                if (i_buffer > STRING_BUFFER_SIZE)
                {
                    i_buffer = i_buffer - 1;
                    input_buffer[i_buffer] = '\0';
                    break;
                }
            }
        }
    }
    Serial.flush();
    return String(input_buffer);
}