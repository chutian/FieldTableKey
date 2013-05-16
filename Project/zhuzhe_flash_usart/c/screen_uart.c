#include "screen_uart.h"
 //			  __enable_irq()  

 //		   __disable_irq()
//------------------------------------
//hardware relate

//-------------------------------------------
//--------------------------------------------
uint16_t uart_pic_length;
extern char flag_down;
//------------------------------
struct screen_uart_datatype screen_uart_var[2]={{UART_UP,{0},0,0,0,0},{UART_DOWN,{0},0,0,0,0}};
char flag_cmd=0,cmd_data[DATA_SIZE]={0},stat=0,file_data[FILE_SIZE];
unsigned int counter=0;
static USART_InitTypeDef USART_InitStructure;

void screen_uart_send(char usart,char data)
{
  if(screen_uart_var[usart].flag_busy==1)
  {		
     __disable_irq();
     if(usart==1)
	 {
	 	screen_uart_var[1].send_buf[screen_uart_var[1].index_in]=data;	
        screen_uart_var[1].index_in=(screen_uart_var[1].index_in+1)%BUFF_SIZE;
        screen_uart_var[1].number++;
	 }
	 else
	 {	  
	 	screen_uart_var[0].send_buf[screen_uart_var[0].index_in]=data;	
        screen_uart_var[0].index_in=(screen_uart_var[0].index_in+1)%BUFF_SIZE;
        screen_uart_var[0].number++;
	 
	 }
	 __enable_irq();
   }
  else
  {
     if(usart==1)
	 {
		 screen_uart_var[1].flag_busy=1;
		 screen_uart_var[1].index_in=0;
		 screen_uart_var[1].index_out=0;
		 screen_uart_var[1].number=0;
		 USART_SendData(screen_uart_var[1].uart, data); 
		 USART_ITConfig(screen_uart_var[1].uart, USART_IT_TXE,ENABLE); 
	 }
	 else
	 { 
		 screen_uart_var[0].flag_busy=1;
		 screen_uart_var[0].index_in=0;
		 screen_uart_var[0].index_out=0;
		 screen_uart_var[0].number=0;
		 USART_SendData(screen_uart_var[0].uart, data); 
		 USART_ITConfig(screen_uart_var[0].uart, USART_IT_TXE,ENABLE); 
	 }
  } 

}
unsigned int err_cnt1=0,err_cnt2=0,u_counter=0;
void screen_uart_up_isp()
{
   char temp;
     if(USART_GetITStatus(screen_uart_var[0].uart, USART_IT_RXNE) != RESET)
  {	 
	   u_counter++;
	  	if(USART_GetFlagStatus(screen_uart_var[0].uart,USART_FLAG_ORE)==SET)
	{
		USART_ClearFlag(screen_uart_var[0].uart,USART_FLAG_ORE); //读SR其实就是清除标志
//		screen_uart_send(1,USART_ReceiveData(screen_uart_var[0].uart)); //读DR
	}   
//	else
//	{
//	  screen_uart_send(1,USART_ReceiveData(screen_uart_var[0].uart));
//	}
        temp= USART_ReceiveData(screen_uart_var[0].uart);
		screen_uart_send(1,temp);
	  switch(stat)
	  {	
		case 0:
	    case 1:
	      if(temp==0x5a) stat++;
		  else           stat=0;
		  counter=0;
		  break;
		case 2:
		   cmd_data[counter++]=temp;
	  	   if(counter==DATA_SIZE)
		   {  
			  counter=0;
		      if((cmd_data[0]==0x00)&&(cmd_data[1]==0x03))
			  {
		           stat=6;
			       uart_pic_length=(uint16_t)cmd_data[2]*4-1;

			  }
		      else if((cmd_data[0]==0x00)&&(cmd_data[1]==0x10))
			  { stat=3;
			    flag_down=1;
			  }
			  else                  stat=7;
		   }
		   break;
		case 3:
		   file_data[counter++]=temp;
	  	   if(counter==2)
		   {
			  uart_pic_length= (((uint16_t)(file_data[0])<<8)|(uint16_t)(file_data[1]))+2;	
			  if(uart_pic_length<0x2000-1)
			  {
			  	stat=4;
				}
				else
				{
				stat=0;
				}
		   }
		   break;
		case 4:
		   file_data[counter++]=temp;
	  	   if(counter==uart_pic_length)
		   {
		      stat=7;
		   }
		   break;
		case 5:			   //NO USED
		   file_data[counter++]=temp;
		      stat=6;
			  uart_pic_length=(uint16_t)temp*4;
		   break;
		case 6:
		   file_data[counter++]=temp;
	  	   if(counter==uart_pic_length)
		   {
		      stat=7;
		   }
		   break;
		case 7:
	  	 if(temp==0xa5)	flag_cmd=1;
		 else           flag_cmd=0;
		 stat=0;
		 break;	
		default:stat=0;break;	
	 }
  }
  if(USART_GetITStatus(screen_uart_var[0].uart, USART_IT_TXE) != RESET)
  {   
    if(screen_uart_var[0].number!=0)
	{
		screen_uart_var[0].number--;
		USART_SendData(screen_uart_var[0].uart, screen_uart_var[0].send_buf[screen_uart_var[0].index_out]); 
		screen_uart_var[0].index_out=(screen_uart_var[0].index_out+1)%BUFF_SIZE;
	}
	else  
	{
		screen_uart_var[0].flag_busy=0;
		USART_ITConfig(screen_uart_var[0].uart, USART_IT_TXE, DISABLE);
	}    
  }
}

