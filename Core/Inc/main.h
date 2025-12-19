/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define NK1_Pin GPIO_PIN_13
#define NK1_GPIO_Port GPIOC
#define NK1_EXTI_IRQn EXTI15_10_IRQn
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define FK1_Pin GPIO_PIN_0
#define FK1_GPIO_Port GPIOA
#define FK2_Pin GPIO_PIN_1
#define FK2_GPIO_Port GPIOA
#define FK3_Pin GPIO_PIN_2
#define FK3_GPIO_Port GPIOA
#define FK4_Pin GPIO_PIN_3
#define FK4_GPIO_Port GPIOA
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define NK4_Pin GPIO_PIN_10
#define NK4_GPIO_Port GPIOD
#define NK4_EXTI_IRQn EXTI15_10_IRQn
#define NK3_Pin GPIO_PIN_11
#define NK3_GPIO_Port GPIOD
#define NK3_EXTI_IRQn EXTI15_10_IRQn
#define NK2_Pin GPIO_PIN_12
#define NK2_GPIO_Port GPIOD
#define NK2_EXTI_IRQn EXTI15_10_IRQn
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define NK12_Pin GPIO_PIN_0
#define NK12_GPIO_Port GPIOD
#define NK12_EXTI_IRQn EXTI0_IRQn
#define NK11_Pin GPIO_PIN_1
#define NK11_GPIO_Port GPIOD
#define NK11_EXTI_IRQn EXTI1_IRQn
#define NK10_Pin GPIO_PIN_2
#define NK10_GPIO_Port GPIOD
#define NK10_EXTI_IRQn EXTI2_IRQn
#define NK9_Pin GPIO_PIN_3
#define NK9_GPIO_Port GPIOD
#define NK9_EXTI_IRQn EXTI3_IRQn
#define NK8_Pin GPIO_PIN_4
#define NK8_GPIO_Port GPIOD
#define NK8_EXTI_IRQn EXTI4_IRQn
#define NK7_Pin GPIO_PIN_5
#define NK7_GPIO_Port GPIOD
#define NK7_EXTI_IRQn EXTI9_5_IRQn
#define NK6_Pin GPIO_PIN_6
#define NK6_GPIO_Port GPIOD
#define NK6_EXTI_IRQn EXTI9_5_IRQn
#define NK5_Pin GPIO_PIN_7
#define NK5_GPIO_Port GPIOD
#define NK5_EXTI_IRQn EXTI9_5_IRQn
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
