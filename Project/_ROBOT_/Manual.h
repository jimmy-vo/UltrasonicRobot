#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"

//////Motors & Encoder///

#define Motor_Scaler_Default				10			//scaler value for motor

#define Difference_Scaler					3000		// reach this, motor will be scaled

#define Timeout_to_Tear						100			//in milisencond, affter this period of time, motors reset to their last speed

#define ROTATE_SPEED							99			//SPEED applied when rotating


#define SPEED_None								0

#define SPEED_Low									75

#define SPEED_Mid									86

#define SPEED_High								100

/////////////////////////////////////
#define Free							1
#define Hand							0


//////servor mode////
#define ON									 1
#define OFF									 0

///////Auto_Case////
#define Danger								1
#define Free_running					2
#define Be_careful						3

void Lock_Move(void);
void 	Led_Indicater(void);
void 	Motor_Scaling(void);
void 	MANUAL_MODE(void);
void Ultrasonic_Process(void);
