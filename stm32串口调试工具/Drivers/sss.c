#include "stdio.h"
#include "stm32f1xx_hal.h"

//�������������.c�ļ������
extern UART_HandleTypeDef huart1;
uint8_t ch;
uint8_t ch_r;
//��д�������,�ض���printf���������ڣ���˼����˵printfֱ����������ڣ���Ĭ�����������̨��
/*fputc*/
int fputc(int c, FILE * f)
{
    ch=c;
    HAL_UART_Transmit(&huart1,&ch,sizeof(ch),1000);//���ʹ���
    return c;
}



//�ض���scanf���������� ��˼����˵���ܴ��ڷ����������ݣ���Ĭ���ǽ��ܿ���̨������
/*fgetc*/
int fgetc(FILE * F)    
{
    HAL_UART_Receive(&huart1,&ch_r,sizeof(ch),1000);//����
    return ch_r;
}
