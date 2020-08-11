#include "EEPROM_Interface.h"

/**
 * @brief Construct a new EEPROMInterface object
 * Currently does nothing besides instantiation.
 * 
 */
EEPROM_Interface::EEPROM_Interface()
{
}

/**
 * @brief Initialises the EEPROM interface and reads the data.
 * 
 */
void EEPROM_Interface::init()
{
    Serial.println("Setting up EEPROM");
    if (EEPROM.begin(EEPROM_SIZE))
    {
        Serial.println("Reading default parameters");
        _SSID = _readEEPROM(SSID_ADDRESS);
        _PASS = _readEEPROM(PASS_ADDRESS);
        _ROS_MASTER = _readEEPROM(ROS_MASTER_ADDRESS);

        _MOTOR_RIGHT_PID_CUSTOM = EEPROM.read(MOTOR_RIGHT_PID_CUSTOM_ADDRESS);
        _MOTOR_LEFT_PID_CUSTOM = EEPROM.read(MOTOR_LEFT_PID_CUSTOM_ADDRESS);

        _MOTOR_RIGHT_P = _readEEPROM_float(MOTOR_RIGHT_P_ADDRESS);
        _MOTOR_RIGHT_I = _readEEPROM_float(MOTOR_RIGHT_I_ADDRESS);
        _MOTOR_RIGHT_D = _readEEPROM_float(MOTOR_RIGHT_D_ADDRESS);

        _MOTOR_LEFT_P = _readEEPROM_float(MOTOR_LEFT_P_ADDRESS);
        _MOTOR_LEFT_I = _readEEPROM_float(MOTOR_LEFT_I_ADDRESS);
        _MOTOR_LEFT_D = _readEEPROM_float(MOTOR_LEFT_D_ADDRESS);

        _LIDAR_Backlash = _readEEPROM_float(LIDAR_BACKLASH_ADDRESS);
        _LIDAR_Angle = _readEEPROM_int(LIDAR_ANGLE_ADDRESS);
    }
    else
    {
        Serial.println("\n\nERROR: Failed to initialise EEPROM.\n\n");
    }

    return;
}

//   get

/**
 * @brief Returns the WiFi SSID, saved in EEPROM.
 * 
 * @return String SSID.
 */
String EEPROM_Interface::getSSID()
{
    return _SSID;
}

/**
 * @brief Returns the WiFi password, saved in EEPROM.
 * 
 * @return String WiFi password.
 */
String EEPROM_Interface::getPASS()
{
    return _PASS;
}

/**
 * @brief Returns the ROS Master IP (as String), saved in EEPROM.
 * 
 * @return String ROS Master IP
 */
String EEPROM_Interface::getROSMaster()
{
    return _ROS_MASTER;
}

char EEPROM_Interface::getMOTOR_PID_CUSTOM(String motor)
{
    char x = 0;

    if (motor.equals("right"))
    {
        x = _MOTOR_RIGHT_PID_CUSTOM;
    }
    else if (motor.equals("left"))
    {
        x = _MOTOR_LEFT_PID_CUSTOM;
    }

    return x;
}

float EEPROM_Interface::getMOTOR_P(String motor)
{
    float x = 0.0f;

    if (motor.equals("right"))
    {
        x = _MOTOR_RIGHT_P;
    }
    else if (motor.equals("left"))
    {
        x = _MOTOR_LEFT_P;
    }

    return x;
}

float EEPROM_Interface::getMOTOR_I(String motor)
{
    float x = 0.0f;

    if (motor.equals("right"))
    {
        x = _MOTOR_RIGHT_I;
    }
    else if (motor.equals("left"))
    {
        x = _MOTOR_LEFT_I;
    }

    return x;
}

float EEPROM_Interface::getMOTOR_D(String motor)
{
    float x = 0.0f;

    if (motor.equals("right"))
    {
        x = _MOTOR_RIGHT_D;
    }
    else if (motor.equals("left"))
    {
        x = _MOTOR_LEFT_D;
    }

    return x;
}

