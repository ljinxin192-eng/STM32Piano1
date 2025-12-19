#ifndef __TONE_H
#define __TONE_H

#include "stdint.h"


extern volatile uint8_t tone_id;


void Tone_Init(void);
void Tone_Apply(uint8_t id);

#endif
