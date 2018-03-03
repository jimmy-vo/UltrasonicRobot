#include "main.h"
#include "Realtime_Manage.h"

#include "Ultrasonic_SR04.h"
#include "stdio.h"
#include "stm32f4_discovery.h"

uint32_t cap = 0;

uint16_t __IO  CCR1;
uint16_t __IO CCR2;

uint32_t __IO Micro;
uint32_t __IO Mili;

uint32_t __IO Signal_timeout;

extern uint32_t __IO Ultrasonic_timeout;

extern  uint32_t __IO ENCount;

extern uint32_t __IO Pulse_Measure;


///////////////////
void TIM4_IRQHandler(void)
{
	
			if (TIM_GetITStatus(TimeManage_TIMER, TIM_IT_CC1) != RESET)			
				{
					TIM_ClearITPendingBit(TimeManage_TIMER, TIM_IT_CC1);
					
					if(Micro!=0) 									Micro--;
					if (ENCount)				
					{
					Pulse_Measure++;
					}
					cap = TIM_GetCapture1(TimeManage_TIMER);
					TIM_SetCompare1(TimeManage_TIMER, cap + CCR1);
				}
			
				
			if (TIM_GetITStatus(TimeManage_TIMER, TIM_IT_CC2) != RESET)
				{
					TIM_ClearITPendingBit(TimeManage_TIMER, TIM_IT_CC2);
					
					if(Mili!=0)			 		Mili--;
					if(Ultrasonic_timeout!=0) 		Ultrasonic_timeout--;
					
					Signal_timeout++;
					
					cap = TIM_GetCapture2(TimeManage_TIMER);
					TIM_SetCompare2(TimeManage_TIMER, cap + CCR2);
				}

	}	

void	Timeout_Manage_Config(void)
		{
		TIM_TimeBaseInitTypeDef 							TIM_TimeBaseStructure;
		NVIC_InitTypeDef 											NVIC_InitStructure;
		TIM_OCInitTypeDef											TIM_OCInitStructure;
			/* TIM clock enable */
			RCC_APB1PeriphClockCmd(TimeManage_TIMER_CLK , ENABLE);
			

			/* Enable the TIM gloabal Interrupt */
			NVIC_InitStructure.NVIC_IRQChannel =  TimeManage_NVIC_IRQChannel	;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
					
			CCR1 = 2;			 					 //1us
			CCR2 = 2000;						//1ms	


			
			/* Time base configuration */
			TIM_TimeBaseStructure.TIM_Period = 0xffff;
			TIM_TimeBaseStructure.TIM_Prescaler = 0;
			TIM_TimeBaseStructure.TIM_ClockDivision = 0;
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		
			TIM_TimeBaseInit(TimeManage_TIMER, &TIM_TimeBaseStructure);		
			

			/* Prescaler configuration */
			TIM_PrescalerConfig(TimeManage_TIMER, 41, TIM_PSCReloadMode_Immediate);

  /* Output Compare Timing Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TimeManage_TIMER, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TimeManage_TIMER, TIM_OCPreload_Disable);

  /* Output Compare Timing Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2;

  TIM_OC2Init(TimeManage_TIMER, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TimeManage_TIMER, TIM_OCPreload_Disable);


   
  /* TIM Interrupts enable */
  TIM_ITConfig(TimeManage_TIMER, TIM_IT_CC1 | TIM_IT_CC2 , ENABLE);

  /* TIM enable counter */
  TIM_Cmd(TimeManage_TIMER, ENABLE);
		}	
		
void Timeout_SetStatus(uint32_t Timer, char unit)
		{
			switch (unit)
				{
					case 'm' : Mili=Timer; 
											break;
					case 'u' :Micro=Timer;
											break;					
				}
		}
		
uint8_t  Timeout_GetStatus(char unit)
{	
		switch (unit)
		{
					case 'm' : {
											if (Mili==0) return 1 ;
												else return 0;
										}	
			
					case 'u' : {
										if (Micro==0) return 1 ;
												else return 0;
											}
		}
		return 0;
}


void Mili_Delay(uint32_t num)
{
	Mili=num;
	while(Mili!=0);
}

void Micro_Delay(uint32_t num)
{
	 Micro=num;
	while( Micro!=0);
}
