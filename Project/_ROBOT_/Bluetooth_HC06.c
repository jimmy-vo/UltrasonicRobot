/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"
#include <stdio.h>
#include "Bluetooth_HC06.h"

// static char RX_buffer[MAX_LEN+1];		


// static int8_t cnt = 0;
static char t;
// static int i;
uint32_t __IO Command;
extern uint32_t __IO 	Signal_timeout;

void UART4_IRQHandler(void)
{
	if( USART_GetITStatus(COM_USART , USART_IT_RXNE))
							{
								t=USART_ReceiveData(COM_USART );
	
								
// 							 /*enable to buffer access*/
// 									if(0)
// 																							{
// 																									if((cnt < 50 )&&(t!='\n'))
// 																										{
// 																											RX_buffer[cnt] = t;
// 																											cnt++;
// 																										}
// 																									else													// otherwise reset the character counter
// 																									{
// 																											printf("-->");
// 																											for(i=0;i<cnt;i++)
// 																											{
// 																												printf("%c",RX_buffer[i]);
// 																											}
// 																											cnt=0;
// 																													printf("\n");
// 																									}
// 																								
// 																									Control_State=0;
// 																								}
// 																								

							switch 	(t)
									{
												case KEY_ROUND :  		Command= ROUND ;
																							break;								
												case KEY_SQUARE:  		Command= SQUARE;
																							break;								
												case KEY_DELTA :  		Command= DELTA ;
																							break;								
												case KEY_CROSS :  		Command= CROSS ;
																							break;								
												
												case KEY_START :  		Command= START ;
																							break;	
												case KEY_SELECT:  		Command= SELECT;
																							break;																					
												
												case KEY_UP 	 : 		  Command= UP  	 ;
																							break;	
												case KEY_DOWN  : 		  Command= DOWN  ;
																							break;																				
												case KEY_RIGHT : 	  	Command= RIGHT ;
																							break;	
												case KEY_LEFT  :		 	Command= LEFT	 ;
																							break;		
												case KEY_NONE  : 		  Command= 0		 ;
																							break;	
										}
							Signal_timeout=0;	
							}

}

void Bluetooth_Module_Init(void)
{
		NVIC_InitTypeDef 											NVIC_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  GPIO_InitTypeDef GPIO_InitStructure;
	  /* USARTx configured as follow:
	        - BaudRate = 115200 baud
	        - Word Length = 8 Bits
	        - One Stop Bit
	        - No parity
	        - Hardware flow control disabled (RTS and CTS signals)
	        - Receive and transmit enabled
	  */
	  USART_InitStructure.USART_BaudRate = 9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	  /* Enable GPIO clock */
	  RCC_AHB1PeriphClockCmd(COM_TX_PORT_CLK | COM_RX_PORT_CLK, ENABLE);
	  /* Enable UART clock */
	  RCC_APB1PeriphClockCmd(COM_USART_CLK, ENABLE);


	  /* Connect PXx to USARTx_Tx*/
	  GPIO_PinAFConfig(COM_TX_PORT, COM_TX_PIN_SOURCE, COM_TX_AF);


	  /* Connect PXx to USARTx_Rx*/
	  GPIO_PinAFConfig(COM_RX_PORT, COM_RX_PIN_SOURCE, COM_RX_AF);


	  /* Configure USART Tx as alternate function  */
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;


	  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(COM_TX_PORT, &GPIO_InitStructure);


	  /* Configure USART Rx as alternate function  */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN;
	  GPIO_Init(COM_RX_PORT, &GPIO_InitStructure);


	  /* USART configuration */
	  USART_Init(COM_USART, &USART_InitStructure);

 
	 	/* Enable USART4 Receive interrupts */
   	USART_ITConfig(COM_USART, USART_IT_RXNE, ENABLE);
		
	  /* Enable USART */
	  USART_Cmd(COM_USART, ENABLE);
	  USART_SendData(COM_USART, (uint8_t) '\r');
		
		/* Configure the NVIC Preemption Priority Bits */  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		
		
		
		/* Enable the USARTy Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel_USART;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0xE;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		printf(" connected!\n");
		
		
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);
}


/*----------------------------------------------------------------------------
  SendChar
  Write character to Serial Port.
 *----------------------------------------------------------------------------*/


int SendChar (int ch) 
	{
			if (ch=='\n')  
				{
					USART_SendData(COM_USART , (uint8_t)'\r');
					while (  (USART_GetFlagStatus(COM_USART , USART_FLAG_TC) == RESET));
			
				   
				} 
      
			USART_SendData(COM_USART, (uint8_t) ch);

			/* Loop until the end of transmission */
					while (  (USART_GetFlagStatus(COM_USART , USART_FLAG_TC) == RESET));
			
				
			return (ch);
	}


/*----------------------------------------------------------------------------
  GetKey
  Read character to Serial Port.
 *----------------------------------------------------------------------------*/
int GetKey (void)
{
	int  ret;  
	//Micro_Timing = timeout;
  /* Loop until incomming data */
			while (  (USART_GetFlagStatus(COM_USART , USART_FLAG_RXNE) == RESET));
	ret = USART_ReceiveData(COM_USART );
  return ret;
}


struct __FILE {
							int handle;                 // Add whatever you need here 
							};
FILE __stdout;
FILE __stdin;



/*----------------------------------------------------------------------------
  fputc
 *----------------------------------------------------------------------------*/
int fputc(int ch, FILE *f)
		{
			return (SendChar(ch));
		}


/*----------------------------------------------------------------------------
  fgetc
 *----------------------------------------------------------------------------*/
int fgetc(FILE *f)
	{
  return (SendChar(GetKey()));
	}


/*----------------------------------------------------------------------------
  _ttywrch
 *----------------------------------------------------------------------------*/
void _ttywrch(int ch) 
	{
		SendChar (ch);
	}


/*----------------------------------------------------------------------------
  ferror
 *----------------------------------------------------------------------------*/
int ferror(FILE *f) 
	{
                             // Your implementation of ferror
  return EOF;
	}


/*----------------------------------------------------------------------------
  _sys_exit
 *----------------------------------------------------------------------------*/
void _sys_exit(int return_code)
			{
			label:  goto label;           // endless loop
			}
