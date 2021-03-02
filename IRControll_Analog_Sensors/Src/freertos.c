/* USER CODE BEGIN Header */
/**
******************************************************************************
* File Name          : freertos.c
* Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "mb.h"
#include "mbport.h"
#include "flash.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim2;
extern ADC_HandleTypeDef hadc1;

extern settings_t settings;
uint16_t sensBuff[8] = {0};
uint8_t sensState = 255; // битовое поле

uint32_t freqSens = 72000000u/30000u; 
uint32_t pwmSens;
volatile uint16_t adc_buffer[1024] = {0};

/* USER CODE END Variables */
osThreadId MainTaskHandle;
osThreadId ModbusHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void mainTask(void const * argument);
void ModBus(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
   *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
   *ppxIdleTaskStackBuffer = &xIdleStack[0];
   *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
   /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
   
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
   /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
   /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
   /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
   /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of MainTask */
  osThreadDef(MainTask, mainTask, osPriorityNormal, 0, 256);
  MainTaskHandle = osThreadCreate(osThread(MainTask), NULL);

  /* definition and creation of Modbus */
  osThreadDef(Modbus, ModBus, osPriorityNormal, 0, 256);
  ModbusHandle = osThreadCreate(osThread(Modbus), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
   /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_mainTask */
/**
* @brief  Function implementing the MainTask thread.
* @param  argument: Not used 
* @retval None
*/
/* USER CODE END Header_mainTask */
void mainTask(void const * argument)
{
  /* USER CODE BEGIN mainTask */
   
   /* Infinite loop */
   for(;;)
   {
      HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adc_buffer, 30);
      HAL_TIM_Base_Start_IT(&htim2);      
      osDelay(1);
   }
  /* USER CODE END mainTask */
}

/* USER CODE BEGIN Header_ModBus */
/**
* @brief Function implementing the Modbus thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ModBus */
void ModBus(void const * argument)
{
  /* USER CODE BEGIN ModBus */
   /* Infinite loop */
   eMBErrorCode eStatus = eMBInit( MB_RTU, settings.SlaveAddress, 3, settings.BaudRate, MB_PAR_NONE );
   eStatus = eMBEnable();
   //HAL_TIM_Base_Start_IT(&htim17);
   for(;;)
   {
      eMBPoll();
      taskYIELD();
   }
  /* USER CODE END ModBus */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
  /* This is called after the conversion is completed */
   if(1){
   //обработать данные из ацп
      // или вычтавить флаг на обработку
   }
}
/*description https://www.freemodbus.org/api/group__modbus__registers.html*/
//0x04
eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
   eMBErrorCode    eStatus = MB_ENOERR;
   
   return eStatus;
}
//0x03 0x06 0x10
eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
   //uint8_t CMD[5] = {0};
   volatile HAL_StatusTypeDef status;
   
   if(usAddress == 0 ){}
   else{usAddress--;} 
   
   eMBErrorCode    eStatus = MB_ENOERR;
   
   switch (eMode)
   {
     case MB_REG_READ:
      {	
         switch (usAddress)
         {
           case 0: //  Stop/Start
            {	
               *(pucRegBuffer++) = sensBuff[0];
               break;
            }
           case 1: // Dir
            {	
               *(pucRegBuffer++) = sensBuff[1];
               break;
            }
           case 2: //Status start/stop
            {	
               *(pucRegBuffer++) = sensBuff[2];
               break;
            }
           case 3: //Status Dir
            {	
               *(pucRegBuffer++) = sensBuff[3];
               break;
            }
           case 4: // RPM
            {	
               *(pucRegBuffer++) = sensBuff[4];             
               break;
            }
           case 5: // 
            {	
               *(pucRegBuffer++) = sensBuff[5];
               break;
            }
           case 6: // 
            {	
               *(pucRegBuffer++) = sensBuff[6];
               break;
            }
           case 7: // 
            {	
               *(pucRegBuffer++) = sensBuff[7];
               break;
            }
           case 8: 
            {	
               //(*(pucRegBuffer) = ) | (*(pucRegBuffer+1))) = settings.BaudRate /10;
               break;
            }
           case 9: 
            {	
               *(pucRegBuffer++) = sensState;
               break;
            }
           case 10: 
            {	
               
               break;
            }
           case 11: 
            {	
               *(pucRegBuffer+1) = settings.BaudRate;
               break;
            }              
           default:
            {	
               eStatus = MB_ENOREG;
               break;
            }
         }
         
         break;
      }
     case MB_REG_WRITE:
      {	
         
         switch (usAddress)
         {
           case 0: //  Stop/Start
            {	
               
               break;
            }
           case 1: // Dir
            {	
               
               break;
            }
           case 2: 
            {	
               
               break;
            }
           case 3: 
            {	
               
               break;
            }
           case 4: // 
            {	
               
               break;
            }
           case 5: // 
            {	
               break;
            }
           case 6: // 
            {	
               
               break;
            }
           case 7: // 
            {	
               break;
            }
           case 8: 
            {	
               settings.BaudRate = ((*(pucRegBuffer)<<8) | (*(pucRegBuffer+1)))*10;
               break;
            }
           case 9: 
            {	
               
               break;
            }
           case 11: 
            {	
               settings.SlaveAddress = *(pucRegBuffer+1);
               break;
            }
           case 0x0F: 
            {	
               FLASH_WriteSettings(settings, StartSettingsAddres);
               break;
            }
           default:
            {	
               eStatus = MB_ENOREG;
               break;
            }
         }
         break;
      }
     default:
      {	
         eStatus = MB_EINVAL;
         break;
      }
   }
   
   return eStatus;
}

// 0x01 0x0f 0x05
eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
   return MB_ENOREG;
}
//0x02
eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
   return MB_ENOREG;
}   


/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/