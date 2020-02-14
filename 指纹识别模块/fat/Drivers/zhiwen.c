#include "zhiwen.h"
#include "lcd.h"
#include "cmsis_os.h"
#include "String.h"
static uint8_t ReadBuffer[14]={0};
static uint8_t WriteBuffer[16]={0};

extern uint8_t rx_buffer[28];  //接收数据缓存
static uint8_t id0,id1;
static uint16_t rcm,ret;
int i=0;

void Command_packet(uint8_t sid,uint8_t did,uint16_t cmd,uint8_t *data){

    uint8_t buffer[26]={0};
    uint16_t leng,len;
    leng=sizeof(data);
//    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);//绿灯发送
    buffer[0]=CMD_PREFIX; buffer[1]=CMD_PREFIX>>8;
    buffer[2]=sid; buffer[3]=did;
    buffer[4]=cmd; buffer[5]=cmd>>8;
    buffer[6]=leng; buffer[7]=leng>>8;
    for(int j=8,k=0;j<=23;j++){
        buffer[j]= data[k];
        k++;
    }
    
    for(int i=0;i<26;i++){
        len=len+buffer[i];
    }
    buffer[24]=len;buffer[25]=len>>8;
    HAL_UART_Transmit(&huart1,buffer,sizeof(buffer),0xff);//发送串口
//    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);
}

int RX_packet(uint8_t *sid,uint8_t *did,uint16_t *rcm,uint16_t *ret,uint8_t *data){

    uint16_t stat;
//    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);//红灯接收
//    if(HAL_UART_Receive(&huart1,buffer,sizeof(buffer),0xff)==HAL_OK){//接收串口

        stat=rx_buffer[0] | rx_buffer[1]<<8;

//    HAL_UART_Transmit(&huart1,&rx_buffer[0],26,0xff);//发送串口
    if(stat==RSP_PREFIX){ Response_packet(sid,did,rcm,ret,rx_buffer,data); return 1;}
    if(stat==RSPDAT_PREFIX){ Response_Data_Packet(sid,did,rcm,ret,rx_buffer,data);return 2;}
//    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
//        LCD_ShowNum(130,1,(int)rx_buffer[0],3,16); 

    return 0;
    
}

void Response_packet(uint8_t *sid,uint8_t *did,uint16_t *rcm,uint16_t *ret,uint8_t *buffer,uint8_t *data){
    *sid=buffer[2];  *did=buffer[3];
    *rcm=buffer[4]|buffer[5]<<8;
    *ret=buffer[8]|buffer[9]<<8;
    for(int j=10;j<=23;j++){
        data[j-10]= buffer[j];

    }
    ///LCD_ShowString(1,1,200,16,16,"packet");
//    HAL_Delay(100);
//           LCD_Fill(120,60,130,80,WHITE);
//           LCD_ShowNum(120,60,(int)buffer[4],4,16);
//       HAL_UART_Transmit(&huart1,rcm,sizeof(*rcm),0xff);//发送串口 
//    LCD_Fill(1,1,100,16,WHITE);
}
int Command_Data_Packet(uint8_t sid,uint8_t did,uint16_t cmd,uint8_t *data){
    uint8_t buffer[26]={0};
    uint16_t leng,len;
    leng=sizeof(data);
    buffer[0]=CMDDAT_PREFIX; buffer[1]=CMDDAT_PREFIX>>8;
    buffer[2]=sid; buffer[3]=did;
    buffer[4]=cmd; buffer[5]=cmd>>8;
    buffer[6]=leng; buffer[7]=leng>>8;
    for(int j=8,k=0;j<=23;j++){
        buffer[j]= data[k];
        k++;
    }
    
    for(int i=0;i<26;i++){
        len=len+buffer[i];
    }
    buffer[24]=len;buffer[25]=len>>8;
    HAL_UART_Transmit_DMA(&huart1,buffer,sizeof(buffer));//发送串口
    return 0;
}

int Response_Data_Packet(uint8_t *sid,uint8_t *did,uint16_t *rcm,uint16_t *ret,uint8_t *buffer,uint8_t *data){
    *sid=buffer[2];  *did=buffer[3];
    *rcm=buffer[4]|buffer[5]<<8;
    *ret=buffer[8]|buffer[9]<<8;
    for(int j=10;j<=23;j++){
        data[j-10]= buffer[j];
    }

    //LCD_ShowString(1,20,200,16,16,"Data_Packet");
    HAL_Delay(100);
//    LCD_Fill(1,20,100,36,WHITE);
    return 0;
}

