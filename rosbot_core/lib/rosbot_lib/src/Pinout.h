#ifndef PINOUT_H
#define PINOUT_H

/**
 * @brief Pin definitions (see schematics)
 * 
 */
#define BUTTON 0      //*< User button */
#define SDA 5         //*< SDA pin for SPI with IMU (MPU6050) */
#define BUZZER 13     //*< Buzzer */
#define SCL 15        //*< SCL pin for SPI with IMU (MPU6050) */
#define INL1 16       //*< Left motor pin 1 */
#define INL2 17       //*< Left motor pin 2 */
#define ENCLA 18      //*< Left motor encoder signal A */
#define ENCLB 19      //*< Left motor encoder signal B */
#define INR1 21       //*< Right motor pin 1 */
#define INR2 22       //*< Right motor pin 1 */
#define ENCRA 23      //*< Right motor encoder signal A */
#define ENCRB 25      //*< Right motor encoder signal A */
#define LED 26        //*< Front LED */
#define SERVO 27      //*< Servo motor signal */
#define DIST 32       //*< Sharp distance sensor */
#define VBAT 33       //*< Battery monitoring */
#define IL 34         //*< Left motor current */
#define IR 35         //*< Right motor current */
#define MOTOR_PWM_0 0 //*< Motor PWM channel for ledcSetup() */
#define MOTOR_PWM_1 1 //*< Motor PWM channel for ledcSetup() */
#define MOTOR_PWM_2 2 //*< Motor PWM channel for ledcSetup() */
#define MOTOR_PWM_3 3 //*< Motor PWM channel for ledcSetup()*/
#define SERVO_CH 4    //*< Servo PWM channel for ledcSetup() */
#define BUZZER_CH 5   //*< Buzzer PWM channel for ledcSetup() */

#endif
