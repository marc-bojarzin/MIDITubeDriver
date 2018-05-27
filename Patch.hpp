#ifndef PATCH_HPP
#define PATCH_HPP

#include <Arduino.h>

// 32 Bits per Patch
struct Patch
{
    byte drive;
    byte tone;
    byte level;
    byte flags;

    Patch()
        : drive(0)
        , tone(0)
        , level(0)
        , flags(0)
    {
    }
};


#endif // PATCH_HPP
