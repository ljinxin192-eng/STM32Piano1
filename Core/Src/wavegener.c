#include "wavegener.h"
#include "gpio.h"
#include "usart.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "tone.h"   // ?????

double Frequency = 0;
static int16_t sinTable[WAVE_TAB_SIZE];
Voice voices[MAX_VOICES];
ADSR adsr = { 0.01f, 0.1f, 0.7f, 0.5f };

float	harmAmp[9] = {
	1.00f,
	0.25f,
	0.80f,
	0.10f,
	0.60f,
	0.05f,
	0.30f,
	0.02f,
	0.15f
};

float	harmDec[9] = {
	1.0f,
	3.0f,
	2.0f,
	5.0f,
	3.5f,
	8.0f,
	4.0f,
	10.0f,
	5.0f
};

void SynthInit(void)
{
	for (int i = 0; i < WAVE_TAB_SIZE; i++){
		float angle = 2.0f * PI * i / WAVE_TAB_SIZE;
		sinTable[i] = (int16_t)(sin(angle) * 32767.0f);
	}
	
	for (int i = 0; i < MAX_VOICES; i++){
		voices[i].active = false;
		voices[i].envelope = 0.0f;
		voices[i].envelopeStage = 0;
		voices[i].envelopeTime = 0.0f;
		voices[i].harmonicTime = 0.0f;
	}
}

void GetFsFromKey(uint8_t note)
{
	Frequency = 440 * pow(2.0, (note - 69) / 12.0);
}

int GetFreeVoice()
{
	for (int i = 0; i < MAX_VOICES; i++)
	{
		if (!voices[i].active) return i;
	}
	return -1;
}

void NoteOn(uint8_t note)
{
	char msg[64];
  snprintf(msg, sizeof(msg), "NoteOn called: note=%d\r\n", note);
  HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 100);
	
	

	int voiceIndex = GetFreeVoice();
	snprintf(msg, sizeof(msg), "Free voice index: %d\r\n", voiceIndex);
  HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 100);
	if (voiceIndex == -1) return;
	
	Voice* voice = &voices[voiceIndex];
	
	GetFsFromKey(note);
	
	voice->delta = (uint32_t)((Frequency * (1ULL << 32)) / SAMPLE_RATE);
	voice->phase = 0;
	voice->active = true;
	voice->envelopeStage = 0;
	voice->envelopeTime = 0.0f;
	voice->harmonicTime = 0.0f;
	voice->note = note;
	voice->envelope = 0.0f;
	
	snprintf(msg, sizeof(msg), "Voice %d activated for note %d, freq=%.2f\r\n", voiceIndex, note, Frequency);
  HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 100);
}

void UpdateEnvelopes()
{
	float dt = 1.0f / SAMPLE_RATE;
	
	for (int i = 0; i < MAX_VOICES; i++){
		if(!voices[i].active) continue;
		
		Voice* voice = &voices[i];
		voice->envelopeTime += dt;
		voice->harmonicTime += dt;
		
		switch (voice->envelopeStage){
			case 0:
				voice->envelope = voice->envelopeTime / adsr.attack;
				if (voice->envelope >= 1.0f){
					voice->envelope = 1.0f;
					voice->envelope = 1.0f;
					voice->envelopeStage = 1;
					voice->envelopeTime = 0.0f;
				}
				break;
				
			case 1:
				voice->envelope = 1.0f - (1.0f - adsr.sustain) * (voice->envelopeTime / adsr.decay);
				if (voice->envelope <= adsr.sustain) {
					voice->envelope = adsr.sustain;
					voice->envelopeStage = 3;
				}
				break;

			case 2:
				break;

			case 3:
				voice->envelope = adsr.sustain * (1.0f - voice->envelopeTime / adsr.release);
				if (voice->envelope <= 0.0f) {
					voice->envelope = 0.0f;
					voice->active = false;
				}
				break;
		}
	}
}

float CalculateHarmonicDecay(float harmonicTime, int harmonicIndex) {
    if (harmonicIndex >= 9) {
        return 0.0f;
    }
    float decayRate = harmDec[harmonicIndex];
		return 1.0f / (1.0f + harmonicTime * decayRate);
}

void SwitchTone(const uint8_t* ampArray, const uint8_t* decArray){
	for(int i = 0; i < 9; i++){
		harmAmp[i] = (float)ampArray[i]/ 100.0f;
	}
	for(int i = 0; i < 9; i++){
		harmDec[i] = (float)decArray[i];
	}
}

static inline float sin_lut(float phase01){
    uint32_t p = (uint32_t)(phase01 * 4294967296.0f);
    uint32_t idx = (p >> 22) & (WAVE_TAB_SIZE - 1);
    uint32_t frac = (p >> 10) & 0xFFF;           
    float y0 = sinTable[idx];
    float y1 = sinTable[(idx+1) & (WAVE_TAB_SIZE - 1)];
    float t = frac * (1.0f/4096.0f);              
    return (y0 + t*(y1 - y0)) * (1.0f/32767.0f);    
}

int16_t SynthGenSample(void) {
    UpdateEnvelopes();

    int32_t sample = 0;

    for (int i = 0; i < MAX_VOICES; i++) {
        if (voices[i].active && voices[i].envelope > 0.001f) {
            Voice* voice = &voices[i];
switch (tone_id) {
            case 0: voice->toneGain = 1.15f; break;  // ??
            case 1: voice->toneGain = 0.65f; break;  // ??
            case 2: voice->toneGain = 0.95f; break;  // ??
            default: voice->toneGain = 1.0f; break;
        }
            float baseFreq = (float)(voice->delta) * SAMPLE_RATE / (float)(1ULL << 32);
            float basePhase = (float)voice->phase / (float)(1ULL << 32);

            float voiceSample = 0.0f;

            for (int harmonic = 0; harmonic < 9; harmonic++) {
                
							float harmonicDecay = CalculateHarmonicDecay(voice->harmonicTime, harmonic);
                float harmonicAmp = harmAmp[harmonic] * harmonicDecay;

                if (harmonicAmp > 0.01f) {
                   float harmonicPhase = basePhase * (harmonic + 1) + harmonic * 0.17f;
                    voiceSample += sin_lut(harmonicPhase) * harmonicAmp;
                }
            }

            if (voice->envelopeTime < 0.02f) {
                static uint32_t noiseSeed = 12345;
                noiseSeed = noiseSeed * 1103515245 + 12345;
                float noise = ((float)(noiseSeed & 0x7FFF) / 32767.0f - 0.5f) * 0.15f;
                float noiseEnvelope = 1.0f - (voice->envelopeTime / 0.02f);
                voiceSample += noise * noiseEnvelope;
            }

           if (voiceSample > 1.0f)  voiceSample = 1.0f;
if (voiceSample < -1.0f) voiceSample = -1.0f;

/* ???? envelope ????? */
int16_t finalSample =
    (int16_t)(voiceSample * voice->envelope * voice->toneGain * 8000.0f);
            sample += finalSample;

            voice->phase += voice->delta;
        }
    }

    if (sample > 32767) sample = 32767;
    if (sample < -32767) sample = -32767;
    
    return (int16_t)sample;
}
