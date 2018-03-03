
#include "stm32f4_discovery.h"
#include "main.h"
#include "stdio.h"

/*-------------------------------
TIMER Freq = (SysCLK/2)/ [(Prescaler+1)*(Period+1)]
This example is set 50KHZ as default

To setup motors: 												Servo_Init()
To update speed:													Servo_Process (Angle)			

the servo work at 50Hz (20ms), duty cyle range: 400us - 2600us

----------------------------------*/











#define SERVO_PWMA_TIM													TIM12
#define SERVO_PWMA_TIM_CLK   									RCC_APB1Periph_TIM12
#define SERVO_PWMA_GPIO_PORT 									GPIOB
#define SERVO_PWMA_GPIO_CLK   									RCC_AHB1Periph_GPIOB
#define SERVO_PWMA_GPIO_PIN 										GPIO_Pin_14
#define SERVO_PWMA_Pin_source 									GPIO_PinSource14
#define SERVO_PWMA_OCMode_TIM								TIM_OCMode_PWM1
#define SERVO_PWMA_TIM_AF											GPIO_AF_TIM12




#define SERVO_PWMB_TIM													TIM12
#define SERVO_PWMB_TIM_CLK   									RCC_APB1Periph_TIM12
#define SERVO_PWMB_GPIO_PORT 									GPIOB
#define SERVO_PWMB_GPIO_CLK   									RCC_AHB1Periph_GPIOB
#define SERVO_PWMB_GPIO_PIN 										GPIO_Pin_15
#define SERVO_PWMB_Pin_source 									GPIO_PinSource15
#define SERVO_PWMB_OCMode_TIM								TIM_OCMode_PWM1
#define SERVO_PWMB_TIM_AF											GPIO_AF_TIM12




#define Period_servo										19999			
#define	Prescaler_servo									83	

#define CCR_Val_servo  									1500	//inital cycle

#define	 Upper_Range						2500
#define		Lower_Range						700

#define  Servo_Scaler_A					650
#define  Servo_Scaler_B     		2460 

#define  Resolution_A						11
#define  Resolution_B						11


void Servo_Init(void);
void Servo_A_Update (int32_t	Ang);
void Servo_B_Update (int32_t	Ang);
