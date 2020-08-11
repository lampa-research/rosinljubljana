#ifndef SETUP_H
#define SETUP_H

#include "Arduino.h"
#include "EEPROM_Interface.h"
#include "Buzzer.h"
#include "Button.h"
#include "IMU.h"

class Setup
{
public:
    Setup(EEPROM_Interface &eeprom_ref, /*Buzzer &buzzer_ref,*/Button &button_ref, IMU &imu_ref) : eeprom(eeprom_ref), /*buzzer(buzzer_ref),*/button(button_ref), imu(imu_ref){};

    void init();
    void loop();

private:
    EEPROM_Interface &eeprom;
    //Buzzer &buzzer;
    Button &button;
    IMU &imu;

    int _menu_level = 0;
    static const int _menu_state_size = 5;
    char _menu_state_selection[_menu_state_size];
    char _menu_state_print[_menu_state_size];
    char _menu_state_print_action = 0;

    void _check();

    void _handleInput();
    void _handleErrorSelection();
    String _readLineSerial();

    //   MENU

    //   lvl 0
    void _menuMain();
    //   lvl 1
    void _menuWIFI();
    void _menuPID();
    void _menuSensors();
    //   lvl 3
    void _menuPIDConstants();

    //   lvl 4
    void _menuEnableCustomPID();

    //   inputs
    void _inputSSID();
    void _inputPASS();
    void _inputROSMaster();

    void _input_PID_Custom(bool x);

    void _input_P_Constant();
    void _input_I_Constant();
    void _input_D_Constant();

    void _inputGyro_Calibration();
    void _inputLIDAR_Backlash();
    void _inputLIDAR_Angle();

    //   navigate
    void _back();
    void _reset();

    //   print
    void _print_PID_Custom();
    void _printMsgSkip();
    void _printMenuMain();
    void _printMenuWIFI();
    void _printMenuSensors();
    void _printMenuPID();
    void _printMenuPIDConstants();
    void _printMenuEnableCustomPID();
    void _printActionMenu();
    void _printActionGyroMenu();
    void _printALL();
};
#endif