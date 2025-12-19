#include "tone.h"
#include "wavegener.h"


volatile uint8_t tone_id = 0;



static const uint8_t tone0_amp[9] = {100, 50, 30, 15, 8, 4, 2, 1, 0};
static const uint8_t tone0_dec[9] = {5, 10, 15, 20, 30, 40, 60, 80, 100};


static const uint8_t tone1_amp[9] = {100, 80, 60, 50, 40, 30, 20, 10, 5};
static const uint8_t tone1_dec[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};


static const uint8_t tone2_amp[9] = {100, 70, 20, 40, 10, 30, 5, 0, 0};
static const uint8_t tone2_dec[9] = {5, 5, 10, 10, 20, 20, 40, 80, 80};



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
