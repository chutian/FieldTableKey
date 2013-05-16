#ifndef _SYS_FUNC
#define _SYS_FUNC
#include "stm32f10x.h"	
#include "lcd128.h"
#include "screen_uart.h"
//#include "pic.h"

#include "usart_flash.h"

#define OK_LENGTH 3708
//#define UP_LENGTH 4772
#define XIAOHUI_LENGTH 7570
#define MUSIC_LENGTH 5468
#define UP_LENGTH 1968
#define DOWN_LENGTH 1962
#define LEFT_LENGTH 1844
#define RIGHT_LENGTH 1998
#define SQUARE_LENGTH 1402	
//extern char arrowdown[1962+8],arrowleft[1844+8],arrowright[1998+8],arrowup[1968+8],square[1402+8],test1[6588+8];

void pic_disp(char name,char picid);
#define PIC_NUM 250
extern  const char *pic_index[40];
extern unsigned int pic_len[40];
extern char ini_index[22];
void sys_main(void);

extern char loading[750+8],loading2[1134+8];
extern char  whitepic[514+8];

#endif
