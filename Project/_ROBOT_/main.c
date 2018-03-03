
#include "stm32f4_discovery.h"
#include "main.h"
#include "stdio.h"
#include "stm32f4xx_conf.h"

#include "Manual.h"
#include "Auto.h"

#include "Bluetooth_HC06.h"
#include "encoder.h"
#include "motor.h"
#include "Servo.h"
#include "Ultrasonic_SR04.h"
#include "Realtime_Manage.h"
#include "acceleration_sensor.h"

uint32_t __IO Toggle_MODE;
//////// MOTORS ////////////////////////////////////////////////
				int32_t __IO 											Speed;
				int32_t __IO 											Lock;
				int32_t __IO 											Old_Move;
				int32_t __IO 											Rotate_Speed;
//////// SERVO & ULTRASONIC ///////////////////////////////////
				uint32_t __IO 										Toggle_Ultrasonic;
				int32_t __IO 											Danger_Ultrasonic;
				
				int32_t __IO 											Servo_Angle_A;
				int32_t __IO 											Servo_Angle_B;
//////////////////////////////////////////////////////////////

extern uint32_t __IO 											Signal_timeout;

void Assert_BTConection(void)
	{
		if(Signal_timeout>700)
		{	
			if(Toggle_MODE==Free)
					{
					motorA_update(Speed*(-Old_Move));
					motorB_update(Speed*(-Old_Move));
					Mili_Delay(200);
					}
					motorA_update(0);
					motorB_update(0);
					
		while(Signal_timeout>700)
			{
				STM_EVAL_LEDOn(LED3);
				STM_EVAL_LEDOn(LED4);
				STM_EVAL_LEDOn(LED5);
				STM_EVAL_LEDOn(LED6);
				Mili_Delay(300);
				STM_EVAL_LEDOff(LED3);
				STM_EVAL_LEDOff(LED4);
				STM_EVAL_LEDOff(LED5);
				STM_EVAL_LEDOff(LED6);
				Mili_Delay(400);
			}
			
				Speed=0;
				Old_Move=0;
		}
	}
int main()
{
	Timeout_Manage_Config(); 
	Led_Indicater(); 
	Encoders_Init ();
	Ultrasonic_Sensor_Init();    
 	motor_init();
	Servo_Init();
	Bluetooth_Module_Init();
//acceleration_sensor_Init();
	
////////////Init Status////////

	Servo_A_Update (180);
	Servo_B_Update (180);
	Toggle_MODE = Hand;
	Toggle_Ultrasonic=OFF;
	Speed=SPEED_Mid;
	Lock=0;
	Rotate_Speed=SPEED_Mid;
	Danger_Ultrasonic=30*58; //mid_speed
// ////////////////////////////
	

	while(1)
			{	
			Assert_BTConection();
			MANUAL_MODE();
			}

}

