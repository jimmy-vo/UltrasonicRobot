
#include "stm32f4_discovery.h"
#include "main.h"
#include "stdio.h"



  /*
   * definitions for the quadrature encoder pins
   */


// Right Motor Channels
#define ENC_A_1_PIN               GPIO_Pin_6
#define ENC_A_1_GPIO_PORT         GPIOC
#define ENC_A_1_GPIO_CLK          RCC_AHB1Periph_GPIOC
#define ENC_A_1_SOURCE            GPIO_PinSource6
#define ENC_A_1_AF                GPIO_AF_TIM3

#define ENC_A_2_PIN               GPIO_Pin_7
#define ENC_A_2_GPIO_PORT         GPIOC
#define ENC_A_2_GPIO_CLK          RCC_AHB1Periph_GPIOC
#define ENC_A_2_SOURCE            GPIO_PinSource7
#define ENC_A_2_AF                GPIO_AF_TIM3

// Left Motor Channels
#define ENC_B_1_PIN               GPIO_Pin_8
#define ENC_B_1_GPIO_PORT         GPIOC
#define ENC_B_1_GPIO_CLK          RCC_AHB1Periph_GPIOC
#define ENC_B_1_SOURCE            GPIO_PinSource8
#define ENC_B_1_AF                GPIO_AF_TIM3

#define ENC_B_2_PIN               GPIO_Pin_9
#define ENC_B_2_GPIO_PORT         GPIOC
#define ENC_B_2_GPIO_CLK          RCC_AHB1Periph_GPIOC
#define ENC_B_2_SOURCE            GPIO_PinSource9
#define ENC_B_2_AF                GPIO_AF_TIM3

// determine the timers to use

#define ENC_A_TIMER              TIM3
#define ENC_A_TIMER_CLK          RCC_APB1Periph_TIM3
#define ENC_B_TIMER              TIM3
#define ENC_B_TIMER_CLK          RCC_APB1Periph_TIM3

#define COUNT_B()            ENC_B_TIMER->CNT
#define COUNT_A()           ENC_A_TIMER->CNT





void Encoders_Init (void);
void Encoders_Reset (void);
void Encoders_Read (void);
