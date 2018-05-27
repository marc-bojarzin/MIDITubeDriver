#include "Led.hpp"

Led::Led(byte pin)
    : pin_(pin)
    , tp0_(millis())
    , status_(led_off)
{
    pinMode(pin_, OUTPUT);
    digitalWrite(pin_, LOW);
}

byte Led::pin() const 
{
    return pin_;
}

void Led::off()
{
    status_ = led_off;
    digitalWrite(pin_, LOW);
}

void Led::on()
{
    status_ = led_on;
    digitalWrite(pin_, HIGH);
}

void Led::blink_slow()
{
    status_ = led_blink_slow;
}

void Led::blink_fast()
{
    status_ = led_blink_fast;
}

void Led::update()
{
    unsigned freq = 0;
    switch(status_) {
    case led_blink_slow: freq = LED_SLOW_FREQ; break;
    case led_blink_fast: freq = LED_FAST_FREQ; break;
    default: return;
    }

    if (freq && (millis() - tp0_ > freq))
    {
        tp0_ = millis();
        digitalWrite(pin_, !digitalRead(pin_));
    }
}

