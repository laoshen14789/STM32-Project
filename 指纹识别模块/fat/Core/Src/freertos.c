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
#include "lcd.h"
#include "24cxx.h" 
#include "sdcard.h"	
#include "ff.h"  
#include "fatfs.h"
#include "mollc.h"	 
#include "usart.h"	
#include "zhiwen.h"	
#include "String.h"	
//#include "GUI.h"	
//#include "exfun.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
 uint8_t key0,key1,wk_up;
/* USER CODE END Includes */
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
 void key_scan(void const * argument);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SAVE_ADDR_BASE 40
/* USER CODE END PD */
extern  uint8_t WriteBuffer[16];
/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
FATFS fs;
FIL file,rea;
uint8_t res=0;
UINT Br,Bw;
char path[4]="0:";
uint8_t testBuffer[]="������ \r\n",read[16];
 extern uint8_t rx_buffer[28];  //�������ݻ���
//uint8_t aRxBuffer;			//�����жϻ���
//uint8_t Uart1_RxBuff[256];		//���ջ���
//uint8_t Uart1_Rx_Cnt = 0;		//���ջ������
//uint8_t	cAlmStr[] = "�������(����256)\r\n";
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
//#define BUFFER_SIZE  100
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId keyTaskHandle;
osThreadId callTaskHandle;
/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
//extern volatile uint8_t rx_len ;  //����һ֡���ݵĳ���
//extern volatile uint8_t recv_end_flag ; //һ֡���ݽ�����ɱ�־
//extern uint8_t rx_buffer[28];  //�������ݻ���
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void SD_Read_Sectorx(uint32_t sec);
extern void MX_FATFS_Init(void);
void MX_FREERTOS_Init(void);
void fat_write(void);
void fat_read(void);
void fat_init(void);
/* (MISRA C 2004 rule 8.1) */
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
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
  
  osThreadDef(key, key_scan, osPriorityNormal, 0, 4);
  keyTaskHandle = osThreadCreate(osThread(key), NULL);
 
//  osThreadDef(retu, return_Call, osPriorityNormal, 0, 128);
//  callTaskHandle = osThreadCreate(osThread(retu), NULL);
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
  /* init code for FATFS */
    //GUI_Init();

	POINT_COLOR=RED; 
	LCD_Clear(WHITE);
    while(zhiwen_init()==0){
		LCD_ShowString(120,1,200,16,16," Error!");
		HAL_Delay(500);					
		LCD_ShowString(120,1,200,16,16,"Please Check! ");
		HAL_Delay(500); 
        LCD_Fill(120,1,240,20,WHITE);
    }

    //fat_init();
    //GUI_DispString("Hello emWin!");
    //Command_packet(0x00,0x00,0x0001,WriteBuffer);
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
//    HAL_UART_Transmit(&huart1,rx_buffer,26,0xff);//���ʹ���
      //zhiwen_init();

//      HAL_Delay(500);
      LCD_ShowString(1,60,200,16,16,"Sid:");
      LCD_ShowString(1,40,200,16,16,"Did:");
      LCD_ShowString(1,20,200,16,16,"Error code:");
      LCD_ShowString(1,1,200,16,16,"Connect state:");
      LCD_ShowString(1,80,200,16,16,"State:");
      LCD_ShowString(1,100,200,16,16,"Result:");
        if(wk_up==1){
            HAL_Delay(20);
            if(wk_up==1){
            //fat_write();
                shibie();
//    memset(WriteBuffer,0x00,14);
//    WriteBuffer[0]=0x00;WriteBuffer[1]=0x00;WriteBuffer[2]=0x01;WriteBuffer[3]=0x00;WriteBuffer[4]=0xD0;WriteBuffer[5]=0x07;
//    Command_packet(0x00,0x00,CMD_SEARCH,WriteBuffer);
    }
}
    if(key1==1)  {
        HAL_Delay(20);
        if(key1==1){
            //fat_read();
            merge();
        }
    }  
    if(key0==1)  {
        HAL_Delay(20);
        if(key0==1){
//            imagebuffer(0x00);
            jiance();

        }
    } 
        taskYIELD ();

  }
  /* USER CODE END StartDefaultTask */
}
 
