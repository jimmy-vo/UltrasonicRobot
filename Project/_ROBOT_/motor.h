
#include "stm32f4_discovery.h"
#include "main.h"
#include "stdio.h"

/*-------------------------------
TIMER Freq = (SysCLK/2)/ [(Prescaler+1)*(Period+1)]
This example is set 10KHZ as default

To setup motors: 												 motor_init()
To update speed:													motor1_update(int dir, float speed_percent)
																						motor2_update(int dir, float speed_percent)							

depending on type of motor driver, edit motor1_update(), motor2_update()

----------------------------------*/



#define PWM_TIM													TIM5
#define PWM_GPIO_PORT										GPIOA


#define PWMA1_TIM												TIM5
#define PWMA1_TIM_CLK   								RCC_APB1Periph_TIM5
#define PWMA1_GPIO_PORT 								GPIOA
#define PWMA1_GPIO_CLK   								RCC_AHB1Periph_GPIOA
#define PWMA1_GPIO_PIN 									GPIO_Pin_0
#define PWMA1_Pin_source 								GPIO_PinSource0
#define PWMA1_TIM_OCMode								TIM_OCMode_PWM1
#define PWMA1_TIM_AF										GPIO_AF_TIM5

#define PWMA2_TIM												TIM5
#define PWMA2_TIM_CLK   								RCC_APB1Periph_TIM5
#define PWMA2_GPIO_PORT 								GPIOA
#define PWMA2_GPIO_CLK   								RCC_AHB1Periph_GPIOA
#define PWMA2_GPIO_PIN 									GPIO_Pin_1
#define PWMA2_Pin_source 								GPIO_PinSource1
#define PWMA2_TIM_OCMode								TIM_OCMode_PWM1
#define PWMA2_TIM_AF										GPIO_AF_TIM5

#define PWMB1_TIM												TIM5
#define PWMB1_TIM_CLK   								RCC_APB1Periph_TIM5
#define PWMB1_GPIO_PORT 								GPIOA
#define PWMB1_GPIO_CLK   								RCC_AHB1Periph_GPIOA
#define PWMB1_GPIO_PIN 									GPIO_Pin_2
#define PWMB1_Pin_source 								GPIO_PinSource2
#define PWMB1_TIM_OCMode								TIM_OCMode_PWM1
#define PWMB1_TIM_AF										GPIO_AF_TIM5

#define PWMB2_TIM												TIM5
#define PWMB2_TIM_CLK   								RCC_APB1Periph_TIM5
#define PWMB2_GPIO_PORT 								GPIOA
#define PWMB2_GPIO_CLK   								RCC_AHB1Periph_GPIOA
#define PWMB2_GPIO_PIN 									GPIO_Pin_3
#define PWMB2_Pin_source 								GPIO_PinSource3
#define PWMB2_TIM_OCMode								TIM_OCMode_PWM1
#define PWMB2_TIM_AF										GPIO_AF_TIM5


#define Period_motor								99			
#define	Prescaler_motor							167	



#define Dutycycle_PWMA1  								0	//inital cycle
#define Dutycycle_PWMA2  								0	//inital cycle

#define Dutycycle_PWMB1								0//inital cycle
#define Dutycycle_PWMB2									0		//inital cycle







//// Motor direction
#define L  																		1
#define R  																		2

void motor_init(void);
void TIMER_Pin_Connect(void);
void PWM_Config(void);

void motorA_update(int32_t SPEED_PERCENT);
void motorB_update(int32_t SPEED_PERCENT);
