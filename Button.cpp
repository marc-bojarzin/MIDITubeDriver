#include "Button.hpp"

Button::Button(byte pin)
    : pin_(pin)
    , stable_state_(HIGH)
    , last_state_(HIGH)
    , last_debounce_time_(millis())
{
    pinMode(pin_, INPUT_PULLUP);
}    

byte Button::pin() const
{
    return pin_;
}

byte Button::read()
{
    // Read the state of the input pin into a local variable.
    byte current_state = digitalRead(pin_);

    // If the input changed, due to noise or pressing, reset the debouncing timer.
    if (current_state != last_state_)
    {
        last_debounce_time_ = millis();
    }

    // Safe the last reading for the next invocation.
    last_state_ = current_state;

    // Check again after debounce time has passed.
    if ((millis() - last_debounce_time_) > BUTTON_DEBOUNCE_DURATION)
    {
        // Whatever the reading is, it's there for longer than the 
        // debounce duration. Evaluate any state transition.
        if (current_state != stable_state_)
        {
            stable_state_ = current_state;
            return (stable_state_ == LOW) ? 1 : 2;
        }
    }

    return 0;  // nothing changed or noise
}

byte Button::status() const
{
    return !stable_state_;
}

