#include "main.h"
#include "Ultrasonic_SR04.h"

#include "Realtime_Manage.h"
#include "stdio.h"
#include "stm32f4_discovery.h"


uint32_t __IO Ultrasonic_timeout;
				
uint32_t __IO ENCount;

uint32_t __IO Pulse_Measure;




////////////////////////////////////////////////////////

// void SysTick_Handler(void)  //systick is set a every 10us
// {
// 					if (ENCount)				
// 					{
// 					Pulse_Measure++;
// 					}
// 								
// }

void Ultrasonic_Sensor_Init(void)
	{
	GPIO_InitTypeDef 											GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(Trig_A_CLK|Echo_A_CLK|Trig_B_CLK|Echo_B_CLK, ENABLE);

// 		SysTick_Config(SystemCoreClock/ (100000)); //100KHz
  /* Trig Pin */
  GPIO_InitStructure.GPIO_Pin = Trig_A_Pin ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(Trig_A_Port, &GPIO_InitStructure);
		
	  /* Echo Pin */
  GPIO_InitStructure.GPIO_Pin = Echo_A_Pin ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(Echo_A_Port, &GPIO_InitStructure);	
		
	///////////////////////////////
	///////////////////////////////

  /* Trig Pin */
  GPIO_InitStructure.GPIO_Pin = Trig_B_Pin ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(Trig_B_Port, &GPIO_InitStructure);
		
	  /* Echo Pin */
  GPIO_InitStructure.GPIO_Pin = Echo_B_Pin ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(Echo_B_Port, &GPIO_InitStructure);	
	}

	
	
	uint32_t 	Get_Distance_A(void)
	{
		ENCount=0;
		Pulse_Measure=0;
		GPIO_SetBits(Trig_A_Port, Trig_A_Pin);
		Micro_Delay(10);
		GPIO_ResetBits(Trig_A_Port, Trig_A_Pin);
		Ultrasonic_timeout=50;
		while(Ultrasonic_timeout!=0)
		{
			if (GPIO_ReadInputDataBit(Echo_A_Port , Echo_A_Pin)) 			ENCount=1;
			else																											ENCount=0;
		}
		ENCount=0;
		
		printf("%d\n",Pulse_Measure);
		return Pulse_Measure; ; 
	}

	
uint32_t 	Get_Distance_B (void)
 	{
		ENCount=0;
		Pulse_Measure=0;
		GPIO_SetBits(Trig_B_Port, Trig_B_Pin);
		Micro_Delay(10);
		GPIO_ResetBits(Trig_B_Port, Trig_B_Pin);
		Ultrasonic_timeout=50;
		while(Ultrasonic_timeout!=0)
		{
			if (GPIO_ReadInputDataBit(Echo_B_Port , Echo_B_Pin)) 			ENCount=1;
			else																											ENCount=0;
		}
		ENCount=0;
		printf("%d\n",Pulse_Measure);
		return Pulse_Measure; ; 
	}
	
	