/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
  void key_scan(void const * argument){
	for(;;){
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5)==0)		key0=1;else key0=0;
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15)==0)		key1=1;else key1=0;
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==1)		wk_up=1;else wk_up=0;
        taskYIELD ();
	  }
  }
  
  void SD_Read_Sectorx(uint32_t sec)
{
	uint8_t *buf;
	uint16_t i;
	buf=mymalloc(512);				//�����ڴ�
	if(SD_ReadDisk(buf,sec,1)==0)	//��ȡ0����������
	{	
		LCD_ShowString(1,190,200,16,16,"USART1 Sending Data...");
		printf("SECTOR 0 DATA:\r\n");
		for(i=0;i<512;i++)printf("%x ",buf[i]);//��ӡsec��������    	   
		printf("\r\nDATA ENDED\r\n");
		//LCD_ShowString(60,190,200,16,16,(char*)buf[i]);
	}
	myfree(buf);//�ͷ��ڴ�	
}
void fat_init(){
    uint32_t sd_size;
    	res=f_mount(&fs,"0:",0);
		   	while(SD_Init())//��ⲻ��SD��
	{
		LCD_ShowString(1,50,200,16,16,"SD Card Error!");
		HAL_Delay(500);					
		LCD_ShowString(1,50,200,16,16,"Please Check! ");
		HAL_Delay(500);
		
	}
	LCD_ShowString(1,50,200,16,16,"SD Card OK!");
	sd_size=SD_GetSectorCount();//�õ�������
	LCD_ShowString(1,70,200,16,16,"SD Card Size:      MB");
	LCD_ShowNum(104,70,sd_size>>11,5,16);//��ʾSD������
		if(res!=FR_OK)  LCD_ShowString(1,90,200,16,16,"error mount");		
        else    LCD_ShowString(1,90,200,16,16,"success mount");
}
void iic_24cxx(uint32_t in,uint32_t *out){
	AT24CXX_WriteLenByte(SAVE_ADDR_BASE+4,in,4); 
	HAL_Delay(200);
	*out=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+4,4);
}

void fat_write(){
           // f_mkdir("0:DATA"); //�����ļ���
		if(f_open(&file,"0:/hello.txt",FA_CREATE_ALWAYS|FA_WRITE)==FR_OK){	
			f_lseek(&file, f_size(&file));//ȷ��д��д�벻�Ḳ��֮ǰ������
			LCD_ShowString(1,110,200,16,16,"success open");
            HAL_Delay(100);
		}
        else   LCD_ShowString(1,110,200,16,16,"open error");		
		if(f_write(&file,testBuffer,sizeof(testBuffer),&Bw)==FR_OK){
			f_close(&file);	//�ǵ�һ��Ҫ�ر��ļ�
			LCD_ShowString(1,130,200,16,16,"success write");
            HAL_Delay(100);
		}
        else   LCD_ShowString(1,130,200,16,16,"error");	
}

void fat_read(){
            f_open(&rea,"0:/hello.txt",FA_READ);
            f_read(&rea,read,sizeof(read),&Br);
            printf("%s",read);
            HAL_Delay(100);
            f_close(&file);	//�ǵ�һ��Ҫ�ر��ļ�
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//    UNUSED(huart);
//if(Uart1_Rx_Cnt >= 255)  //����ж�
//	{
//		Uart1_Rx_Cnt = 0;
//		memset(Uart1_RxBuff,0x00,sizeof(Uart1_RxBuff));
//		HAL_UART_Transmit(&huart1, (uint8_t *)&cAlmStr, sizeof(cAlmStr),0xFFFF);	
//	}
//	else
//	{
//		Uart1_RxBuff[Uart1_Rx_Cnt++] = aRxBuffer;   //��������ת��
//	
//		if((Uart1_RxBuff[Uart1_Rx_Cnt-1] == 0)&&(Uart1_RxBuff[Uart1_Rx_Cnt-2] == 0)) //�жϽ���λ
//		{
//			HAL_UART_Transmit(&huart1, (uint8_t *)&Uart1_RxBuff, Uart1_Rx_Cnt,0xFFFF); //���յ�����Ϣ���ͳ�ȥ
//			Uart1_Rx_Cnt = 0;
//			memset(Uart1_RxBuff,0x00,sizeof(Uart1_RxBuff)); //�������
//		}
//	}
//	
//	HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);   //�ٿ��������ж�


//}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
