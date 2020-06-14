#include "Buzzer.h"

/**
 * @brief Construct a new Buzzer object
 * Initializes the ledc channel to be used with the buzzer.
 */
Buzzer::Buzzer()
{
    pinMode(BUZZER, OUTPUT);
    ledcSetup(BUZZER_CH, 0, 10);
    ledcAttachPin(BUZZER, BUZZER_CH);
}

/**
 * @brief Enable buzzer.
 * 
 * @param frequency Tone frequency.
 */
void Buzzer::on(double frequency)
{
    ledcWriteTone(BUZZER_CH, frequency);
}

/**
 * @brief Disable buzzer.
 * 
 */
void Buzzer::off()
{
    ledcWriteTone(BUZZER_CH, 0);
}

/**
 * @brief Perform a beep.
 * 
 * @param frequency Tone frequency.
 * @param ms Duration in milliseconds.
 */
void Buzzer::beep(double frequency, uint32_t ms)
{
    uint32_t start = millis();
    on(frequency);
    while (millis() - start < ms)
    {
    }
    off();
}