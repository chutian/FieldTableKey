#include "lcd128.h"
//--------------------------------------------------------------------
//hardware relate
void screen_init_spi(void);
void screen_init_gpio(void);
void screen_init_rcc(void);
void screen_init_nvic(void);
//void screen_enable(char name);
//void screen_disable(char name);
char screen_spi_getdata(void);
void screen_spi_send(char data);

//-------------------------------------------------------
struct disp_data
{
   volatile char name;
   volatile char *pdata[3];         //0:head 1:data 2:tailer 
   volatile unsigned int length[3];   //0:head_length 1:data_length 2:tailer_length	 CAN NOT BE ZERO
   volatile unsigned int send_num;
   volatile unsigned char stat;
};
GPIO_TypeDef *  screen_port_ss[9]={SCREEN_PORT_SS1,SCREEN_PORT_SS2,SCREEN_PORT_SS3,SCREEN_PORT_SS4,SCREEN_PORT_SS5,SCREEN_PORT_SS6,SCREEN_PORT_SS7,SCREEN_PORT_SS8,SCREEN_PORT_SS9}; 
  uint16_t      screen_pin_ss[9]={SCREEN_PIN_SS1,SCREEN_PIN_SS2,SCREEN_PIN_SS3,SCREEN_PIN_SS4,SCREEN_PIN_SS5,SCREEN_PIN_SS6,SCREEN_PIN_SS7,SCREEN_PIN_SS8,SCREEN_PIN_SS9};
 static uint16_t time_out=0;
 struct disp_data screen_cmd_data={0};
struct disp_data *screen_pcmd=&screen_cmd_data;
char data_buff[10]={0},flag_pass_once=0;
const char INIT_STRING[8]="LOADING";


char   flash_pic[READ_DATA_SIZE];

char flag,flag_high_speed=0;
char   key_value=0,key_flag=0,key_prestat[KEY_NUM]={0},key_prestat2[KEY_NUM]={0},screen_init_stat[KEY_NUM], key_value2=0,key_flag2=0;
char   screen_head[20],screen_tailer[10],screen_data[FULL_SIZE];
static SPI_InitTypeDef   SPI_InitStructure;

uint16_t key_dly[KEY_NUM]={0};

void screen_init_reset(void);



 char flag=0;


void screen_save(char name)
{
    while(screen_pcmd->stat<3);// return;
    screen_pcmd->stat=0;
    screen_pcmd->name=name;
    screen_head[0]=DISP_SAVE; screen_head[1]=~DISP_SAVE; screen_head[2]=0; screen_head[3]=0;
	data_buff[0]=0;data_buff[1]=0;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=data_buff;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=2;screen_pcmd->length[1]=2;screen_pcmd->length[2]=3;
    screen_pcmd->send_num=0;
    screen_enable(name);
    screen_spi_send(screen_pcmd->pdata[0][0]);
}
void screen_call(char name)
{
    while(screen_pcmd->stat<3);// return;
    screen_pcmd->stat=0;
    screen_pcmd->name=name;
    screen_head[0]=DISP_CALL; screen_head[1]=~DISP_CALL; screen_head[2]=0; screen_head[3]=0;
	data_buff[0]=0;data_buff[1]=0;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=data_buff;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=2;screen_pcmd->length[1]=2;screen_pcmd->length[2]=3;
    screen_pcmd->send_num=0;
    screen_enable(name);
    screen_spi_send(screen_pcmd->pdata[0][0]);
}

void screen_update_rle_all_noint(char name ,char* pdata,uint16_t length)
{
uint16_t i=0;
    while(screen_pcmd->stat<3);// return;
    screen_pcmd->stat=0;
    screen_pcmd->name=name;
    screen_head[0]=DISP_RLE; screen_head[1]=~DISP_RLE; screen_head[2]=(length+4)/256; screen_head[3]=(length+4)%256;
    screen_head[4]=0;               screen_head[5]=0;                screen_head[6]=128;             screen_head[7]=128;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=pdata;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=8;screen_pcmd->length[1]=length;screen_pcmd->length[2]=3;
    screen_pcmd->send_num=0;
    screen_send_noint_slow();
	
	for(i=0;i<10000;i++);	

}

