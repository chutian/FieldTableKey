#include "sys.h"

void delay_Tns(void);
void delay_Tms(void);
void delay_ms(unsigned int Ms);

 void write(char id,uint16_t length,char* pdata){}

//uint16_t pic_length[5]={6588,DOWN_LENGTH,LEFT_LENGTH,RIGHT_LENGTH,SQUARE_LENGTH};  
//uint16_t pic_length[5]={UP_LENGTH,DOWN_LENGTH,LEFT_LENGTH,RIGHT_LENGTH,SQUARE_LENGTH};  
//extern  char ok[3708+8],up[4772+8],xiaohui[7570+8],music[5468+8];
//char * pic_addr[5]={(char *)test1+8,(char *)arrowdown+8,(char *)arrowleft+8,(char *)arrowright+8,(char *)square+8};
//char * pic_addr[5]={(char *)arrowup+8,(char *)arrowdown+8,(char *)arrowleft+8,(char *)arrowright+8,(char *)square+8};
static uint16_t j=0;
char key_id[KEY_NUM]={0};

char key_picid[KEY_NUM]={0};

char ini_num=5,flag_down=0;

static void RCC_Configuration(void);

void delay_Tns(void)
{
    unsigned int i;
    for(i=0;i<60000;i++);
}
void delay_Tms(void)
{
    unsigned int k;
    for(k=0;k<10;k++)
    {
        delay_Tns();
    }
}
void delay_ms(unsigned int Ms)
{
    unsigned int k;
    for(k=0;k<Ms;k++)
    {
        delay_Tns();
    }
}
void delay(unsigned int ms)
{
   unsigned int tuij;
   while (ms--) {
      for (tuij=0;tuij<=1000;tuij++) {
         ;
      }
   }
}