float EEPROM_Interface::getLIDAR_Backlash()
{
    return _LIDAR_Backlash;
}

int EEPROM_Interface::getLIDAR_Angle()
{
    return _LIDAR_Angle;
}

//   set

void EEPROM_Interface::setSSID(String new_SSID)
{
    if (new_SSID.length() > STRING_MAX_SIZE)
    {
        Serial.println("Your WiFi's SSID is too long.");
    }
    else
    {
        _SSID = new_SSID;
        _writeEEPROM(SSID_ADDRESS, _SSID);
    }
}

void EEPROM_Interface::setPASS(String new_PASS)
{
    if (new_PASS.length() > STRING_MAX_SIZE)
    {
        Serial.println("Your Wifi's password is too long.");
    }
    else
    {
        _PASS = new_PASS;
        _writeEEPROM(PASS_ADDRESS, _PASS);
    }

    return;
}

void EEPROM_Interface::setROSMaster(String new_server_IP)
{
    if (new_server_IP.length() > STRING_MAX_SIZE)
    {
        Serial.println("Your ROS server IP is too long.");
    }
    else
    {
        _ROS_MASTER = new_server_IP;
        _writeEEPROM(ROS_MASTER_ADDRESS, _ROS_MASTER);
    }

    return;
}

void EEPROM_Interface::setMOTOR_PID_CUSTOM(String motor, char new_MOTOR_PID_CUSTOM)
{

    if (motor.equals("right"))
    {
        _MOTOR_RIGHT_PID_CUSTOM = new_MOTOR_PID_CUSTOM;
        EEPROM.write(MOTOR_RIGHT_PID_CUSTOM_ADDRESS, _MOTOR_RIGHT_PID_CUSTOM);
        EEPROM.commit();
    }
    else if (motor.equals("left"))
    {
        _MOTOR_LEFT_PID_CUSTOM = new_MOTOR_PID_CUSTOM;
        EEPROM.write(MOTOR_LEFT_PID_CUSTOM_ADDRESS, _MOTOR_LEFT_PID_CUSTOM);
        EEPROM.commit();
    }
    else if (motor.equals("both"))
    {
        _MOTOR_RIGHT_PID_CUSTOM = new_MOTOR_PID_CUSTOM;
        EEPROM.write(MOTOR_RIGHT_PID_CUSTOM_ADDRESS, _MOTOR_RIGHT_PID_CUSTOM);
        EEPROM.commit();
        _MOTOR_LEFT_PID_CUSTOM = new_MOTOR_PID_CUSTOM;
        EEPROM.write(MOTOR_LEFT_PID_CUSTOM_ADDRESS, _MOTOR_LEFT_PID_CUSTOM);
        EEPROM.commit();
    }

    return;
}

void EEPROM_Interface::setMOTOR_P(String motor, float new_MOTOR_P)
{
    if (isnan(new_MOTOR_P))
    {
        Serial.println("Entered number is not in a valid float format.");
    }
    else
    {
        if (motor.equals("right"))
        {
            _MOTOR_RIGHT_P = new_MOTOR_P;
            _writeEEPROM_float(MOTOR_RIGHT_P_ADDRESS, _MOTOR_RIGHT_P);
        }
        else if (motor.equals("left"))
        {
            _MOTOR_LEFT_P = new_MOTOR_P;
            _writeEEPROM_float(MOTOR_LEFT_P_ADDRESS, _MOTOR_LEFT_P);
        }
        else if (motor.equals("both"))
        {
            _MOTOR_RIGHT_P = new_MOTOR_P;
            _writeEEPROM_float(MOTOR_RIGHT_P_ADDRESS, _MOTOR_RIGHT_P);
            _MOTOR_LEFT_P = new_MOTOR_P;
            _writeEEPROM_float(MOTOR_LEFT_P_ADDRESS, _MOTOR_LEFT_P);
        }
    }

    return;
}

