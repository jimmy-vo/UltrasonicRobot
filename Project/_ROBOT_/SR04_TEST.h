#include "stm32f4_discovery.h"

#include "Bluetooth_HC06.h"
#include "main.h"

#define Trig_A_Port 													GPIOE
#define Trig_A_CLK 														RCC_AHB1Periph_GPIOE
#define Trig_A_Pin														GPIO_Pin_6

#define PulseLength_TIMER 					TIM9
#define PulseLength_TIMER_CLK				RCC_APB2Periph_TIM9
#define PulseLength_NVIC_IRQChannel		TIM1_BRK_TIM9_IRQn  
#define PulseLength_Channel					TIM_Channel_2
#define PulseLength_IT_sources 				TIM_IT_CC2

#define PulseLength_Port 						GPIOE
#define PulseLength_CLK 						RCC_AHB1Periph_GPIOE
#define PulseLength_Pin						GPIO_Pin_5
#define PulseLength_PinSource				GPIO_PinSource5
#define PulseLength_GPIO_AF					GPIO_AF_TIM5


void TIM9_IRQHandler(void);
void Ultra_ECHO_Config(void);
void Ultra_ECHO_Config(void);
void Ultra_TRIG_Config(void);
void Ultrasonic_Init(void);
void	Ultrasonic_active(void);
