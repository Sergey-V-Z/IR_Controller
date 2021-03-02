/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "stm32f1xx_hal.h"

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

//******************
//
// DESCRIPTION:
//  Общие настройки для устройства
//
// CREATED: 13.09.2020, by Ierixon-HP
//
// FILE: main.h
//
typedef struct 
{
   uint32_t BaudRate;
   uint8_t  SlaveAddress;
   
   
}settings_t;

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DE_Pin GPIO_PIN_1
#define DE_GPIO_Port GPIOA
#define IN8_Pin GPIO_PIN_7
#define IN8_GPIO_Port GPIOA
#define IN7_Pin GPIO_PIN_4
#define IN7_GPIO_Port GPIOC
#define IN6_Pin GPIO_PIN_5
#define IN6_GPIO_Port GPIOC
#define IN5_Pin GPIO_PIN_0
#define IN5_GPIO_Port GPIOB
#define IN4_Pin GPIO_PIN_1
#define IN4_GPIO_Port GPIOB
#define IN3_Pin GPIO_PIN_2
#define IN3_GPIO_Port GPIOB
#define IN2_Pin GPIO_PIN_10
#define IN2_GPIO_Port GPIOB
#define IN1_Pin GPIO_PIN_11
#define IN1_GPIO_Port GPIOB
#define B_Pin GPIO_PIN_12
#define B_GPIO_Port GPIOB
#define G_Pin GPIO_PIN_13
#define G_GPIO_Port GPIOB
#define R_Pin GPIO_PIN_14
#define R_GPIO_Port GPIOB
#define OUT1_Pin GPIO_PIN_6
#define OUT1_GPIO_Port GPIOC
#define OUT2_Pin GPIO_PIN_7
#define OUT2_GPIO_Port GPIOC
#define OUT3_Pin GPIO_PIN_8
#define OUT3_GPIO_Port GPIOC
#define OUT4_Pin GPIO_PIN_9
#define OUT4_GPIO_Port GPIOC
#define OUT5_Pin GPIO_PIN_8
#define OUT5_GPIO_Port GPIOA
#define OUT6_Pin GPIO_PIN_9
#define OUT6_GPIO_Port GPIOA
#define OUT7_Pin GPIO_PIN_10
#define OUT7_GPIO_Port GPIOA
#define OUT8_Pin GPIO_PIN_11
#define OUT8_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