void sys_main(void)
{		   
    volatile uint16_t i,k=0,x=1;
    char temp,temp2,flag_err=0,ini_buff[100];
    char flag_debug=0;
    unsigned char tucWritePage;
    unsigned char tucWriteLoop;
    unsigned char tucReadLoop;
    //unsigned char tempKey[8192];
    delay_Tms();
    screen_init();                //按键屏初始化，SPI初始化
    #ifdef BOARD_6_1
        i=1;		
    #endif
    #ifdef BOARD_7
        i=2;
    #endif
    #ifdef BOARD_6_2
        i=3;
    #endif
    #ifdef BOARD_6_3
        i=4;
    #endif
    ReadDate (flash_pic,READ_DATA_SIZE,i);   //根据FLASH读取面信息，来显示图片
    for(i=0;i<100;i++)
    {
        ini_buff[i]=flash_pic[i];
    }
    if((ini_buff[1]<100)&&(ini_buff[1]>=KEY_NUM))
    {
        ini_num=ini_buff[1]/KEY_NUM;
        if(ini_num>9) ini_num=9;
    }
    ReadDate (flash_pic,READ_DATA_SIZE,5);      //读取第5页暂存的页面
    if((flash_pic[0]==0X0A5)&&(flash_pic[1]==0X5A)&&(flash_pic[2]==0X0A5))
    {
        for(temp=NAME_MIN;temp<=NAME_MAX;temp++)
        {
            screen_call(temp); 
            delay_Tms();
        }
    }
    else
    {
        for(temp=NAME_MIN;temp<=NAME_MAX;temp++)
        {
            screen_update_rle_l_noint(temp,loading+8,sizeof(loading)-8); 
            delay_Tms();
        }
        for(temp=NAME_MIN;temp<=NAME_MAX;temp++)
        {
            screen_down_rle_noint(temp,10,whitepic+8,sizeof(whitepic)-8); 
            delay_Tns();
        }
        if((ini_buff[1]<100)&&(ini_buff[1]>=KEY_NUM))
        {
            for(i=0;i<ini_num;i++)
            { 
                for(temp=NAME_MIN;temp<=NAME_MAX;temp++)
                {    
                    temp2=ini_buff[2+i+(temp-NAME_MIN)*ini_num];
                    if(temp2!=0)
                    {
                        flash_pic[0]=0;
                        flash_pic[1]=0;
                        ReadDate (flash_pic,READ_DATA_SIZE,temp2);
                        k=(uint16_t)(flash_pic[0]<<8)|flash_pic[1];
                        if((k!=0xffff)&&(k!=0))
                        {
                            screen_down_rle_noint(temp,i+1,flash_pic+2,k);
                            screen_recall(temp,i+1); 
                        } 
                    } 
                }
            } 
        }
        for(temp=NAME_MIN;temp<=NAME_MAX;temp++)
        {
            screen_save(temp); 
            delay_Tms();
        }
        flash_pic[0]=0x0a5;
        flash_pic[1]=0x5a;
        flash_pic[2]=0x0a5;
        WriteDate(flash_pic,READ_DATA_SIZE,5);
    } 
    delay_ms(20);
    for(temp=NAME_MIN;temp<=NAME_MAX;temp++)
    {					
        delay_Tns();
        flag_pass_once=1;
        screen_recall(temp,1);
        key_picid[temp-NAME_MIN]=1; 
    }	
    flag_pass_once=0; 
    screen_uart_init();          //初始化串口相关的信息
    while(1)
    { 
        if(flag_down==0)
        {
            for(i=NAME_MIN;i<=NAME_MAX;i++)
            {	 
                if(screen_init_stat[i-NAME_MIN]==0xc8)
                {
                    screen_key_ack(i);	
                }
                if(key_flag==1)
                {
                    if(flag_debug==1)
                    {
                        for(temp=NAME_MIN;temp<=NAME_MAX;temp++)
                        {
                            flag_pass_once=1;
                            key_picid[temp-NAME_MIN]=x; 
                            screen_recall(temp,x++); 
                            flag_pass_once=0;
                            if(x>5)  x-=5;
                        }
                    }
                    else
                    {	
                        flag_pass_once=1;
                        screen_recall(i,10);
                    }
                    screen_uart_send(0,key_value);
                    key_flag=0;
                    j++;
                } 
                if(key_flag2==1)
                {
                    if(flag_debug==0)
                    {
                        pic_disp(key_value2,key_picid[key_value2-NAME_MIN]);
                    }
                    screen_uart_send(0,key_value2|0x80);
                    key_flag2=0;
                    j++;
                }

            }
        }
        if(flag_cmd==1)
        {
            switch(cmd_data[1])
            {
            case 0x03: 
                flag_err=0;
                for(k=0;k<cmd_data[2];k++)
                {
                    i=file_data[k*4];
                    if(((i>=NAME_MIN))&&(i<=NAME_MAX))
                    {  
                        if(screen_init_stat[i-NAME_MIN]!=0xc8)
                        {
                            flag_err=1;
                        }
                        else if(file_data[k*4+2]<=ini_num)
                            {
                                flag_pass_once=1;
                                screen_recall(i,file_data[k*4+2]);
                                key_picid[i-NAME_MIN]=file_data[k*4+2];
                            }
                        else if(file_data[k*4+2]<=PIC_NUM)              
                            {
                                ReadDate (flash_pic,READ_DATA_SIZE,file_data[k*4+2]);
                                screen_update_rle(i,(flash_pic+2),(flash_pic[0]<<8)|flash_pic[1]);
                                key_picid[i-NAME_MIN]=file_data[k*4+2];
                            }
                    }
                }
                break;
            case 0x04:
                if(cmd_data[3]==1)
                {
                    flag_debug=1;
                }
                else 
                {
                    flag_debug=0;
                }
                break; 
            case 0x27:
                for(i=NAME_MIN;i<=NAME_MAX;i++)
                {  
                    if(screen_init_stat[i-NAME_MIN]==0xc8)
                    {
                        temp=(cmd_data[2]<<4)|(cmd_data[3]&0x0f);
                        screen_backlight(i,temp);
                    }
                }
                break;
            case 0x0ff: 
                if((cmd_data[2]<=NAME_MAX)&&(cmd_data[2]>=NAME_MIN)) 
                {
                    if(cmd_data[3]<=ini_num)
                    { 
                        flag_pass_once=1;
                        screen_recall(cmd_data[2],cmd_data[3]);
                        key_picid[cmd_data[2]-NAME_MIN]=cmd_data[3];
                    }
                    else 
                    {
                        if(cmd_data[3]<=PIC_NUM)
                        {
                            temp=cmd_data[2];
                            ReadDate (flash_pic,READ_DATA_SIZE,cmd_data[3]);
                            screen_update_rle(temp,(flash_pic+2),(flash_pic[0]<<8)|flash_pic[1]);
                            key_picid[cmd_data[2]-NAME_MIN]=cmd_data[3];
                        }
                    }
                }
                break;
            case 0x010: 
                #ifdef BOARD_6_1
                    if((cmd_data[2]==0)||(cmd_data[2]==1))		
                #endif
                #ifdef BOARD_7
                    if((cmd_data[2]==0)||(cmd_data[2]==2))
                #endif
                #ifdef BOARD_6_2
                    if((cmd_data[2]==0)||(cmd_data[2]==3))
                #endif
                #ifdef BOARD_6_3
                    if((cmd_data[2]==0)||(cmd_data[2]==4))
                #endif 
                {		
                        flag_down=1;
                        temp=cmd_data[3];	
                        i=	((file_data[0]<<8)|file_data[1])+2;
                        for(k=0;k<i;k++)
                        {
                            flash_pic[k]= file_data[k];   
                        }
                        WriteDate(flash_pic,READ_DATA_SIZE,temp);
                        //测试FLASH写入是否正确
                        /* 
                        ReadDate (file_data,READ_DATA_SIZE,temp);
                        for(i=0;i<READ_DATA_SIZE;i++)
                        {
                            if(flash_pic[i]!=file_data[i])
                            {
                                break;
                            }
                        } 
                        */ 
                        delay_ms(5);
                        flash_pic[0]=0x0;
                        flash_pic[1]=0x0;
                        flash_pic[2]=0x0;
                        WriteDate(flash_pic,READ_DATA_SIZE,5);
                 }
                 break;		        		  
            default :
                break;
            }
            flag_cmd=0;   
        }				   	
    }
}

