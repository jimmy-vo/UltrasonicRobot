

#include "stm32f4xx.h"




// To init
//			Ultrasonic_Sensor_Init(};
//
//To get distance (cm), the below function will return uint32_t value
//			Ultrasonic_Sensor_execute ();



//TIM3 is use with Chanel 1 and 2


/////////////////////////////////
#define Trig_A_Port 													GPIOE
#define Trig_A_CLK 														RCC_AHB1Periph_GPIOE
#define Trig_A_Pin														GPIO_Pin_11

#define Echo_A_Port 													GPIOE
#define Echo_A_CLK 														RCC_AHB1Periph_GPIOE
#define Echo_A_Pin														GPIO_Pin_12
/////////////////////////////////

#define Trig_B_Port 													GPIOE
#define Trig_B_CLK 														RCC_AHB1Periph_GPIOE
#define Trig_B_Pin														GPIO_Pin_13

#define Echo_B_Port 													GPIOE
#define Echo_B_CLK 														RCC_AHB1Periph_GPIOE
#define Echo_B_Pin														GPIO_Pin_14




#define HALT 0
#define SCAN 1
#define DONE 3


void Ultrasonic_Sensor_Init(void);



	uint32_t Get_Distance_A(void);


	uint32_t Get_Distance_B(void);
