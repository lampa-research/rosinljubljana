#include "Setup.h"

void Setup::init()
{
    //buzzer.beep(2000, 600);

    Serial.println("\n\n\n\n");
    Serial.println("========================================");
    Serial.println("\n    Welcome to ROSin Ljubljana.    \n");
    Serial.println("========================================");

    eeprom.init();
    imu.begin();

    _reset();

    return;
}

void Setup::loop()
{
    while (!button.pressed())
    {
        _check();
    }

    return;
}

//--- private
void Setup::_check()
{
    _handleInput();
    _menuMain();

    return;
}

String Setup::_readLineSerial()
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

//   handle

void Setup::_handleInput()
{
    if (Serial.available() > 0)
    {
        char c = Serial.read();
        Serial.flush();

        int ic = (int)c - '0';
        if (ic >= 0 && ic < 10)
        {
            _menu_state_selection[_menu_level] = ic;
            _menu_level++;
            Serial.print("You pressed NUMBER:");
            Serial.println(ic);
            Serial.println("........................................");
        }
        else
        {
            Serial.println("\n *** ERROR - Press NUMBER (0-9).\n");
        }
    }

    return;
}

void Setup::_handleErrorSelection()
{
    Serial.println("\n *** ERROR - Selection is not valid.\n");
    _back();

    return;
}

//   menu

