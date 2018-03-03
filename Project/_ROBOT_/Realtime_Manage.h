#include "stm32f4xx.h"


#define TimeManage_TIMER            												  TIM4
#define TimeManage_TIMER_CLK        												  RCC_APB1Periph_TIM4
#define TimeManage_NVIC_IRQChannel														TIM4_IRQn

void TIM4_IRQHandler(void);																			// remember to adjust this

void	Timeout_Manage_Config(void);

uint8_t  Timeout_GetStatus(char unit);

void Timeout_SetStatus(uint32_t Timer, char unit);

void Mili_Delay(uint32_t num);

void Micro_Delay(uint32_t num);
