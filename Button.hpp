#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <Arduino.h>

/*
Debounced pushbutton.
Setup:
- pushbutton attached from input pin to GND
- input pins will be configured to use the internal pullup resistor.
*/

// The global debounce duration (in ms). Increase if the output flickers.
#define BUTTON_DEBOUNCE_DURATION 5

class Button 
{
public:
    // Not default constructible.
    Button() = delete;

    // Constructor.
    Button(byte pin);

    // Returns the pin-number the pushbutton is attached to.
    byte pin() const;

    // Reads the input pin and returns ...
    // 0: nothing changed
    // 1: pushbutton pressed
    // 2: pushbutton released
    byte read();

    // Returns the last stable button status.    
    byte status() const;

private:
    // The input pin this Button is attached to.
    const byte pin_;

    // The current stable reading from the input pin.
    byte stable_state_;

    // The previous reading from the input pin.
    byte last_state_;

    // The last time the state was changed, due to noise or pressing.
    unsigned long last_debounce_time_;


};

#endif // BUTTON_HPP