void screen_uart_down_isp()
{
	if(USART_GetITStatus(screen_uart_var[1].uart, USART_IT_RXNE) != RESET)
	{
		screen_uart_send(0,USART_ReceiveData(screen_uart_var[1].uart));
	}
	if(USART_GetITStatus(screen_uart_var[1].uart, USART_IT_TXE) != RESET)
	{   
		if(screen_uart_var[1].number!=0)
		{
			screen_uart_var[1].number--;
]			USART_SendData(screen_uart_var[1].uart, screen_uart_var[1].send_buf[screen_uart_var[1].index_out]); 
			screen_uart_var[1].index_out=(screen_uart_var[1].index_out+1)%BUFF_SIZE;
		}
		else  
		{
			screen_uart_var[1].flag_busy=0;
			USART_ITConfig(screen_uart_var[1].uart, USART_IT_TXE, DISABLE);
		}    
	}
}
void screen_uart_init()
{	
    NVIC_InitTypeDef NVIC_InitStructure; 
   GPIO_InitTypeDef GPIO_InitStructure;
  // rcc and gpio
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_AFIO, ENABLE);

  /* Enable USARTy Clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
  /* Enable USARTz Clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  

  /* Configure USARTy Rx as input floating */
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Configure USARTz Rx as input floating */
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  
  
  /* Configure USARTy Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USARTz Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  

  USART_InitStructure.USART_BaudRate =115200;//9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  USART_Init(screen_uart_var[0].uart, &USART_InitStructure);
  USART_Init(screen_uart_var[1].uart, &USART_InitStructure);
    /* Enable USARTy Receive and Transmit interrupts */
  USART_ITConfig(screen_uart_var[0].uart, USART_IT_RXNE, ENABLE);
//  USART_ITConfig(screen_uart_var[0].uart, USART_IT_TXE, ENABLE);

  /* Enable USARTz Receive and Transmit interrupts */
  USART_ITConfig(screen_uart_var[1].uart, USART_IT_RXNE, ENABLE);
//  USART_ITConfig(screen_uart_var[1].uart, USART_IT_TXE, ENABLE);
    /* Enable the USARTy */
  USART_Cmd(screen_uart_var[0].uart, ENABLE);
  /* Enable the USARTz */
  USART_Cmd(screen_uart_var[1].uart, ENABLE);

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the USARTz Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}