void pic_disp(char name,char picid)
{
   if(picid<=ini_num)
   {
      screen_recall(name,picid);
   }
   else
   {

	  ReadDate (flash_pic,READ_DATA_SIZE,picid);
	  screen_update_rle(name,(flash_pic+2),(flash_pic[0]<<8)|flash_pic[1]);
   }

}


 /*配置系统时钟,使能各外设时钟*/
static void RCC_Configuration(void)
        {
           ErrorStatus  HSEStartUpStatus;

     RCC_DeInit();                     //RCC 系统复位
     RCC_HSEConfig(RCC_HSE_ON);      //开启HSE
     HSEStartUpStatus = RCC_WaitForHSEStartUp();  //等待HSE准备好
     if(HSEStartUpStatus == SUCCESS)
     {
       FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //Enable Prefetch Buffer
       FLASH_SetLatency(FLASH_Latency_2);      //Set 2 Latency cycles
       RCC_HCLKConfig(RCC_SYSCLK_Div1);   //AHB clock  = SYSCLK
       RCC_PCLK2Config(RCC_HCLK_Div1);   //APB2 clock = HCLK
       RCC_PCLK1Config(RCC_HCLK_Div2);   //APB1 clock = HCLK/2
       RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); //PLLCLK = 12MHz * 6 = 72 MHz
       RCC_PLLCmd(ENABLE);          //Enable PLL
       while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);  //Wait till PLL is ready  
       RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //Select PLL as system clock source
       while(RCC_GetSYSCLKSource() != 0x08);   //Wait till PLL is used as system clock source     
        }
  }
