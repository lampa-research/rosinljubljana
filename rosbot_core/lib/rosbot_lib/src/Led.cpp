#include "Led.h"

/**
 * @brief Construct a new Led:: Led object
 * Configures the LED pin to be an OUTPUT.
 */
Led::Led()
{
    pinMode(LED, OUTPUT);
}

/**
 * @brief Turns LED on.
 * 
 */
void Led::on()
{
    digitalWrite(LED, HIGH);
}

/**
 * @brief Turns LED off.
 * 
 */
void Led::off()
{
    digitalWrite(LED, LOW);
}