void screen_update_rle_l_noint(char name ,char* pdata,uint16_t length)
{
uint16_t i=0;
    while(screen_pcmd->stat<3);// return;
    screen_pcmd->stat=0;
    screen_pcmd->name=name;
    screen_head[0]=DISP_RLE; screen_head[1]=~DISP_RLE; screen_head[2]=(length+4)/256; screen_head[3]=(length+4)%256;
    screen_head[4]=0;               screen_head[5]=48;                screen_head[6]=128;             screen_head[7]=32;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=pdata;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=8;screen_pcmd->length[1]=length;screen_pcmd->length[2]=3;
    screen_pcmd->send_num=0;
    screen_send_noint_slow();
	
	for(i=0;i<10000;i++);	

}


void screen_down_rle_noint(char name,char dispID, char *pdata,unsigned int data_length)
{
  volatile  uint16_t i=0;
	while(screen_pcmd->stat<3);
	for(i=0;i<10000;i++);	 
        screen_pcmd->stat=0; 
    screen_head[0]=DISP_DOWNLOAD; screen_head[1]=~DISP_DOWNLOAD; screen_head[2]=(data_length+4)/256; 
	screen_head[3]=(data_length+4)%256;
    screen_head[4]=128; screen_head[5]=128; screen_head[6]=dispID; screen_head[7]=0X03;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=pdata;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=8;screen_pcmd->length[1]=data_length;screen_pcmd->length[2]=3;  
    screen_pcmd->name=name;	
    screen_send_noint_slow();
}

