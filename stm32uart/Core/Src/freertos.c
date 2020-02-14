/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "GUI.h"
#include "wm.h"
#include "DIALOG.h"
#include "windows.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

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


/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId key;
osThreadId windows;
/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern uint8_t key0,key1,wk_up;   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
extern  void SpeedTest(void);
extern void MX_FATFS_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */
extern WM_HWIN CreateWindow(void);
void key_scan(void const * argument);
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
  /* definition and creation of defaultTask */
//  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
//  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
  
    osThreadDef(www, window, osPriorityNormal, 0, 512);
  windows = osThreadCreate(osThread(www), NULL);
  
  osThreadDef(keyscan, key_scan, osPriorityNormal, 0, 8);
  key = osThreadCreate(osThread(keyscan), NULL);
  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);
    vTaskDelay(500);
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {


  }
  /* USER CODE END StartDefaultTask */
}



/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
  void key_scan(void const * argument){
	for(;;){
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5)==0)		{key0=1;HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);}else {key0=0; HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);}
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15)==0)		{key1=1;HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);}else {key1=0;HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);}
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==1)		 wk_up=1;else wk_up=0;

	  }
  }  


/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
