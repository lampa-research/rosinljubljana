#include "Button.h"

/**
 * @brief Construct a new Button object.
 * Configures the pin to be an INPUT_PULLUP.
 */
Button::Button()
{
    pinMode(BUTTON, INPUT_PULLUP);
}

/**
 * @brief Checks whether the button is pressed.
 * 
 * @return true When the button is pressed.
 * @return false When the button is not pressed.
 */
bool Button::pressed()
{
    return digitalRead(BUTTON) == LOW;
}

/**
 * @brief Waits until the button is pressed.
 * 
 */
void Button::wait()
{
    while (!pressed())
    {
    }
    return;
}