void screen_init_reset_noint(void)
{
    char i,temp,data[2]={00,0x11};
	volatile int dly=0;

    screen_head[0]=DISP_RESET; screen_head[1]=~DISP_RESET; screen_head[2]=0; screen_head[3]=2;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=data;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=4;screen_pcmd->length[1]=2;screen_pcmd->length[2]=3;
    for(i=NAME_MIN;i<=NAME_MAX;i++)
	{
        screen_pcmd->name=i;
		screen_send_noint();
		screen_init_stat[i-NAME_MIN]=screen_pcmd->stat;
   }
    screen_head[0]=DISP_SET_COLOR; screen_head[1]=~DISP_SET_COLOR; screen_head[2]=0; screen_head[3]=3;
	data_buff[0]=15;data_buff[1]=0XFF;data_buff[2]=0XFF;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=data;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=4;screen_pcmd->length[1]=3;screen_pcmd->length[2]=3;
       for(i=NAME_MIN;i<=NAME_MAX;i++)
	{
        screen_pcmd->name=i;	
		screen_send_noint(); 
   }
   
    screen_head[0]=DISP_CLEAR_DISPLAY; screen_head[1]=~DISP_CLEAR_DISPLAY; screen_head[2]=0; screen_head[3]=1;
	data_buff[0]=15;data_buff[1]=0XFF;data_buff[2]=0XFF;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=data;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=4;screen_pcmd->length[1]=1;screen_pcmd->length[2]=3;
       for(i=NAME_MIN;i<=NAME_MAX;i++)
	{
        screen_pcmd->name=i;
		screen_send_noint();
   }

}
void screen_send_noint_slow()
{
   volatile unsigned int i,k,temp=0;
   __disable_irq();
  	screen_enable(screen_pcmd->name);

		  for(temp=0;temp<3000;temp++);	
	flag_high_speed=1;

	do{			
	
		  for(temp=0;temp<3000;temp++);
	 SPI_I2S_SendData(SPI2,0x00); 
	 while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	 k=screen_spi_getdata();
	 }while(k&BIT_BUSY);

	for(i=0;i<screen_pcmd->length[0];i++)
	{
	  do{ 	  
		  for(temp=0;temp<3000;temp++);
	      SPI_I2S_SendData(SPI2,screen_pcmd->pdata[0][i]); 
	      while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
		  k=screen_spi_getdata();
		  }while(k&BIT_BUSY); 
	}  
	for(i=0;i<screen_pcmd->length[1];i++)
	{
	  do{  
		  for(temp=0;temp<3000;temp++);
	      SPI_I2S_SendData(SPI2,screen_pcmd->pdata[1][i]); 
	      while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
		  k=screen_spi_getdata();
		  }while(k&BIT_BUSY); 
	}
	for(i=0;i<screen_pcmd->length[2];i++)
	{
	  do{ 
		  for(temp=0;temp<3000;temp++);
	      SPI_I2S_SendData(SPI2,screen_pcmd->pdata[2][i]); 
//	   screen_spi_send(screen_head[i]);
	      while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
		  k=screen_spi_getdata(); 
		  }while(k&BIT_BUSY); 
	}
	screen_pcmd->stat=(k<<4)+0x08;
	flag_high_speed=0;

		do{
	 for(temp=0;temp<3000;temp++);
	 SPI_I2S_SendData(SPI2,0x00); 
	 while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	 k=screen_spi_getdata();
	 }while(k&BIT_BUSY); 
   		  for(temp=0;temp<3000;temp++);

	screen_disable(screen_pcmd->name);
   __enable_irq();
   		  for(temp=0;temp<3000;temp++);




}
void screen_send_noint()
{
   volatile unsigned int i,k,temp=0;
   __disable_irq();
  	screen_enable(screen_pcmd->name);

	 for(temp=0;temp<250;temp++);
	 	
	flag_high_speed=1;

	do{
	 for(temp=0;temp<250;temp++);
	 SPI_I2S_SendData(SPI2,0x00); 
	 while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	 k=screen_spi_getdata();
	 }while(k&BIT_BUSY);

	for(i=0;i<screen_pcmd->length[0];i++)
	{
	  do{ 	  
		  for(temp=0;temp<250;temp++);
	      SPI_I2S_SendData(SPI2,screen_pcmd->pdata[0][i]); 
	      while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
		  k=screen_spi_getdata();
		  }while(k&BIT_BUSY); 
	}  
	for(i=0;i<screen_pcmd->length[1];i++)
	{
	  do{  
		  for(temp=0;temp<250;temp++);
	      SPI_I2S_SendData(SPI2,screen_pcmd->pdata[1][i]); 
	      while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
		  k=screen_spi_getdata();
		  }while(k&BIT_BUSY); 
	}
	for(i=0;i<screen_pcmd->length[2];i++)
	{
	  do{ 
		  for(temp=0;temp<250;temp++);
	      SPI_I2S_SendData(SPI2,screen_pcmd->pdata[2][i]); 
//	   screen_spi_send(screen_head[i]);
	      while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
		  k=screen_spi_getdata(); 
		  }while(k&BIT_BUSY); 
	}
	screen_pcmd->stat=(k<<4)+0x08;
	flag_high_speed=0;

		do{
		 for(temp=0;temp<250;temp++);
	 SPI_I2S_SendData(SPI2,0x00); 
	 while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	 k=screen_spi_getdata();
	 }while(k&BIT_BUSY);
  
	 for(temp=0;temp<250;temp++);
	screen_disable(screen_pcmd->name);
	 for(temp=0;temp<250;temp++);
   __enable_irq();




}
void screen_init(void)													 
{
//		char a[10]={0},b=0,c[10]={0x09,0xf6,0x0,0x0,0x55,0xaa,0x0},e[10]={0x22,0xdd,FULL_SIZE/256,(FULL_SIZE%256),0,0,128,128},
//             f[4]={0x55,0xaa,0x00,0x00};
//        unsigned int i,color=1000;
//volatile unsigned int dly;
   screen_init_rcc();         //配置按键屏的外设
   screen_init_gpio();        //初始化按键屏的GPIO
   screen_init_nvic();        //配置按键屏中断模式
   screen_init_spi();         //初始化SPI总线
//	screen_init_reset();
   screen_init_reset_noint();    //初始化按键屏相关参数
}

