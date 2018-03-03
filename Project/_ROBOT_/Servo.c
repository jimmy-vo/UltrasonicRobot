#include "motor.h"
#include "Servo.h"


extern uint32_t Toggle_sensor;

void Servo_A_Update (int32_t	Ang)
{
	
	//the servo work at 50Hz (20ms), duty cyle range: 600us - 2600us
	//		Scaler - 0 Deg (reference)
	//		Resolution - 1 deg
	if((Ang<=180)&&(Ang>=0))
			{		
			Ang=(Ang*Resolution_A)+Servo_Scaler_A;
			TIM_SetCompare1(SERVO_PWMA_TIM, Ang);

			}	
		
}
void Servo_B_Update (int32_t	Ang)
{
	
	//the servo work at 50Hz (20ms), duty cyle range: 600us - 2600us
	//		Scaler - 0 Deg (reference)
	//		Resolution - 1 deg
	if((Ang<=180)&&(Ang>=0))
			{		
			Ang=-(Ang*Resolution_B)+Servo_Scaler_B;
			TIM_SetCompare2(SERVO_PWMB_TIM, Ang);

			}	
		
}

void Servo_Init(void)
{
	GPIO_InitTypeDef 											GPIO_InitStructure;		
	TIM_TimeBaseInitTypeDef 							TIM_TimeBaseStructure;
	TIM_OCInitTypeDef											TIM_OCInitStructure;
	
	/* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(SERVO_PWMA_TIM_CLK|SERVO_PWMB_TIM_CLK , ENABLE);

  /* GPIO clock enable */
  RCC_AHB1PeriphClockCmd(SERVO_PWMA_GPIO_CLK|SERVO_PWMB_GPIO_CLK, ENABLE);
  
  /* GPIO Configuration: Output config */
  GPIO_InitStructure.GPIO_Pin = SERVO_PWMA_GPIO_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(SERVO_PWMA_GPIO_PORT 	, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = SERVO_PWMB_GPIO_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(SERVO_PWMB_GPIO_PORT 	, &GPIO_InitStructure); 

	
  /* Connect TIM pins to AF */  
  GPIO_PinAFConfig(SERVO_PWMA_GPIO_PORT, SERVO_PWMA_Pin_source, SERVO_PWMA_TIM_AF	);
	GPIO_PinAFConfig(SERVO_PWMB_GPIO_PORT, SERVO_PWMB_Pin_source, SERVO_PWMB_TIM_AF	);
	
	

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = Period_servo;
  TIM_TimeBaseStructure.TIM_Prescaler = Prescaler_servo;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(SERVO_PWMA_TIM	, &TIM_TimeBaseStructure);

  /* PWMA Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode =SERVO_PWMA_OCMode_TIM;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR_Val_servo;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(SERVO_PWMA_TIM		, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(SERVO_PWMA_TIM			, TIM_OCPreload_Enable);
	
	
	 /* PWMB Mode configuration: Channel2 */
	  TIM_OCInitStructure.TIM_OCMode =SERVO_PWMB_OCMode_TIM;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR_Val_servo;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC2Init(SERVO_PWMB_TIM		, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(SERVO_PWMB_TIM			, TIM_OCPreload_Enable);

		TIM_ARRPreloadConfig(SERVO_PWMB_TIM		, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(SERVO_PWMA_TIM	, ENABLE);

}




