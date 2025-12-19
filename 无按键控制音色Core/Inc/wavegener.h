#ifndef WAVEGENER_H
#define	WAVEGENER_H

#include <stdint.h>
#include <stdbool.h>

#define	SAMPLE_RATE		44100
#define PI 3.14159265358979323846f
#define	MAX_VOICES		12
#define	WAVE_TAB_BITS	10
#define	WAVE_TAB_SIZE	(1u<<WAVE_TAB_BITS)

typedef struct {
    uint32_t phase;
    uint32_t delta;
    uint8_t  harmonic;
    uint16_t amp;
    bool active;
    float envelope;
    int envelopeStage;
    int note;
    float envelopeTime;
    float harmonicTime;
} Voice;

typedef struct {
    float attack;
    float decay;
    float sustain;
    float release;
} ADSR;

void 	SynthInit(void);
void	GetFsFromKey(uint8_t note);
int16_t SynthGenSample(void);
void	SwitchTone(const uint8_t* ampArray, const uint8_t* decArray);

void NoteOn(uint8_t note);
void NoteOff(uint8_t note);
void UpdateEnvelopes(void);
float CalculateHarmonicDecay(float harmonicTime, int harmonicIndex);

#endif