void screen_backlight(char name, char light)
{
    volatile uint16_t i=0;
	while(screen_pcmd->stat<3);	
        screen_pcmd->stat=0;
        screen_pcmd->name=name;
    screen_head[0]=0;screen_head[1]=DISP_BACK_LIGHT; screen_head[2]=~DISP_BACK_LIGHT; screen_head[3]=0; screen_head[4]=2;
	data_buff[0]=light;data_buff[1]=0;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;screen_tailer[3]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=data_buff;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=5;screen_pcmd->length[1]=2;screen_pcmd->length[2]=4;
        screen_pcmd->send_num=0;
        screen_enable(name);
		for(i=0;i<1000;i++);
        screen_spi_send(screen_pcmd->pdata[0][0]);  
}
void screen_highspeed(char name,char *pdata)
{
	  volatile unsigned int i,j=0;
	  volatile char k=0;
	while(screen_pcmd->stat<3);
        screen_pcmd->name=name;
    screen_head[0]=DISP_HIGH_SPEED; screen_head[1]=~DISP_HIGH_SPEED; screen_head[2]=0; screen_head[3]=2;
	screen_head[4]=1;	screen_head[5]=0X01;screen_head[6]=0x55;screen_head[7]=0xaa;screen_head[8]=0x00;
	screen_enable(name);
	flag_high_speed=1;
	for(i=0;i<9;i++)
	{
	  do{ 
	  
//	      SPI_I2S_SendData(SPI2,screen_head[i]); 
	   screen_spi_send(screen_head[i]);
	  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	  
//		  for(i=0;i<1000;i++);
		  j=screen_spi_getdata();
		  }while(j&BIT_BUSY); 
	}
	for(i=0;i<2500;i++);
	k=pdata[0];
	for(i=0;i<FULL_SIZE;i++)
	{
	      SPI_I2S_SendData(SPI2,k);
		  k=pdata[i+1];
	      while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
//		  pdata[i]=0xaa;
//		  pdata[i]=screen_spi_getdata();
//		  for(i=0;i<1;i++);
	}
	
	for(i=0;i<250;i++);
	screen_disable(name);
	for(i=0;i<250;i++);
	screen_enable(name);
	for(i=0;i<1000;i++);
	screen_disable(name);
	for(i=0;i<1000;i++); 
	screen_enable(name); 
	for(i=0;i<1000;i++); 
	screen_disable(name);
	flag_high_speed=0;

}
void screen_recall_h(char name,char  dispID)
{
	volatile uint16_t i=0,j=0;

	while(screen_pcmd->stat<3);	 
        screen_pcmd->stat=0;
        screen_enable(name);  
    screen_head[0]=DISP_RECALL; screen_head[1]=~DISP_RECALL; screen_head[2]=0; screen_head[3]=3;
	screen_head[4]=0;	screen_head[5]=0;	screen_head[6]=dispID;
    screen_tailer[7]=0x55;screen_tailer[8]=0xaa;screen_tailer[9]=0x00;
	flag_high_speed=1;
	for(i=0;i<10;i++)
	{
	  do{ 
	  
//	      SPI_I2S_SendData(SPI2,screen_head[i]); 	
	   screen_spi_send(screen_head[i]);	
	  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);    
		  for(i=0;i<1000;i++);
	  
		  j=screen_spi_getdata();
		  }while(j&BIT_BUSY); 
	}
	
        screen_disable(name);  
	flag_high_speed=0; 
        screen_pcmd->stat=3;

}
void screen_recall(char name,char dispID)
{
	volatile uint16_t i=0;

	while(screen_pcmd->stat<3);
        screen_pcmd->name=name;
		
        screen_enable(name);
    screen_head[0]=0x00;screen_head[1]=DISP_RECALL; screen_head[2]=~DISP_RECALL; screen_head[3]=0; screen_head[4]=3;
	data_buff[0]=0;	data_buff[1]=0;	data_buff[2]=dispID;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=data_buff;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=5;screen_pcmd->length[1]=3;screen_pcmd->length[2]=3;
        screen_pcmd->stat=0;
        screen_pcmd->send_num=0;
 //       screen_enable(name);
//		for(i=0;i<50;i++);
        screen_spi_send(screen_pcmd->pdata[0][0]);  
}
//void screen_down_rle_1(char name,char dispID, char *pdata,unsigned int data_length)
//{
//   uint16_t i=0;
//	while(screen_pcmd->stat<3);	 
//        screen_pcmd->stat=0;
//        screen_pcmd->name=name;	 
//    screen_head[0]=DISP_DOWNLOAD; screen_head[1]=~DISP_DOWNLOAD; screen_head[2]=(data_length+4)/256; screen_head[3]=(data_length+4)%256;
//    screen_head[4]=128; screen_head[5]=128; screen_head[6]=dispID; screen_head[7]=0X03;
//    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
//    screen_pcmd->pdata[0]=screen_head;
//    screen_pcmd->pdata[1]=pdata;
//    screen_pcmd->pdata[2]=screen_tailer;
//    screen_pcmd->length[0]=8;screen_pcmd->length[1]=data_length;screen_pcmd->length[2]=3;
//        screen_pcmd->send_num=0;   
//		for(i=0;i<100;i++);
//        screen_enable(name);
//		for(i=0;i<100;i++);
//        screen_spi_send(screen_pcmd->pdata[0][0]);  
//}
void screen_down_rle(char name,char dispID, char *pdata,unsigned int data_length)
{
   uint16_t i=0;
   
	while(screen_pcmd->stat<3);	 
        screen_pcmd->stat=0;
        screen_pcmd->name=name;	 
    screen_head[0]=0x0;screen_head[1]=DISP_DOWNLOAD; screen_head[2]=~DISP_DOWNLOAD; screen_head[3]=(data_length+4)/256; 
	screen_head[4]=(data_length+4)%256;
    screen_head[5]=128; screen_head[6]=128; screen_head[7]=dispID; screen_head[8]=0X03;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=pdata;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=9;screen_pcmd->length[1]=data_length;screen_pcmd->length[2]=3;
//----------------------
//    screen_trans_noint(screen_head,8,pdata,data_length,screen_tailer,3,name);
//	screen_pcmd->stat=screen_trans_noint(screen_head,8,pdata,data_length,screen_tailer,3,name);
        screen_pcmd->send_num=0;   
		for(i=0;i<10000;i++);
        screen_enable(name);
		for(i=0;i<10000;i++);
        screen_spi_send(screen_pcmd->pdata[0][0]); 
		for(i=0;i<10000;i++);  
	while(screen_pcmd->stat<3);
//	while(screen_pcmd->stat!=0xc8)
//	{
//	  SPI_I2S_SendData(SPI2,0x00);
//	
//	}	
}
void screen_down(char dispID,char name,char *pdata)
{
//    uint16_t i=0;
	while(screen_pcmd->stat<3);	 
        screen_pcmd->stat=0;
//		for(i=0;i<200;i++);
        screen_pcmd->name=name;
    screen_head[0]=DISP_DOWNLOAD; screen_head[1]=~DISP_DOWNLOAD; screen_head[2]=(30*30+4)/256; screen_head[3]=(30*30+4)%256;
    screen_head[4]=30; screen_head[5]=30; screen_head[6]=dispID; screen_head[7]=0X00;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=pdata;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=8;screen_pcmd->length[1]=30*30;screen_pcmd->length[2]=3;
        screen_pcmd->send_num=0;
        screen_enable(name);
        screen_spi_send(screen_pcmd->pdata[0][0]);  
//		for(i=0;i<2000;i++);
}
void screen_update(char name ,char* pdata)
{
    while(screen_pcmd->stat<3);// return;
    screen_pcmd->stat=0;
    screen_pcmd->name=name;
    screen_head[0]=DISP_FULL_COLOR; screen_head[1]=~DISP_FULL_COLOR; screen_head[2]=(FULL_SIZE+4)/256; screen_head[3]=(FULL_SIZE+4)%256;
    screen_head[4]=0;               screen_head[5]=0;                screen_head[6]=128;             screen_head[7]=128;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=pdata;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=8;screen_pcmd->length[1]=FULL_SIZE;screen_pcmd->length[2]=3;
    screen_pcmd->send_num=0;
    screen_enable(name);
    screen_spi_send(screen_pcmd->pdata[0][0]);
}
void screen_update_rle_l(char name ,char* pdata,uint16_t length)
{
    while(screen_pcmd->stat<3);// return;
    screen_pcmd->stat=0;
    screen_pcmd->name=name;
    screen_head[0]=DISP_RLE; screen_head[1]=~DISP_RLE; screen_head[2]=(length+4)/256; screen_head[3]=(length+4)%256;
    screen_head[4]=0;               screen_head[5]=48;                screen_head[6]=128;             screen_head[7]=32;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=pdata;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=8;screen_pcmd->length[1]=length;screen_pcmd->length[2]=3;
    screen_pcmd->send_num=0;
    screen_enable(name);
    screen_spi_send(screen_pcmd->pdata[0][0]);
}
void screen_update_rle(char name ,char* pdata,uint16_t length)
{
    while(screen_pcmd->stat<3);// return;
    screen_pcmd->stat=0;
    screen_pcmd->name=name;
    screen_head[0]=DISP_RLE; screen_head[1]=~DISP_RLE; screen_head[2]=(length+4)/256; screen_head[3]=(length+4)%256;
    screen_head[4]=0;               screen_head[5]=0;                screen_head[6]=128;             screen_head[7]=128;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=pdata;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=8;screen_pcmd->length[1]=length;screen_pcmd->length[2]=3;
    screen_pcmd->send_num=0;
    screen_enable(name);
    screen_spi_send(screen_pcmd->pdata[0][0]);
}
void screen_spi_isp(void)
{
  char screen_stat,temp1,temp2;
  unsigned int temp3,i=0; 
  if(flag_high_speed)
  {
   flag=1;
   SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, DISABLE);
   return;
  }
  temp2=screen_pcmd->name-NAME_MIN;
  temp3=screen_pcmd->send_num;
  screen_stat=screen_spi_getdata(); 
   for(i=0;i<400;i++);
						  
    temp1=screen_pcmd->stat;
  if(!(screen_stat&BIT_BUSY))
  {
    time_out=0;
    if(temp3<(screen_pcmd->length[temp1]-1))
    {
       temp3++;
    }  
    else if(temp1<2) 
    {
        temp1++;
        temp3=0;
    } 
    else   
    {
	    SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, DISABLE);	
        screen_disable(temp2+NAME_MIN);
        screen_pcmd->stat=0x08; 
        screen_pcmd->stat|=(screen_stat<<4);   
			

        return;
    }    
  }
  else
  {	   for(i=0;i<200;i++);
    if(flag_pass_once==1)
	{
    if((temp1==2)&&(temp3==2)) 	
	 {	
	    for(i=0;i<400;i++);   
	    flag_pass_once= 0;
        screen_disable(temp2+NAME_MIN);
        screen_pcmd->stat=(screen_stat<<4)|0x04;	
	    SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, DISABLE);
        return;
	 }
	 }
	time_out++;
	 if(time_out>10000)
	 {
        screen_disable(temp2+NAME_MIN);
        screen_pcmd->stat=screen_stat<<4|0x04;	
	    SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, DISABLE);
        return;
	 }
  }

  temp2=screen_pcmd->pdata[temp1][temp3];	
  screen_spi_send(temp2);
  screen_pcmd->send_num=temp3;
  screen_pcmd->stat=temp1;
} 
char screen_trans_noint(char *phead,unsigned int head_len,char *pdata,unsigned int data_len ,char *ptailer,unsigned int tailer_len,char name)
{
   unsigned int i,k;
   __disable_irq();
  	screen_enable(name);
	
	for(k=0;k<1000;k++);
	flag_high_speed=1;
	for(i=0;i<head_len;i++)
	{
	  do{ 
	  
	      SPI_I2S_SendData(SPI2,phead[i]); 
//	   screen_spi_send(screen_head[i]);
	  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	  
		  for(k=0;k<1000;k++);
		  k=screen_spi_getdata();
		  }while(k&BIT_BUSY); 
	}  
	for(i=0;i<data_len;i++)
	{
	  do{ 
	  
	      SPI_I2S_SendData(SPI2,pdata[i]); 
//	   screen_spi_send(screen_head[i]);
	  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	  
		  for(k=0;k<1000;k++);
		  k=screen_spi_getdata();
		  }while(k&BIT_BUSY); 
	}
		for(i=0;i<tailer_len;i++)
	{
	  do{ 
	  
	      SPI_I2S_SendData(SPI2,ptailer[i]); 
//	   screen_spi_send(screen_head[i]);
	  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	  
		  for(k=0;k<1000;k++);
		  k=screen_spi_getdata();
		  }while(k&BIT_BUSY); 
	}
	 for(k=0;k<1000;k++);
	flag_high_speed=0;
	screen_disable(name);
	
   __enable_irq();
	return k;

}


