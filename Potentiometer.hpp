#ifndef POTENTIOMETER_HPP
#define POTENTIOMETER_HPP

#include <Arduino.h>

/**
 * Potentiometer with a resolution of 7 bits.
 * A simple digital low-pass fiter is used to remove jitter.
 */
class Potentiometer
{
public:
    /// Not default constructible.
    Potentiometer() = delete;

    /// Constructor.
    Potentiometer(byte pin);

    /// Returns the analog input pinnumber.
    byte pin() const;

    /// Takes a new sample and returns 'TRUE' if value changed.
    boolean update();

    /// Returns the last value sampled in range [0..127].
    byte value() const;

private:
    // Takes a new sample and feeds it into the filter.
    void sample();

private:
    // The analog input pin the potentiometer is attached to.
    const byte pin_;

    // The smoothed value of the last iteration.
    float feedback_;

    // The value after filtering.
    byte value_;

    // The last value (to detect changes).
    byte last_value_;
};

#endif // POTENTIOMETER_HPP
