#include "tone.h"
#include "wavegener.h"


volatile uint8_t tone_id = 0;



// ???? - ??????
static const uint8_t tone0_amp[9] = {100, 30, 50, 10, 20, 5, 10, 2, 5};
static const uint8_t tone0_dec[9] = {2, 15, 8, 30, 12, 50, 20, 80, 40};

// ???? - ????????
static const uint8_t tone1_amp[9] = {100, 70, 60, 50, 45, 40, 35, 30, 25};
static const uint8_t tone1_dec[9] = {1, 1, 1, 2, 2, 2, 3, 3, 4};

// ???? - ?????,???????
static const uint8_t tone2_amp[9] = {100, 20, 80, 10, 60, 5, 40, 2, 20};
static const uint8_t tone2_dec[9] = {3, 25, 5, 40, 8, 60, 12, 90, 18};



void Tone_Apply(uint8_t id)
{
    switch (id)
    {
    case 0:
        SwitchTone(tone0_amp, tone0_dec);
        break;

    case 1:
        SwitchTone(tone1_amp, tone1_dec);
        break;

    case 2:
        SwitchTone(tone2_amp, tone2_dec);
        break;

    default:
        SwitchTone(tone0_amp, tone0_dec);
        break;
    }
}


void Tone_Init(void)
{
    tone_id = 0;
    Tone_Apply(tone_id);
}
