
#include <MIDI.h>
#include "Button.hpp"
#include "Potentiometer.hpp"
#include "Led.hpp"
#include "Patch.hpp"

//----------------------------------------------------------
// Pins for pushbuttons.

#define PB_EDIT_PIN 11
#define PB_STORE_PIN 10
#define PB_SELECT_PIN 9
#define PB_BYPASS_PIN 8

//----------------------------------------------------------
// Pins for potentiometers

#define POT_DRIVE_PIN A0
#define POT_TONE_PIN A1
#define POT_LEVEL_PIN A2

//----------------------------------------------------------
// Pins for LEDs

#define LED_GREEN_PIN 7
#define LED_RED_PIN 6

//----------------------------------------------------------
// Button objects

Button pb_edit(PB_EDIT_PIN);
Button pb_store(PB_STORE_PIN);
//Button pb_select(PB_SELECT_PIN);
//Button pb_bypass(PB_BYPASS_PIN);

//const int BUTTON_COUNT = 3;
//Button* buttons [] { &pb_edit, &pb_store };

//----------------------------------------------------------
// Potentiometer objects

Potentiometer pot_drive(POT_DRIVE_PIN);
Potentiometer pot_tone(POT_TONE_PIN);
Potentiometer pot_level(POT_LEVEL_PIN);

//const int POTENTIOMETER_COUNT = 1;
//Potentiometer* pots [] { &pot_drive };

//----------------------------------------------------------
// Led objects

Led led_green(LED_GREEN_PIN);
Led led_red(LED_RED_PIN);

//==========================================================

void setup()
{
    Serial.begin(19200);
    Serial.println("MIDITubeDriver");
    led_green.off();
    led_red.off();
}

//----------------------------------------------------------

bool dirty = false;
Patch patch;

enum FSM
{
    state_ready = 1
  , state_edit  = 2
} prog_state = state_ready;

void loop()
{
    led_green.update();
    led_red.update();

    switch(prog_state) 
    {
    case state_ready:
        led_green.off();
        if (pb_edit.read() == 1)
        {
            prog_state = state_edit;
            led_green.blink_slow();
        }
        break;
        
    case state_edit:
        dirty = false;
        if (pb_edit.read() == 1)
        {
            prog_state = state_ready;
            led_green.off();
        }
        if (pot_drive.update())
        {
            patch.drive = pot_drive.value();
            dirty = true;
        }
        if (pot_tone.update())
        {
            patch.tone = pot_tone.value();
            dirty = true;
        }
        if (pot_level.update())
        {
            patch.level = pot_level.value();
            dirty = true;
        }

        if (dirty)
        {
            Serial.print("DRIVE:");
            Serial.print(patch.drive);

            Serial.print(" TONE:");
            Serial.print(patch.tone);

            Serial.print(" LEVEL:");
            Serial.println(patch.level);
        }
        break;
    }
}

//----------------------------------------------------------