void EEPROM_Interface::setMOTOR_I(String motor, float new_MOTOR_I)
{
    if (isnan(new_MOTOR_I))
    {
        Serial.println("Entered number is not in a valid float format.");
    }
    else
    {
        if (motor.equals("right"))
        {
            _MOTOR_RIGHT_I = new_MOTOR_I;
            _writeEEPROM_float(MOTOR_RIGHT_I_ADDRESS, _MOTOR_RIGHT_I);
        }
        else if (motor.equals("left"))
        {
            _MOTOR_LEFT_I = new_MOTOR_I;
            _writeEEPROM_float(MOTOR_LEFT_I_ADDRESS, _MOTOR_LEFT_I);
        }
        else if (motor.equals("both"))
        {
            _MOTOR_RIGHT_I = new_MOTOR_I;
            _writeEEPROM_float(MOTOR_RIGHT_I_ADDRESS, _MOTOR_RIGHT_I);
            _MOTOR_LEFT_I = new_MOTOR_I;
            _writeEEPROM_float(MOTOR_LEFT_I_ADDRESS, _MOTOR_LEFT_I);
        }
    }

    return;
}

void EEPROM_Interface::setMOTOR_D(String motor, float new_MOTOR_D)
{
    if (isnan(new_MOTOR_D))
    {
        Serial.println("Entered number is not in a valid float format.");
    }
    else
    {
        if (motor.equals("right"))
        {
            _MOTOR_RIGHT_D = new_MOTOR_D;
            _writeEEPROM_float(MOTOR_RIGHT_D_ADDRESS, _MOTOR_RIGHT_D);
        }
        else if (motor.equals("left"))
        {
            _MOTOR_LEFT_D = new_MOTOR_D;
            _writeEEPROM_float(MOTOR_LEFT_D_ADDRESS, _MOTOR_LEFT_D);
        }
        else if (motor.equals("both"))
        {
            _MOTOR_RIGHT_D = new_MOTOR_D;
            _writeEEPROM_float(MOTOR_RIGHT_D_ADDRESS, _MOTOR_RIGHT_D);
            _MOTOR_LEFT_D = new_MOTOR_D;
            _writeEEPROM_float(MOTOR_LEFT_D_ADDRESS, _MOTOR_LEFT_D);
        }
    }
    return;
}

void EEPROM_Interface::setLIDAR_Backlash(float new_LIDAR_Backlash)
{
    _LIDAR_Backlash = new_LIDAR_Backlash;
    _writeEEPROM_float(LIDAR_BACKLASH_ADDRESS, _LIDAR_Backlash);

    return;
}

void EEPROM_Interface::setLIDAR_Angle(int new_LIDAR_Angle)
{
    _LIDAR_Angle = new_LIDAR_Angle;
    _writeEEPROM_int(LIDAR_ANGLE_ADDRESS, _LIDAR_Angle);

    return;
}

//--- private

void EEPROM_Interface::_writeEEPROM(int address, String s)
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

String EEPROM_Interface::_readEEPROM(int address)
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

void EEPROM_Interface::_writeEEPROM_int(int address, int i)
{
    byte b[4];
    memcpy(&b, &i, 4);

    for (int j = 0; j < 4; j++)
    {
        EEPROM.write(address + j, b[j]);
        EEPROM.commit();
    }

    return;
}

int EEPROM_Interface::_readEEPROM_int(int address)
{
    byte b[4];

    for (int j = 0; j < 4; j++)
    {
        b[j] = EEPROM.read(address + j);
    }

    int i;
    memcpy(&i, b, 4);

    if (isnan(i))
    {
        i = 0;
    }

    return i;
}

void EEPROM_Interface::_writeEEPROM_float(int address, float f)
{
    byte b[4];
    memcpy(&b, &f, 4);

    for (int i = 0; i < 4; i++)
    {
        EEPROM.write(address + i, b[i]);
        EEPROM.commit();
    }

    return;
}

float EEPROM_Interface::_readEEPROM_float(int address)
{
    byte b[4];

    for (int i = 0; i < 4; i++)
    {
        b[i] = EEPROM.read(address + i);
    }

    float f;
    memcpy(&f, b, 4);

    if (isnan(f))
    {
        f = 0.0f;
    }

    return f;
}