uint8_t zhiwen_init(){
    cancel();
    memset(WriteBuffer,0x00,16);
    Command_packet(0x00,0x00,CMD_TEST_CONNECTION,WriteBuffer);
        HAL_Delay(150);
   if(RX_packet(&id0,&id1,&rcm,&ret,ReadBuffer)==1){
    if(rcm==0x0001&&ret==ERR_SUCCESS){
    LCD_ShowNum(30,60,(int)id0,3,16); 
    LCD_ShowNum(30,40,(int)id1,3,16);
    LCD_ShowString(120,1,200,16,16,"Connect success");
    }
    //return 1;

//   HAL_Delay(100);
    memset(WriteBuffer,0x00,16);
        WriteBuffer[0]=0x04;WriteBuffer[1]=0x01;
        Command_packet(0x00,0x00,CMD_SET_PARAM,WriteBuffer);
        HAL_Delay(150);
if(RX_packet(&id0,&id1,&rcm,&ret,ReadBuffer)==1){
    if(rcm==CMD_SET_PARAM){
        LCD_ShowString(50,80,200,16,16,"Initialize success");
        HAL_Delay(100);
//        LCD_Fill(50,80,240,100,WHITE); 
       return 1; 
    }
    
}
}

    else return 0;

}

void cancel(){
    Command_packet(0x00,0x00,CMD_FP_CANCEL,WriteBuffer);
    HAL_Delay(100);
}


void jiance(){
    LCD_Fill(85,20,240,40,WHITE);
        memset(WriteBuffer,0x00,16);memset(ReadBuffer,0x00,16);
    Command_packet(0x00,0x00,CMD_FINGER_DETECT,WriteBuffer);
    HAL_Delay(50);
    if(RX_packet(&id0,&id1,&rcm,&ret,ReadBuffer)==1){
    if(rcm==CMD_FINGER_DETECT&&ReadBuffer[0]==0x01){
        LCD_Fill(50,80,240,100,WHITE);
        LCD_ShowString(50,80,200,16,16,"Finger success");
        if(caiji()==1){
        HAL_Delay(1000);
            if(caiji()==2){
                HAL_Delay(1000);
                if(caiji()==3) i=0;
            }
        }
        HAL_Delay(200);
        merge();

    }else {LCD_Fill(50,80,240,100,WHITE); LCD_ShowString(50,80,200,16,16,"No finger");}
}
}

int caiji(){

        memset(WriteBuffer,0x00,16);memset(ReadBuffer,0x00,16);
        Command_packet(0x00,0x00,CMD_GET_IMAGE,WriteBuffer);
        HAL_Delay(200);
        if(RX_packet(&id0,&id1,&rcm,&ret,ReadBuffer)==1){
            if(rcm==CMD_GET_IMAGE&&ret==ERR_SUCCESS){
                LCD_Fill(50,80,240,100,WHITE);
        LCD_ShowString(50,80,200,16,16,"Acquisition success");
                imagebuffer(i);
                i++;
                return i;
            }
            else LCD_ShowNum(80,20,(int)ret,3,16);
        } else {LCD_Fill(50,80,240,100,WHITE); LCD_ShowString(50,80,200,16,16,"Acquisition Fail");}
}

void imagebuffer(uint8_t buffer_id){
        memset(WriteBuffer,0x00,16);memset(ReadBuffer,0x00,16);
    LCD_Fill(85,20,240,40,WHITE);
    WriteBuffer[0]=buffer_id;
    Command_packet(0x00,0x00,CMD_GENERATE,WriteBuffer);
    HAL_Delay(300);
    if(RX_packet(&id0,&id1,&rcm,&ret,ReadBuffer)==1){
        if(rcm==CMD_GENERATE&&ret==ERR_SUCCESS){
            LCD_Fill(50,80,240,100,WHITE);
        LCD_ShowString(50,80,200,16,16,"Buffer success");
        }
        else  LCD_ShowNum(80,20,(int)ret,4,16);
    }else {LCD_Fill(50,80,240,100,WHITE); LCD_ShowString(50,80,200,16,16,"Buffer Fail");}
}


void merge(){
    memset(WriteBuffer,0x00,16);memset(ReadBuffer,0x00,16);
    WriteBuffer[0]=0x00;WriteBuffer[1]=0x00;WriteBuffer[2]=0x03;
    Command_packet(0x00,0x00,CMD_MERGE,WriteBuffer);
    HAL_Delay(300);
        if(RX_packet(&id0,&id1,&rcm,&ret,ReadBuffer)==1){
            if(rcm==CMD_MERGE&&ret==ERR_SUCCESS){
        LCD_ShowString(50,80,200,16,16,"Merge success");
                HAL_Delay(100);
                luru(0x03);
            }else LCD_ShowNum(80,20,(int)ret,4,16);
        }else {LCD_Fill(50,80,240,100,WHITE); LCD_ShowString(50,80,200,16,16,"Merge Fail");}
}