void Setup::_menuMain()
{
    switch (_menu_state_selection[0])
    {
    case 0:
        _printMenuMain();
        break;
    case 1:
        _menuWIFI();
        break;
    case 2:
        _menuPID();
        break;
    case 3:
        _menuSensors();
        break;
    case 4:
        _printALL();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

void Setup::_menuWIFI()
{
    switch (_menu_state_selection[1])
    {
    case 0:
        _printMenuWIFI();
        break;
    case 1:
        _inputSSID();
        break;
    case 2:
        _inputPASS();
        break;
    case 3:
        _inputROSMaster();
        break;
    case 4:
        _back();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

void Setup::_menuPID()
{
    switch (_menu_state_selection[1])
    {
    case 0:
        _printMenuPID();
        break;
    case 1:
        _menuPIDConstants();
        break;
    case 2:
        _menuPIDConstants();
        break;
    case 3:
        _menuPIDConstants();
        break;
    case 4:
        _back();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

void Setup::_menuPIDConstants()
{
    switch (_menu_state_selection[2])
    {
    case 0:
        _printMenuPIDConstants();
        break;
    case 1:
        _menuEnableCustomPID();
        break;
    case 2:
        _input_P_Constant();
        break;
    case 3:
        _input_I_Constant();
        break;
    case 4:
        _input_D_Constant();
        break;
    case 5:
        _back();
        break;
    case 6:
        _reset();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

void Setup::_menuEnableCustomPID()
{
    switch (_menu_state_selection[3])
    {
    case 0:
        _printMenuEnableCustomPID();
        break;
    case 1:
        _input_PID_Custom(true);
        break;
    case 2:
        _input_PID_Custom(false);
        break;
    case 3:
        _print_PID_Custom();
        break;
    case 4:
        _back();
        break;
    case 5:
        _reset();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

void Setup::_menuSensors()
{
    switch (_menu_state_selection[1])
    {
    case 0:
        _printMenuSensors();
        break;
    case 1:
        _inputGyro_Calibration();
        break;
    case 2:
        _inputLIDAR_Backlash();
        break;
    case 3:
        _inputLIDAR_Angle();
        break;
    case 4:
        _back();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

void Setup::_back()
{
    for (int i = 0; i < 2; i++)
    {
        _menu_level--;
        _menu_state_selection[_menu_level] = 0;
        _menu_state_print[_menu_level] = 0;
    }
    _menu_state_print_action = 0;

    Serial.println("........................................");

    return;
}

void Setup::_reset()
{
    _menu_level = 0;
    for (int i = 0; i < _menu_state_size; i++)
    {
        _menu_state_selection[i] = 0;
        _menu_state_print[i] = 0;
    }
    _menu_state_print_action = 0;

    Serial.println("........................................");

    return;
}

//   input

void Setup::_inputSSID()
{
    switch (_menu_state_selection[2])
    {
    case 0:
        _printActionMenu();
        break;
    case 1:
        Serial.println("Enter WiFi SSID. (e.g. 'thisIsMyWiFiName')");
        eeprom.setSSID(_readLineSerial());
        _back();
        break;
    case 2:
        Serial.print("SSID: ");
        Serial.println(eeprom.getSSID());
        _back();
        break;
    case 3:
        _back();
        break;
    case 4:
        _reset();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

void Setup::_inputPASS()
{
    switch (_menu_state_selection[2])
    {
    case 0:
        _printActionMenu();
        break;
    case 1:
        Serial.println("Enter wifi password. (e.g. 'thisIsMyWiFiPassword')");
        eeprom.setPASS(_readLineSerial());
        _back();
        break;
    case 2:
        Serial.print("PASS: ");
        Serial.println(eeprom.getPASS());
        _back();
        break;
    case 3:
        _back();
        break;
    case 4:
        _reset();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

void Setup::_inputROSMaster()
{
    switch (_menu_state_selection[2])
    {
    case 0:
        _printActionMenu();
        break;
    case 1:
        Serial.println("Enter ROS server IP. (e.g. '192.168.1.2')");
        eeprom.setROSMaster(_readLineSerial());
        _back();
        break;
    case 2:
        Serial.print("ROS Master IP: ");
        Serial.println(eeprom.getROSMaster());
        _back();
        break;
    case 3:
        _back();
        break;
    case 4:
        _reset();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

void Setup::_input_PID_Custom(bool x)
{
    switch (_menu_state_selection[1])
    {
    case 1:
        eeprom.setMOTOR_PID_CUSTOM("right", x);
        break;
    case 2:
        eeprom.setMOTOR_PID_CUSTOM("left", x);
        break;
    case 3:
        eeprom.setMOTOR_PID_CUSTOM("both", x);
        break;
    }
    _back();

    return;
}

void Setup::_print_PID_Custom()
{
    switch (_menu_state_selection[1])
    {
    case 1:
        Serial.print("Enable custom PID settings: ");
        if (eeprom.getMOTOR_PID_CUSTOM("right"))
        {
            Serial.println("ON");
        }
        else
        {
            Serial.println("OFF");
        }
        break;
    case 2:
        Serial.print("Enable custom PID settings for LEFT motor: ");
        if (eeprom.getMOTOR_PID_CUSTOM("left"))
        {
            Serial.println("ON");
        }
        else
        {
            Serial.println("OFF");
        }

        break;
    case 3:
        Serial.print("Enable custom PID settings for RIGHT motor: ");
        if (eeprom.getMOTOR_PID_CUSTOM("right"))
        {
            Serial.print("ON");
        }
        else
        {
            Serial.print("OFF");
        }
        Serial.print(" and for LEFT motor: ");
        if (eeprom.getMOTOR_PID_CUSTOM("left"))
        {
            Serial.println("ON");
        }
        else
        {
            Serial.println("OFF");
        }
        break;
    }
    _back();

    return;
}

void Setup::_input_P_Constant()
{
    float x = 0.0f;

    switch (_menu_state_selection[3])
    {
    case 0:
        _printActionMenu();
        break;
    case 1:
        Serial.println("Enter P constant. (e.g. '125.75')");
        x = _readLineSerial().toFloat();
        switch (_menu_state_selection[1])
        {
        case 1:
            eeprom.setMOTOR_P("right", x);
            break;
        case 2:
            eeprom.setMOTOR_P("left", x);
            break;
        case 3:
            eeprom.setMOTOR_P("both", x);
            break;
        }
        _back();
        break;
    case 2:
        switch (_menu_state_selection[1])
        {
        case 1:
            Serial.print("P constant for RIGHT motor: ");
            Serial.println(eeprom.getMOTOR_P("right"));
            break;
        case 2:
            Serial.print("P constant for LEFT motor: ");
            Serial.println(eeprom.getMOTOR_P("left"));
            break;
        case 3:
            Serial.print("P constant for RIGHT motor: ");
            Serial.print(eeprom.getMOTOR_P("right"), 2);
            Serial.print(" and for LEFT motor: ");
            Serial.println(eeprom.getMOTOR_P("left"), 2);
            break;
        }
        _back();
        break;
    case 3:
        _back();
        break;
    case 4:
        _reset();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

void Setup::_input_I_Constant()
{
    float x = 0.0f;

    switch (_menu_state_selection[3])
    {
    case 0:
        _printActionMenu();
        break;
    case 1:
        Serial.println("Enter I constant. (e.g. '125.75')");
        x = _readLineSerial().toFloat();
        switch (_menu_state_selection[1])
        {
        case 1:
            eeprom.setMOTOR_I("right", x);
            break;
        case 2:
            eeprom.setMOTOR_I("left", x);
            break;
        case 3:
            eeprom.setMOTOR_I("both", x);
            break;
        }
        _back();
        break;
    case 2:
        switch (_menu_state_selection[1])
        {
        case 1:
            Serial.print("I constant for RIGHT motor: ");
            Serial.println(eeprom.getMOTOR_I("right"));
            break;
        case 2:
            Serial.print("I constant for LEFT motor: ");
            Serial.println(eeprom.getMOTOR_I("left"));
            break;
        case 3:
            Serial.print("I constant for RIGHT motor: ");
            Serial.print(eeprom.getMOTOR_I("right"), 2);
            Serial.print(" and for LEFT motor: ");
            Serial.println(eeprom.getMOTOR_I("left"), 2);
            break;
        }
        _back();
        break;
    case 3:
        _back();
        break;
    case 4:
        _reset();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

void Setup::_input_D_Constant()
{
    float x = 0.0f;

    switch (_menu_state_selection[3])
    {
    case 0:
        _printActionMenu();
        break;
    case 1:
        Serial.println("Enter D constant. (e.g. '0.0035')");
        x = _readLineSerial().toFloat();
        switch (_menu_state_selection[1])
        {
        case 1:
            eeprom.setMOTOR_D("right", x);
            break;
        case 2:
            eeprom.setMOTOR_D("left", x);
            break;
        case 3:
            eeprom.setMOTOR_D("both", x);
            break;
        }
        _back();
        break;
    case 2:
        switch (_menu_state_selection[1])
        {
        case 1:
            Serial.print("D constant for RIGHT motor: ");
            Serial.println(eeprom.getMOTOR_D("right"));
            break;
        case 2:
            Serial.print("D constant for LEFT motor: ");
            Serial.println(eeprom.getMOTOR_D("left"));
            break;
        case 3:
            Serial.print("D constant for RIGHT motor: ");
            Serial.print(eeprom.getMOTOR_D("right"), 2);
            Serial.print(" and for LEFT motor: ");
            Serial.println(eeprom.getMOTOR_D("left"), 2);
            break;
        }
        _back();
        break;
    case 3:
        _back();
        break;
    case 4:
        _reset();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

void Setup::_inputGyro_Calibration()
{
    switch (_menu_state_selection[2])
    {
    case 0:
        _printActionGyroMenu();
        break;
    case 1:
        imu.calcGyroOffsets(true);
        _back();
        break;
    case 2:
        Serial.println("IMU Gyro offsets");
        Serial.print("X: ");
        Serial.println(imu.getGyroXoffset());
        Serial.print("Y: ");
        Serial.println(imu.getGyroYoffset());
        Serial.print("Z: ");
        Serial.println(imu.getGyroZoffset());
        _back();
        break;
    case 3:
        _back();
        break;
    case 4:
        _reset();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

void Setup::_inputLIDAR_Backlash()
{
    float x = 0.0f;

    switch (_menu_state_selection[2])
    {
    case 0:
        _printActionMenu();
        break;
    case 1:
        Serial.println("Enter LIDAR Backlash in radians. (e.g. '0.06')");
        x = _readLineSerial().toFloat();
        eeprom.setLIDAR_Backlash(x);
        _back();
        break;
    case 2:
        Serial.print("LIDAR Backlash: ");
        Serial.print(eeprom.getLIDAR_Backlash());
        Serial.println(" radians");
        _back();
        break;
    case 3:
        _back();
        break;
    case 4:
        _reset();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

void Setup::_inputLIDAR_Angle()
{
    int x = 0.0f;

    switch (_menu_state_selection[2])
    {
    case 0:
        _printActionMenu();
        break;
    case 1:
        Serial.println("Enter LIDAR angle in degrees. (e.g. '90')");
        x = _readLineSerial().toInt();
        eeprom.setLIDAR_Angle(x);
        _back();
        break;
    case 2:
        Serial.print("LIDAR Angle: ");
        Serial.print(eeprom.getLIDAR_Angle());
        Serial.println(" degrees");
        _back();
        break;
    case 3:
        _back();
        break;
    case 4:
        _reset();
        break;
    default:
        _handleErrorSelection();
        break;
    }

    return;
}

//   print

void Setup::_printMsgSkip()
{
    Serial.println("\nPress USER button to exit setup.\n");

    return;
}

void Setup::_printMenuMain()
{
    if (_menu_state_print[0] == 0)
    {
        Serial.println("\nPress NUMBER to enter submenu.");
        Serial.println("1 - WIFI");
        Serial.println("2 - PID");
        Serial.println("3 - Sensors");
        Serial.println("4 - Print ALL settings");
        _printMsgSkip();

        _menu_state_print[0] = 1;
    }

    return;
}

void Setup::_printMenuWIFI()
{
    if (_menu_state_print[1] == 0)
    {
        Serial.println("\nPress NUMBER to enter WIFI submenu.");
        Serial.println("1 - SSID");
        Serial.println("2 - PASS");
        Serial.println("3 - ROS Master");
        Serial.println("4 - Back");
        _printMsgSkip();

        _menu_state_print[1] = 1;
    }

    return;
}

void Setup::_printMenuSensors()
{
    if (_menu_state_print[1] == 0)
    {
        Serial.println("\nPress NUMBER to enter Sensors submenu.");
        Serial.println("1 - IMU Gyro Calibration");
        Serial.println("2 - LIDAR Backlash");
        Serial.println("3 - LIDAR Angle");
        Serial.println("4 - Back");
        _printMsgSkip();

        _menu_state_print[1] = 1;
    }

    return;
}

void Setup::_printMenuPID()
{
    if (_menu_state_print[1] == 0)
    {
        Serial.println("\nPress NUMBER to enter PID controller submenu.");
        Serial.println("1 - Right motor");
        Serial.println("2 - Left motor");
        Serial.println("3 - Right and Left motor");
        Serial.println("4 - Back");
        _printMsgSkip();

        _menu_state_print[1] = 1;
    }

    return;
}

void Setup::_printMenuPIDConstants()
{
    if (_menu_state_print[2] == 0)
    {
        Serial.println("\nPress NUMBER to enter PID controller submenu.");
        Serial.println("1 - Enable custom PID");
        Serial.println("2 - Proportional constant");
        Serial.println("3 - Integral constant");
        Serial.println("4 - Derivative constant");
        Serial.println("5 - Back");
        Serial.println("6 - Main menu");
        _printMsgSkip();

        _menu_state_print[2] = 1;
    }

    return;
}

void Setup::_printMenuEnableCustomPID()
{
    if (_menu_state_print[3] == 0)
    {
        Serial.println("\nPress NUMBER to select custom PID mode.");
        Serial.println("1 - Enable - use Custom constants");
        Serial.println("2 - Disable - use Default constants");
        Serial.println("3 - Print");
        Serial.println("4 - Back");
        Serial.println("5 - Main menu");
        _printMsgSkip();

        _menu_state_print[3] = 1;
    }

    return;
}

void Setup::_printActionMenu()
{
    if (_menu_state_print_action == 0)
    {
        Serial.println("\nPress NUMBER to act.");
        Serial.println("1 - Set");
        Serial.println("2 - Print");
        Serial.println("3 - Back");
        Serial.println("4 - Main menu");
        _printMsgSkip();

        _menu_state_print_action = 1;
    }

    return;
}

void Setup::_printActionGyroMenu()
{
    if (_menu_state_print_action == 0)
    {
        Serial.println("\nPress NUMBER to act.");
        Serial.println("1 - Calibrate");
        Serial.println("2 - Print");
        Serial.println("3 - Back");
        Serial.println("4 - Main menu");
        _printMsgSkip();

        _menu_state_print_action = 1;
    }

    return;
}

void Setup::_printALL()
{
    Serial.println("");
    Serial.println("----------------------------------------");
    Serial.println("All settings in EEPROM.");

    Serial.println("\n--- WIFI");
    Serial.print("SSID: ");
    Serial.println(eeprom.getSSID());
    Serial.print("PASS: ");
    Serial.println(eeprom.getPASS());
    Serial.print("ROS Master IP: ");
    Serial.println(eeprom.getROSMaster());

    Serial.println("\n--- PID for RIGHT motor");
    Serial.print("Enable custom settings: ");
    if (eeprom.getMOTOR_PID_CUSTOM("right"))
    {
        Serial.println("ON");
    }
    else
    {
        Serial.println("OFF");
    }
    Serial.print("P: ");
    Serial.println(eeprom.getMOTOR_P("right"));
    Serial.print("I: ");
    Serial.println(eeprom.getMOTOR_I("right"));
    Serial.print("D: ");
    Serial.println(eeprom.getMOTOR_D("right"));

    Serial.println("\n--- PID for LEFT motor");
    Serial.print("Enable custom settings: ");
    if (eeprom.getMOTOR_PID_CUSTOM("left"))
    {
        Serial.println("ON");
    }
    else
    {
        Serial.println("OFF");
    }
    Serial.print("P: ");
    Serial.println(eeprom.getMOTOR_P("left"));
    Serial.print("I: ");
    Serial.println(eeprom.getMOTOR_I("left"));
    Serial.print("D: ");
    Serial.println(eeprom.getMOTOR_D("left"));

    Serial.println("\n--- LIDAR");
    Serial.print("Backlash: ");
    Serial.print(eeprom.getLIDAR_Backlash());
    Serial.println(" radians");
    Serial.print("Angle: ");
    Serial.print(eeprom.getLIDAR_Angle());
    Serial.println(" degrees");
    Serial.println("----------------------------------------");

    _reset();

    return;
}