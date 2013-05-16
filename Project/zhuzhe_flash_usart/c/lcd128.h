#ifndef _lcd_128
#define _lcd_128
//#define BOARD_6
// #define BOARD_6_1
 #define BOARD_6_2
//#define BOARD_6_3
//#define BOARD_7
//#define BOARD_9

// move to h file
#include "stm32f10x.h"
#define DISP_SAVE    0X03
#define DISP_CALL    0X04
#define DISP_TEXT    0X20
#define DISP_RLE 0x27
#define DISP_CLEAR_DISPLAY    0X13
#define DISP_SET_COLOR    0X11
#define DISP_BACK_LIGHT   0X15
#define DISP_HIGH_SPEED   0X01
#define	DISP_RESET        0X01
#define DISP_KEY_ACK      0X09
#define DISP_FULL_COLOR   0x22
#define DISP_DOWNLOAD     0X32
#define DISP_RECALL       0X33
#define FULL_SIZE   (1*1*2)
#define BIT_SW      0X80
#define BIT_ONLINE  0X08
#define BIT_CMDOK   0X04
#define BIT_NACK    0X02
#define BIT_BUSY    0X01

//else than 0~2
#define SCREEN_STAT_IDLE          0x10
#define SCREEN_STAT_CMDOK         0X40
#define SCREEN_STAT_ERR_ONLINE    0x80
#define SCREEN_STAT_ERR_NACK      0x20
#define SCREEN_STAT_ERR_MISSED    0x08

//----------------------------------------------



#define SCREEN_SS6       GPIO_Pin_8 

//#if !defined (BOARD_6) || !defined (BOARD_7) || !defined (BOARD_9) 
//#define BOARD_6
//#endif



#ifdef BOARD_6_1
#define NAME_MAX     6
#define NAME_MIN     1
#define SCREEN_PIN_SS1       GPIO_Pin_3 
#define SCREEN_PIN_SS2       GPIO_Pin_4 
#define SCREEN_PIN_SS3       GPIO_Pin_2 
#define SCREEN_PIN_SS4       GPIO_Pin_0 
#define SCREEN_PIN_SS5       GPIO_Pin_8 
#define SCREEN_PIN_SS6       GPIO_Pin_8 

#define SCREEN_PIN_SS7       GPIO_Pin_1
#define SCREEN_PIN_SS8       GPIO_Pin_9 
#define SCREEN_PIN_SS9       GPIO_Pin_11

#define SCREEN_PORT_SS1  GPIOE
#define SCREEN_PORT_SS2  GPIOE
#define SCREEN_PORT_SS3  GPIOE
#define SCREEN_PORT_SS4  GPIOB
#define SCREEN_PORT_SS5  GPIOA
#define SCREEN_PORT_SS6  GPIOD

#define SCREEN_PORT_SS7  GPIOE
#define SCREEN_PORT_SS8  GPIOB
#define SCREEN_PORT_SS9  GPIOC
#endif

#ifdef BOARD_6_2
#define NAME_MAX     12
#define NAME_MIN     7
#define SCREEN_PIN_SS1       GPIO_Pin_3 
#define SCREEN_PIN_SS2       GPIO_Pin_4 
#define SCREEN_PIN_SS3       GPIO_Pin_2 
#define SCREEN_PIN_SS4       GPIO_Pin_0 
#define SCREEN_PIN_SS5       GPIO_Pin_8 
#define SCREEN_PIN_SS6       GPIO_Pin_8 

#define SCREEN_PIN_SS7       GPIO_Pin_1
#define SCREEN_PIN_SS8       GPIO_Pin_9 
#define SCREEN_PIN_SS9       GPIO_Pin_11

#define SCREEN_PORT_SS1  GPIOE
#define SCREEN_PORT_SS2  GPIOE
#define SCREEN_PORT_SS3  GPIOE
#define SCREEN_PORT_SS4  GPIOB
#define SCREEN_PORT_SS5  GPIOA
#define SCREEN_PORT_SS6  GPIOD

#define SCREEN_PORT_SS7  GPIOE
#define SCREEN_PORT_SS8  GPIOB
#define SCREEN_PORT_SS9  GPIOC
#endif

#ifdef BOARD_6_3
#define NAME_MAX     18
#define NAME_MIN     13
#define SCREEN_PIN_SS1       GPIO_Pin_3 
#define SCREEN_PIN_SS2       GPIO_Pin_4 
#define SCREEN_PIN_SS3       GPIO_Pin_2 
#define SCREEN_PIN_SS4       GPIO_Pin_0 
#define SCREEN_PIN_SS5       GPIO_Pin_8 
#define SCREEN_PIN_SS6       GPIO_Pin_8 

#define SCREEN_PIN_SS7       GPIO_Pin_1
#define SCREEN_PIN_SS8       GPIO_Pin_9 
#define SCREEN_PIN_SS9       GPIO_Pin_11