void screen_init_reset(void)
{
    char i,temp,data[2]={00,0x11};
	volatile int dly=0;

    screen_head[0]=DISP_RESET; screen_head[1]=~DISP_RESET; screen_head[2]=0; screen_head[3]=2;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=data;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=4;screen_pcmd->length[1]=2;screen_pcmd->length[2]=3;
    for(i=NAME_MIN;i<=NAME_MAX;i++)
	{
	
        screen_pcmd->stat=0;
        screen_pcmd->name=i;
        screen_pcmd->send_num=0;
        screen_enable(i);	
        for(dly=20000;dly>0;dly--);
        screen_spi_send(screen_pcmd->pdata[0][0]); 
		while(screen_pcmd->stat<3);
		screen_init_stat[i-NAME_MIN]=screen_pcmd->stat;
		for(dly=60000;dly>0;dly--);
		for(dly=60000;dly>0;dly--);
		for(dly=60000;dly>0;dly--);
		for(dly=60000;dly>0;dly--);
		for(dly=60000;dly>0;dly--);
		for(dly=60000;dly>0;dly--);
		for(dly=60000;dly>0;dly--);
		for(dly=60000;dly>0;dly--);
   }


//
//          screen_head[0]=0; screen_head[1]=DISP_TEXT; screen_head[2]=~DISP_TEXT; screen_head[3]=0; screen_head[4]=2+7;
//	   screen_head[5]=0xf0; screen_head[6]=0x02;
//    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;screen_tailer[3]=0x00;
//    screen_pcmd->pdata[0]=screen_head;
//    screen_pcmd->pdata[1]=(char *)INIT_STRING;
//    screen_pcmd->pdata[2]=screen_tailer;
//    screen_pcmd->length[0]=7;screen_pcmd->length[1]=7;screen_pcmd->length[2]=4;
//       for(i=NAME_MIN;i<=NAME_MAX;i++)
//	{
//	
//        screen_pcmd->stat=0;
//        screen_pcmd->name=i;
//        screen_pcmd->send_num=0;
//        screen_enable(i);	
//        for(dly=20000;dly>0;dly--);
//        screen_spi_send(screen_pcmd->pdata[0][0]); 
//		while(screen_pcmd->stat<3);
//		for(dly=20000;dly>0;dly--);
//   }	
   
   
   
   	
    screen_head[0]=DISP_SET_COLOR; screen_head[1]=~DISP_SET_COLOR; screen_head[2]=0; screen_head[3]=3;
	data_buff[0]=15;data_buff[1]=0XFF;data_buff[2]=0XFF;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=data;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=4;screen_pcmd->length[1]=3;screen_pcmd->length[2]=3;

       for(i=NAME_MIN;i<=NAME_MAX;i++)
	{
	
        screen_pcmd->stat=0;
        screen_pcmd->name=i;
        screen_pcmd->send_num=0;
        screen_enable(i);	
        for(dly=20000;dly>0;dly--);
        screen_spi_send(screen_pcmd->pdata[0][0]); 
		while(screen_pcmd->stat<3);
		for(dly=20000;dly>0;dly--);
   }
   
    screen_head[0]=DISP_CLEAR_DISPLAY; screen_head[1]=~DISP_CLEAR_DISPLAY; screen_head[2]=0; screen_head[3]=1;
	data_buff[0]=15;data_buff[1]=0XFF;data_buff[2]=0XFF;
    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
    screen_pcmd->pdata[0]=screen_head;
    screen_pcmd->pdata[1]=data;
    screen_pcmd->pdata[2]=screen_tailer;
    screen_pcmd->length[0]=4;screen_pcmd->length[1]=1;screen_pcmd->length[2]=3;
       for(i=NAME_MIN;i<=NAME_MAX;i++)
	{
	
        screen_pcmd->stat=0;
        screen_pcmd->name=i;
        screen_pcmd->send_num=0;
        screen_enable(i);	
        for(dly=20000;dly>0;dly--);
        screen_spi_send(screen_pcmd->pdata[0][0]); 
		while(screen_pcmd->stat<3);
		for(dly=20000;dly>0;dly--);
   }

}
void screen_key_ack(char name)
{
    char i;
	uint16_t k=0,temp;
	if(screen_init_stat[name-NAME_MIN]!=0x0c8)
        {
		   return;
		}    
	while(screen_pcmd->stat<3);	
    screen_pcmd->name=name;
    screen_head[0]=DISP_KEY_ACK; screen_head[1]=~DISP_KEY_ACK; screen_head[2]=0; screen_head[3]=0;
	screen_head[4]=0x55;screen_head[5]=0xaa;screen_head[6]=0x00;screen_head[7]=0x00;screen_head[8]=0x00;
	screen_head[9]=0x00;screen_head[10]=0x00;screen_head[11]=0x00;screen_head[12]=0x00;screen_head[13]=0x00;
	screen_head[14]=0x00;screen_head[15]=0x00;screen_head[16]=0x00;
	screen_enable(name);
	flag_high_speed=1;

		  do{ 
		      SPI_I2S_SendData(SPI2,0); 
//	   screen_spi_send(screen_head[i]);
	  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
//	  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	  
		  for(k=0;k<1000;k++);
		  k=screen_spi_getdata();
		  }while(k&BIT_BUSY); 

	for(i=0;i<17;i++)
	{
	  do{ 
	  
	      SPI_I2S_SendData(SPI2,screen_head[i]); 
//	   screen_spi_send(screen_head[i]);
	  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
//	  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	  
		  for(k=0;k<1000;k++);
		  k=screen_spi_getdata();
		  }while(k&BIT_BUSY); 
		    
//                k=k&BIT_SW;
//                if(k&&(!key_prestat[name-NAME_MIN]))   //if scope freq were lower than sw-pressed ,sw-pressed would be missed;
//                { 
//                    key_value=name;
//                    key_flag=1;
//                }
				 

	   if(i==2)
	   {
        k=k&BIT_SW;
 //  uint16_t key_dly2=0;
			if(k!= key_prestat[name-NAME_MIN])
			{
			 if(key_dly[name-NAME_MIN]<5) key_dly[name-NAME_MIN]++;
			 else
			 {
			   key_dly[name-NAME_MIN]=0;
	           if(k&&(!key_prestat[name-NAME_MIN]))   //if scope freq were lower than sw-pressed ,sw-pressed would be missed;
	           { 
	//				   for(temp=0;temp<10000;temp++);
	              key_value=name;
	              key_flag=1;
	           }
	  		   if(!k&&(key_prestat[name-NAME_MIN]))   //if scope freq were lower than sw-pressed ,sw-pressed would be missed;
	           { 
	//					for(temp=0;temp<10000;temp++);
	               key_value2=name;
	               key_flag2=1;
	           }					   
	 //    key_prestat2[name-NAME_MIN]=key_prestat[name-NAME_MIN];
	          key_prestat[name-NAME_MIN]=k;
		     }	
		   }
		   else
		   {
		   	  if(k)  key_dly[name-NAME_MIN]=0;
		   }
	   }
	
            
	}
	flag_high_speed=0;
	screen_disable(name);


//        screen_pcmd->stat=0;
//        screen_pcmd->name=name;
//    screen_head[0]=DISP_KEY_ACK; screen_head[1]=~DISP_KEY_ACK; screen_head[2]=0; screen_head[3]=0;
//	data_buff[0]=0;data_buff[1]=0;
//    screen_tailer[0]=0x55;screen_tailer[1]=0xaa;screen_tailer[2]=0x00;
//    screen_pcmd->pdata[0]=screen_head;
//    screen_pcmd->pdata[1]=data_buff;
//    screen_pcmd->pdata[2]=screen_tailer;

//    screen_pcmd->length[0]=2;screen_pcmd->length[1]=2;screen_pcmd->length[2]=3;
//        screen_pcmd->send_num=0;
//        screen_enable(name);
//        screen_spi_send(screen_pcmd->pdata[0][0]);  
}

