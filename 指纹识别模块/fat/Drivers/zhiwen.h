#include "main.h"
#include "usart.h"

#define CMD_PREFIX 0xAA55
#define RSP_PREFIX 0x55AA
#define CMDDAT_PREFIX 0xA55A
#define RSPDAT_PREFIX 0x5AA5

/*÷∏¡Ó*/
#define CMD_TEST_CONNECTION 0x0001
#define CMD_SET_PARAM 0x0002
#define CMD_GET_PARAM 0x0003
#define CMD_GET_DEVICE_INFO 0x0004
#define CMD_ENTER_IAP_MODE 0x0005
#define CMD_GET_IMAGE 0x0020
#define CMD_FINGER_DETECT 0x0021
#define CMD_UP_IMAGE 0x0022
#define CMD_DOWN_IMAGE 0x0023
#define CMD_SLED_CTRL 0x0024
#define CMD_STORE_CHAR 0x0040
#define CMD_LOAD_CHAR 0x0041
#define CMD_UP_CHAR 0x0042
#define CMD_DOWN_CHAR 0x0043
#define CMD_DEL_CHAR 0x0044
#define CMD_GET_EMPTY_ID 0x0045
#define CMD_GET_STATUS 0x0046
#define CMD_GET_BROKEN_ID 0x0047
#define CMD_GET_ENROLL_COUNT 0x0048
#define CMD_GENERATE 0x0060
#define CMD_MERGE 0x0061
#define CMD_MATCH 0x0062
#define CMD_SEARCH 0x0063
#define CMD_VERIFY 0x0064
#define CMD_SET_MODULE_SN 0x0008
#define CMD_GET_MODULE_SN 0x0009
#define CMD_FP_CANCEL 0x0025
#define CMD_GET_ENROLLED_ID_LIST 0x0049
#define CMD_ENTER_STANDY_STATE 0x000C

/*¥ÌŒÛ*/
#define ERR_SUCCESS 0x00
#define ERR_FAIL 0x01
#define ERR_VERIFY 0x10
#define ERR_IDENTIFY 0x11
#define ERR_TMPL_EMPTY 0x12
#define ERR_TMPL_NOT_EMPTY 0x13
#define ERR_ALL_TMPL_EMPTY 0x14
#define ERR_EMPTY_ID_NOEXIST 0x15
#define ERR_BROKEN_ID_NOEXIST 0x16
#define ERR_INVALID_TMPL_DATA 0x17
#define ERR_DUPLICATION_ID 0x18
#define ERR_BAD_QUALITY 0x19
#define ERR_MERGE_FAIL 0x1A
#define ERR_NOT_AUTHORIZED 0x1B
#define ERR_MEMORY 0x1C
#define ERR_INVALID_TMPL_NO 0x1D
#define ERR_INVALID_PARAM 0x22
#define ERR_GEN_COUNT 0x25
#define ERR_TIME_OUT 0x23
#define ERR_INVALID_BUFFER_ID 0x26
#define ERR_FP_NOT_DETECTED 0x28
#define ERR_FP_CANCEL 0x41


void Command_packet(uint8_t sid,uint8_t did,uint16_t cmd,uint8_t *data);
void Response_packet(uint8_t *sid,uint8_t *did,uint16_t *rcm,uint16_t *ret,uint8_t *buffer,uint8_t *data);
int RX_packet(uint8_t *sid,uint8_t *did,uint16_t *rcm,uint16_t *ret,uint8_t *data);
int Response_Data_Packet(uint8_t *sid,uint8_t *did,uint16_t *rcm,uint16_t *ret,uint8_t *buffer,uint8_t *data);
int Command_Data_Packet(uint8_t sid,uint8_t did,uint16_t cmd,uint8_t *data);
uint8_t zhiwen_init(void);
uint8_t zhiwen_state(void);
void return_Call(void const * argument);
void jiance(void);
void imagebuffer(uint8_t buffer_id);
void merge();
int caiji(void);
void luru(uint8_t id);
void shibie(void);
void cancel(void);
