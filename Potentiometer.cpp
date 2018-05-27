#include "Potentiometer.hpp"

Potentiometer::Potentiometer(byte pin)
    : pin_(pin)
    , feedback_(0)
    , value_(0)
    , last_value_(0)
{
    feedback_ = analogRead(pin_);
    value_ = static_cast<int>(feedback_) >> 3;
    last_value_ = value_;
}

byte Potentiometer::pin() const
{ 
    return pin_;
}

bool Potentiometer::update()
{
    sample();
    if (last_value_ == value_)
    {
        return false;
    }
    last_value_ = value_;
    return true;
}

byte Potentiometer::value() const
{
    return value_;
}

void Potentiometer::sample()
{
    float data = analogRead(pin_);
    feedback_ = (data * 0.1 + feedback_ * 0.9);
    value_ = static_cast<int>(feedback_) >> 3;
}

