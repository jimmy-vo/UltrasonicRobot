#include "encoder.h"
#include "main.h"




//speeds
volatile int16_t B_Encoder_Speed;
volatile int16_t A_Encoder_Speed;


//distances
volatile int32_t B_Encoder_Distance;
volatile int32_t A_Encoder_Distance;


// local variables
static volatile int16_t oldEncoderB;
static volatile int16_t oldEncoderA;
static volatile int16_t EncoderB;
static volatile int16_t EncoderA;
static volatile int16_t encoderSum;
static volatile int16_t encoderDiff;





/*
 * Configure two timers as quadrature encoder counters. 
 * Details of which timers should be used are
 * in the project hardware header file.
 * Most timers can be used if channels 1 and 2 are available on pins.
 * The timers are mostly 16 bit. Timers can be set to 32 bit but they are
 * not very convenient for IO pins so the counters are simply set to to
 * 16 bit counting regardless.
 * A mouse needs 32 bits of positional data and, since it also needs the
 * current speed, distance is not maintained by the encoder code but will
 * be looked after by the motion control code.
 * The counters are set to X4 mode. The only alternative is X2 counting.
 */
void Encoders_Init (void)
{
		
		GPIO_InitTypeDef GPIO_InitStructure;
	  // Timer peripheral clock enable
  RCC_APB1PeriphClockCmd (ENC_B_TIMER_CLK, ENABLE);
  RCC_APB1PeriphClockCmd (ENC_A_TIMER_CLK, ENABLE);

  // turn on the clocks for each of the ports needed
  RCC_AHB1PeriphClockCmd (ENC_B_1_GPIO_CLK, ENABLE);
  RCC_AHB1PeriphClockCmd (ENC_B_2_GPIO_CLK, ENABLE);
  RCC_AHB1PeriphClockCmd (ENC_A_1_GPIO_CLK, ENABLE);
  RCC_AHB1PeriphClockCmd (ENC_A_2_GPIO_CLK, ENABLE);

  // now configure the pins themselves
  // they are all going to be inputs with pullups
  GPIO_StructInit (&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = ENC_B_1_PIN;
  GPIO_Init (ENC_B_1_GPIO_PORT, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = ENC_B_2_PIN;
  GPIO_Init (ENC_B_2_GPIO_PORT, &GPIO_InitStructure);
  
	GPIO_InitStructure.GPIO_Pin = ENC_A_1_PIN;
  GPIO_Init (ENC_A_1_GPIO_PORT, &GPIO_InitStructure);
  
	GPIO_InitStructure.GPIO_Pin = ENC_A_2_PIN;
  GPIO_Init (ENC_A_2_GPIO_PORT, &GPIO_InitStructure);

  // Connect the pins to their Alternate Functions
  GPIO_PinAFConfig (ENC_B_1_GPIO_PORT, ENC_B_1_SOURCE, ENC_B_1_AF);
  GPIO_PinAFConfig (ENC_B_2_GPIO_PORT, ENC_B_2_SOURCE, ENC_B_2_AF);
  GPIO_PinAFConfig (ENC_A_1_GPIO_PORT, ENC_A_1_SOURCE, ENC_A_1_AF);
  GPIO_PinAFConfig (ENC_A_2_GPIO_PORT, ENC_A_2_SOURCE, ENC_A_2_AF);



  // set them up as encoder inputs
  // set both inputs to rising polarity to let it use both edges
  TIM_EncoderInterfaceConfig (ENC_B_TIMER, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_SetAutoreload (ENC_B_TIMER, 0xffff);
  TIM_EncoderInterfaceConfig (ENC_A_TIMER, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_SetAutoreload (ENC_A_TIMER, 0xffff);

  // turn on the timer/counters
  TIM_Cmd (ENC_B_TIMER, ENABLE);
  TIM_Cmd (ENC_A_TIMER, ENABLE);
  Encoders_Reset();
}


void Encoders_Reset (void)
{
  __disable_irq();
  oldEncoderB = 0;
  oldEncoderA = 0;
  B_Encoder_Distance = 0;
  A_Encoder_Distance = 0;

  TIM_SetCounter (ENC_B_TIMER, 0);
  TIM_SetCounter (ENC_A_TIMER, 0);
  Encoders_Read();
  __enable_irq();
}


void Encoders_Read (void)
{
  oldEncoderB = EncoderB;																		oldEncoderA = EncoderA;
		
  EncoderB = TIM_GetCounter (ENC_B_TIMER) ;										EncoderA = -TIM_GetCounter (ENC_A_TIMER) ;
  
	B_Encoder_Speed = EncoderB - oldEncoderB;												A_Encoder_Speed = EncoderA - oldEncoderA;
   
	
	B_Encoder_Distance += B_Encoder_Speed;																					A_Encoder_Distance += A_Encoder_Speed;
}	

