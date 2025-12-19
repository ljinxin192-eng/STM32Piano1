#include "audiodma.h"
#include "i2s.h"
#include "usart.h"
#include <stdio.h>
#include "wavegener.h"
#include "stm32f4xx_hal.h"
#include <string.h>

#define AUDIO_BLK_SZ   1024
static uint16_t audioBuf[2][AUDIO_BLK_SZ] __attribute__((section(".ram2")));
static volatile uint32_t prodIdx = 0;
static volatile uint32_t bufIdx  = 0;

static void fillBlock(uint16_t *blk)
{
    for (uint32_t i = 0; i < AUDIO_BLK_SZ; ++i){
        int16_t sample = SynthGenSample();
        blk[i] = (uint16_t)(sample + 0x8000);
		}
}

void audioInit(void)
{
    char msg[64];
    snprintf(msg, sizeof(msg), "Filling audio buffers...\r\n");
    HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 100);
    
    fillBlock(audioBuf[0]);
    fillBlock(audioBuf[1]);
    
    snprintf(msg, sizeof(msg), "Starting I2S DMA transfer...\r\n");
    HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 100);
    
    HAL_StatusTypeDef status = HAL_I2S_Transmit_DMA(&hi2s2, (uint16_t *)audioBuf[0], AUDIO_BLK_SZ * 2);
    
    snprintf(msg, sizeof(msg), "I2S DMA status: %d\r\n", status);
    HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 100);
}


void audioSchedule(void)
{
    bufIdx ^= 1;
    fillBlock(audioBuf[bufIdx]);
}