//-------------------------------------------------
void screen_init_spi(void)
{
  /* SPI2 Config -------------------------------------------------------------*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure);
  SPI_Cmd(SPI2, ENABLE);
}
void screen_init_gpio(void)
{
  char i=0;
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  //-----------------------------SS
  for(i=0;i<KEY_NUM;i++)
  {
  GPIO_InitStructure.GPIO_Pin =screen_pin_ss[i];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(screen_port_ss[i], &GPIO_InitStructure);
  screen_disable(i+NAME_MIN);
  }	
  
}
void screen_init_rcc(void)
{
  /* PCLK2 = HCLK/2 */
  RCC_PCLK2Config(RCC_HCLK_Div2);  
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
  //----------------------ss
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE , ENABLE);
}
void screen_init_nvic(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* 1 bit for pre-emption priority, 3 bits for subpriority */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  /* Configure and enable SPI_MASTER interrupt -------------------------------*/
  NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
}
void screen_enable(char name)
{ 
 char i=name-NAME_MIN;
 GPIO_ResetBits(screen_port_ss[i],screen_pin_ss[i]);
}
void screen_disable(char name)
{  	

 char i=name-NAME_MIN;	 
 GPIO_SetBits(screen_port_ss[i],screen_pin_ss[i]);
}
char screen_spi_getdata(void)
{
    return (char) SPI_I2S_ReceiveData (SPI2);  
}
void screen_spi_send(char data)
{
    SPI_I2S_SendData(SPI2,(uint16_t)data);  
    SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, ENABLE);
}




