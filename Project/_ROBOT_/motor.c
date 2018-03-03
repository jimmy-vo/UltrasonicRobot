#include "motor.h"
#include "main.h"


void TIMER_Pin_Connect(void)
	{ 
		GPIO_InitTypeDef 											GPIO_InitStructure;		
	
	/* TIM3 clock enable */
  
	RCC_APB1PeriphClockCmd(PWMA1_TIM_CLK |PWMB1_TIM_CLK|PWMA2_TIM_CLK |PWMB2_TIM_CLK, ENABLE);

	
  /* GPIO clock enable */
  RCC_AHB1PeriphClockCmd(PWMA1_GPIO_CLK|PWMA2_GPIO_CLK|PWMB2_GPIO_CLK|PWMB1_GPIO_CLK, ENABLE);

	
  /* GPIO Configuration: Output config */
  GPIO_InitStructure.GPIO_Pin = PWMA1_GPIO_PIN | PWMB1_GPIO_PIN|PWMA2_GPIO_PIN | PWMB2_GPIO_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(PWM_GPIO_PORT, &GPIO_InitStructure); 

	
  /* Connect TIM pins to AF */  
  GPIO_PinAFConfig(PWMA1_GPIO_PORT, PWMA1_Pin_source, PWMA1_TIM_AF	);
  GPIO_PinAFConfig(PWMB1_GPIO_PORT ,PWMB1_Pin_source, PWMB1_TIM_AF	);
	 GPIO_PinAFConfig(PWMA2_GPIO_PORT, PWMA2_Pin_source, PWMA2_TIM_AF	);
  GPIO_PinAFConfig(PWMB2_GPIO_PORT ,PWMB2_Pin_source, PWMB2_TIM_AF	);
	}
	
void PWM_Config(void)
{		
	TIM_TimeBaseInitTypeDef 							TIM_TimeBaseStructure;
	TIM_OCInitTypeDef											TIM_OCInitStructure;
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = Period_motor;
  TIM_TimeBaseStructure.TIM_Prescaler = Prescaler_motor;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(PWM_TIM	, &TIM_TimeBaseStructure);

  /* PWMA1 Mode configuration: Channel1 */
					TIM_OCInitStructure.TIM_OCMode = PWMA1_TIM_OCMode ;
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
					TIM_OCInitStructure.TIM_Pulse = Dutycycle_PWMA1;
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

					TIM_OC1Init(PWMA1_TIM, &TIM_OCInitStructure);

					TIM_OC1PreloadConfig(PWMA1_TIM	, TIM_OCPreload_Enable);

  /* PWMA2 Mode configuration: Channel2 */

					//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
					TIM_OCInitStructure.TIM_Pulse = Dutycycle_PWMA2;

					
					TIM_OC2Init(PWMA2_TIM, &TIM_OCInitStructure);

					TIM_OC2PreloadConfig(PWMA2_TIM, TIM_OCPreload_Enable);
	
	  /* PWMB1 Mode configuration: Channel3 */
					//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
					TIM_OCInitStructure.TIM_Pulse = Dutycycle_PWMB1;

					TIM_OC3Init(PWMB1_TIM, &TIM_OCInitStructure);

					TIM_OC3PreloadConfig(PWMB1_TIM	, TIM_OCPreload_Enable);


  /* PWMB2 Mode configuration: Channel4 */

				//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
					TIM_OCInitStructure.TIM_Pulse = Dutycycle_PWMB2;
			
					
					TIM_OC4Init(PWMB2_TIM, &TIM_OCInitStructure);

					TIM_OC4PreloadConfig(PWMB2_TIM, TIM_OCPreload_Enable);
 
	TIM_ARRPreloadConfig(PWM_TIM, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(PWM_TIM	, ENABLE);
}





// dir : L or R
//speed_percent: 0 -> 100

void motorA_update(int32_t SPEED_PERCENT)
{

	if (SPEED_PERCENT<0)
		{
			TIM_SetCompare1(PWMA1_TIM, -SPEED_PERCENT);
			TIM_SetCompare2(PWMA2_TIM, 0);
		}
		else 
			{
			TIM_SetCompare2(PWMA2_TIM, SPEED_PERCENT);
			TIM_SetCompare1(PWMA1_TIM, 0);
			}

}
void motorB_update(int32_t SPEED_PERCENT)
{

	if (SPEED_PERCENT<0)
		{
			TIM_SetCompare3(PWMB1_TIM, -SPEED_PERCENT);
			TIM_SetCompare4(PWMB2_TIM, 0);
		}
		else 
			{
			TIM_SetCompare4(PWMB2_TIM,SPEED_PERCENT);
			TIM_SetCompare3(PWMB1_TIM, 0);
			}
}
void motor_init(void)
{
	TIMER_Pin_Connect();
	PWM_Config();
}
