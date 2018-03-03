#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"


#define COM_USART         								UART4
#define COM_USART_CLK   									RCC_APB1Periph_UART4

#define COM_TX_PORT      									GPIOC
#define COM_RX_PORT    					 					GPIOC

#define COM_TX_PORT_CLK  									RCC_AHB1Periph_GPIOC
#define COM_RX_PORT_CLK 									RCC_AHB1Periph_GPIOC

#define COM_TX_PIN      									GPIO_Pin_10
#define COM_RX_PIN       									GPIO_Pin_11

#define COM_TX_PIN_SOURCE									GPIO_PinSource10
#define COM_RX_PIN_SOURCE	 								GPIO_PinSource11

#define COM_TX_AF        									GPIO_AF_UART4
#define COM_RX_AF       									GPIO_AF_UART4

#define NVIC_IRQChannel_USART							UART4_IRQn

#define MAX_LEN  			20


////////// Control_state  ////


////////// Command & State ////
#define LOW						0

#define UP 						1
#define DOWN					2	
#define RIGHT				  3
#define LEFT					4

#define  ROUND			5
#define  CROSS			6
#define  DELTA			7
#define  SQUARE			8

#define  START			9
#define  SELECT			10

#define HIGH			11

/////////////KEY/////////
#define KEY_NONE		'0'		
#define KEY_UP			'1'			
#define KEY_DOWN 		'2'
#define KEY_LEFT		'3'				
#define KEY_RIGHT		'4'

#define KEY_CROSS		'5'
#define KEY_ROUND		'6'
#define KEY_SQUARE	'7'
#define KEY_DELTA		'8'

#define KEY_SELECT	'9'
#define KEY_START		'A'	




/*----------------------------------------
Default: 
 Slave, 9600 baud rate, N, 8, 1. Pincode 1234 
 
AT command: 

	1. Communications Test : 
		
		Sent : AT 
		receive : OK 

	2. Change baud rate : 
		
		Sent : AT+BAUD1 
		receive : OK1200 
		
		Sent : AT+BAUD2 
		receive : OK2400 

											1---------1200 
											2---------2400 
											3---------4800 
											4---------9600 
											5---------19200 
											6---------38400 
											7---------57600 
											8---------115200 
		Baud rate setting can be save even power down. 


	3. Change Bluetooth device name: 
	
		Sent : AT+NAMEdevicename 
		receive : OKname 
		
		(devicename is the name you want the device to be , and it will be searched with this name) 
			Name setting can be save even power down. 
			
4. Change Pincode: 

		Sent : AT+PINxxxx 
		receive : OKsetpin 
		
		(xxxx is the pin code you set) 
		Pin code can be save even power down
------------------------------------------*/




void USART2_IRQHandler(void);
void Bluetooth_Module_Init(void);
int SendChar (int ch) ;




