
#include "stm32f4_discovery.h"
#include "stdio.h"
#include "Bluetooth_HC06.h"
#include "main.h"
#include "SR04_TEST.h"
#include "stm32f4_discovery.h"

__IO uint16_t IC2Value = 0;
__IO uint16_t DutyCycle = 0;
__IO uint32_t Frequency = 0;
__IO uint32_t pulse_length;

void TIM9_IRQHandler(void)
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  /* Clear TIM4 Capture compare interrupt pending bit */
  TIM_ClearITPendingBit(PulseLength_TIMER, TIM_IT_CC2);

  /* Get the Input Capture value */
  IC2Value = TIM_GetCapture2(PulseLength_TIMER);

  if (IC2Value != 0)
  {
    /* Duty cycle computation */
    DutyCycle = (TIM_GetCapture1(PulseLength_TIMER) * 100) / IC2Value;

    /* Frequency computation 
       TIM4 counter clock = (RCC_Clocks.HCLK_Frequency)/2 */

    Frequency = (RCC_Clocks.HCLK_Frequency)/2 / IC2Value;
		
		pulse_length=(10000/Frequency)*DutyCycle;
  }
  else
  {
    DutyCycle = 0;
    Frequency = 0;
  }
}

void Ultra_ECHO_Config(void)
{
	TIM_ICInitTypeDef  TIM_ICInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* TIM4 clock enable */
  RCC_APB2PeriphClockCmd(PulseLength_TIMER_CLK, ENABLE);

  /* GPIOB clock enable */
  RCC_AHB1PeriphClockCmd(PulseLength_CLK, ENABLE);
  
  /* TIM4 chennel2 configuration : PB.07 */
  GPIO_InitStructure.GPIO_Pin   = PulseLength_Pin;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP ;
  GPIO_Init(PulseLength_Port, &GPIO_InitStructure);
  
  /* Connect TIM pin to AF2 */
  GPIO_PinAFConfig(PulseLength_Port , PulseLength_PinSource, PulseLength_GPIO_AF);

  /* Enable the TIM4 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = PulseLength_NVIC_IRQChannel	;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
  /* TIM4 configuration: PWM Input mode ------------------------
     The external signal is connected to TIM4 CH2 pin (PB.07), 
     The Rising edge is used as active edge,
     The TIM4 CCR2 is used to compute the frequency value 
     The TIM4 CCR1 is used to compute the duty cycle value
  ------------------------------------------------------------ */

  TIM_ICInitStructure.TIM_Channel = PulseLength_Channel	;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_PWMIConfig(PulseLength_TIMER , &TIM_ICInitStructure);

  /* Select the TIM4 Input Trigger: TI2FP2 */
  TIM_SelectInputTrigger(PulseLength_TIMER, TIM_TS_TI2FP2);

  /* Select the slave Mode: Reset Mode */
  TIM_SelectSlaveMode(PulseLength_TIMER 	, TIM_SlaveMode_Reset);
  TIM_SelectMasterSlaveMode(PulseLength_TIMER 	,TIM_MasterSlaveMode_Enable);

  /* TIM enable counter */
  TIM_Cmd(PulseLength_TIMER 	, ENABLE);

  /* Enable the CC2 Interrupt Request */
  TIM_ITConfig(PulseLength_TIMER 	, PulseLength_IT_sources, ENABLE);

}


void Ultra_TRIG_Config(void)
{
	GPIO_InitTypeDef 											GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(Trig_A_CLK, ENABLE);

  /* Trig Pin */
  GPIO_InitStructure.GPIO_Pin = Trig_A_Pin ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(Trig_A_Port, &GPIO_InitStructure);
		
	GPIO_ResetBits(Trig_A_Port, Trig_A_Pin);
}

void Ultrasonic_Init(void)
{
	 Ultra_ECHO_Config();
	 Ultra_TRIG_Config();
}

void	Ultrasonic_active(void)
{
		GPIO_SetBits(Trig_A_Port, Trig_A_Pin);
		Micro_Delay (10);
		GPIO_ResetBits(Trig_A_Port, Trig_A_Pin);
		Mili_Delay (60);
}