#define SCREEN_PORT_SS1  GPIOE
#define SCREEN_PORT_SS2  GPIOE
#define SCREEN_PORT_SS3  GPIOE
#define SCREEN_PORT_SS4  GPIOB
#define SCREEN_PORT_SS5  GPIOA
#define SCREEN_PORT_SS6  GPIOD

#define SCREEN_PORT_SS7  GPIOE
#define SCREEN_PORT_SS8  GPIOB
#define SCREEN_PORT_SS9  GPIOC
#endif

#ifdef BOARD_7
#define NAME_MAX     25
#define NAME_MIN     19
#define SCREEN_PIN_SS1       GPIO_Pin_3 
#define SCREEN_PIN_SS2       GPIO_Pin_4 
#define SCREEN_PIN_SS3       GPIO_Pin_2 
#define SCREEN_PIN_SS4       GPIO_Pin_0 
#define SCREEN_PIN_SS5       GPIO_Pin_8 
#define SCREEN_PIN_SS6       GPIO_Pin_8 
#define SCREEN_PIN_SS7       GPIO_Pin_13 

#define SCREEN_PIN_SS8       GPIO_Pin_9 
#define SCREEN_PIN_SS9       GPIO_Pin_11

#define SCREEN_PORT_SS1  GPIOE
#define SCREEN_PORT_SS2  GPIOE
#define SCREEN_PORT_SS3  GPIOE
#define SCREEN_PORT_SS4  GPIOB
#define SCREEN_PORT_SS5  GPIOA
#define SCREEN_PORT_SS6  GPIOD
#define SCREEN_PORT_SS7  GPIOE

#define SCREEN_PORT_SS8  GPIOB
#define SCREEN_PORT_SS9  GPIOC
#endif


#ifdef BOARD_9
#define NAME_MAX     22
#define NAME_MIN     14	
#define SCREEN_PIN_SS1       GPIO_Pin_1
#define SCREEN_PIN_SS2       GPIO_Pin_3 
#define SCREEN_PIN_SS3       GPIO_Pin_4 
#define SCREEN_PIN_SS4       GPIO_Pin_9 
#define SCREEN_PIN_SS5       GPIO_Pin_2 
#define SCREEN_PIN_SS6       GPIO_Pin_0 
#define SCREEN_PIN_SS7       GPIO_Pin_11
#define SCREEN_PIN_SS8       GPIO_Pin_8 
#define SCREEN_PIN_SS9       GPIO_Pin_8 
					   
#define SCREEN_PORT_SS1  GPIOE
#define SCREEN_PORT_SS2  GPIOE
#define SCREEN_PORT_SS3  GPIOE
#define SCREEN_PORT_SS4  GPIOB
#define SCREEN_PORT_SS5  GPIOE
#define SCREEN_PORT_SS6  GPIOB
#define SCREEN_PORT_SS7  GPIOC
#define SCREEN_PORT_SS8  GPIOA
#define SCREEN_PORT_SS9  GPIOD
#endif


#define KEY_NUM      (NAME_MAX-NAME_MIN+1)

#define SCREEN_MISO	 GPIO_Pin_14
#define SCREEN_MOSI	 GPIO_Pin_15
#define SCREEN_SCLK  GPIO_Pin_13




#define SCREEN_PORT GPIOB
//-----------------------------------------------------
void screen_init(void);
void screen_update(char name,char *pdata);
void screen_spi_isp(void);
void screen_key_ack(char name); 
void screen_down(char dispID,char name,char *pdata);
void screen_recall(char name,char dispID);
void screen_highspeed(char name,char *pdata);
void screen_down_rle(char name,char dispID, char *pdata,unsigned int data_length);
//void screen_down_rle_1(char name,char dispID, char *pdata,unsigned int data_length);
void screen_update_rle_l(char name ,char* pdata,uint16_t length);

void screen_update_rle(char name ,char* pdata,uint16_t length);

void screen_backlight(char name, char light);

char screen_trans_noint(char *phead,unsigned int head_len,char *pdata,unsigned int data_len ,char *ptailer,unsigned int tailer_len,char name);

 
void screen_recall_h(char name,char dispID);

void screen_enable(char name);
void screen_disable(char name);

void screen_send_noint(void);
void screen_init_reset_noint(void);
void screen_down_rle_noint(char name,char dispID, char *pdata,unsigned int data_length);

void screen_send_noint_slow(void);

void screen_update_rle_l_noint(char name ,char* pdata,uint16_t length);
void screen_update_rle_all_noint(char name ,char* pdata,uint16_t length);

void screen_save(char name);
void screen_call(char name);
extern struct disp_data *screen_pcmd;
extern char   key_value,key_flag,screen_init_stat[KEY_NUM],key_value2,key_flag2;
extern char   screen_head[20],screen_data[FULL_SIZE],screen_tailer[10];

#define READ_DATA_SIZE 0x2000
extern char   flash_pic[READ_DATA_SIZE],flag_pass_once;
#endif