void luru(uint8_t id){
    memset(WriteBuffer,0x00,16);memset(ReadBuffer,0x00,16);
    WriteBuffer[0]=id;WriteBuffer[1]=0x00;WriteBuffer[2]=0x00;WriteBuffer[3]=0x00;
    Command_packet(0x00,0x00,CMD_STORE_CHAR,WriteBuffer);
    HAL_Delay(500);
        if(RX_packet(&id0,&id1,&rcm,&ret,ReadBuffer)==1){
            if(rcm==CMD_STORE_CHAR&&ret==ERR_SUCCESS){
                LCD_ShowString(50,80,200,16,16,"Save success");
                LCD_ShowNum(50,100,(int)id,4,16);
                LCD_ShowNum(80,100,(int)ReadBuffer[1],4,16);
            }else LCD_ShowNum(80,20,(int)ret,4,16);
        }else {LCD_Fill(50,80,240,100,WHITE); LCD_ShowString(50,80,200,16,16,"Save Fail");}
}

void return_Call(void const * argument){

    for(;;){

    RX_packet(&id0,&id1,&rcm,&ret,ReadBuffer);
//        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);
//        osDelay(500);
//        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);
        taskYIELD ();
        } 
    }

void shibie(){
    cancel();
    LCD_Fill(50,100,240,120,WHITE);
    LCD_Fill(85,20,240,40,WHITE);
        memset(WriteBuffer,0x00,16);memset(ReadBuffer,0x00,16);//检测手指
    Command_packet(0x00,0x00,CMD_FINGER_DETECT,WriteBuffer);
    HAL_Delay(50);
    if(RX_packet(&id0,&id1,&rcm,&ret,ReadBuffer)==1){
    if(rcm==CMD_FINGER_DETECT&&ReadBuffer[0]==0x01){
        LCD_Fill(50,80,240,100,WHITE);
        LCD_ShowString(50,80,200,16,16,"Finger success");
/************************************************************************************************/        
        memset(WriteBuffer,0x00,16);memset(ReadBuffer,0x00,16);//存入imagebuffer0
        Command_packet(0x00,0x00,CMD_GET_IMAGE,WriteBuffer);
        HAL_Delay(200);
        if(RX_packet(&id0,&id1,&rcm,&ret,ReadBuffer)==1){
            if(rcm==CMD_GET_IMAGE&&ret==ERR_SUCCESS){
                LCD_Fill(50,80,240,100,WHITE);
        LCD_ShowString(50,80,200,16,16,"Acquisition success");
/*******************************************************************************************/                
       
    LCD_Fill(85,20,240,40,WHITE);
    memset(WriteBuffer,0x00,16);memset(ReadBuffer,0x00,16);//存到rambuffer0 
    WriteBuffer[0]=0x00;
    Command_packet(0x00,0x00,CMD_GENERATE,WriteBuffer);
    HAL_Delay(500);
    if(RX_packet(&id0,&id1,&rcm,&ret,ReadBuffer)==1){
        if(rcm==CMD_GENERATE&&ret==ERR_SUCCESS){
            LCD_Fill(50,80,240,100,WHITE);
        LCD_ShowString(50,80,200,16,16,"Buffer success");
/**************************************************************************************/            
    memset(WriteBuffer,0x00,16);memset(ReadBuffer,0x00,16);//比对
    WriteBuffer[0]=0x00;WriteBuffer[1]=0x00;WriteBuffer[2]=0x01;WriteBuffer[3]=0x00;WriteBuffer[4]=0x10;WriteBuffer[5]=0x00;
    Command_packet(0x00,0x00,CMD_SEARCH,WriteBuffer);
    HAL_Delay(100);
            ret=0;
        if(RX_packet(&id0,&id1,&rcm,&ret,ReadBuffer)==1){
            if(rcm==CMD_SEARCH&&ret==ERR_SUCCESS){
                LCD_ShowNum(50,100,(int)ReadBuffer[0],4,16);
                LCD_ShowNum(100,100,(int)ReadBuffer[2],4,16);
        LCD_ShowString(50,80,200,16,16,"Verief success");
/***************************************************************************************/
            }else { LCD_ShowNum(80,20,(int)ret,4,16);LCD_Fill(50,80,240,100,WHITE); LCD_ShowString(50,80,200,16,16,"Verief Fail");}
        }else {LCD_Fill(50,80,240,100,WHITE); LCD_ShowString(50,80,200,16,16,"Fail");}
/**********************************************************************************************/                        
        }
        else  LCD_ShowNum(80,20,(int)ret,4,16);
    }else {LCD_Fill(50,80,240,100,WHITE); LCD_ShowString(50,80,200,16,16,"Buffer Fail");}
 /***********************************************************************************************/                     
            }
            else LCD_ShowNum(80,20,(int)ret,3,16);
        } else {LCD_Fill(50,80,240,100,WHITE); LCD_ShowString(50,80,200,16,16,"Acquisition Fail");}
/*************************************************************************************************/     
    }else {LCD_Fill(50,80,240,100,WHITE); LCD_ShowString(50,80,200,16,16,"No finger");}
}
}
    







