
// #include "stm32f4_discovery.h"
// #include "main.h"
// #include "stdio.h"
// #include "stm32f4xx_conf.h"
// #include "Auto.h"

// #include "Bluetooth_HC06.h"
// #include "encoder.h"
// #include "motor.h"
// #include "Servo.h"
// #include "Ultrasonic_SR04.h"
// #include "Realtime_Manage.h"



// extern uint32_t Toggle_MODE;
// extern uint32_t distance;
// extern int32_t	Tear_Process;
// extern uint32_t	Auto_Case;


// ////////Manual Control//////////
// extern uint32_t __IO 	Command;

// ////////servo//////////////
// extern 	uint32_t Toggle_sensor;
// extern int32_t __IO 	Servo_Angle_A;

// extern int32_t __IO 	Servo_Angle_B;
// ////////////////////


// ////////Encoder///////

// //speeds
// extern volatile int16_t B_Encoder_Speed;
// extern volatile int16_t A_Encoder_Speed;


// //distances
// extern volatile int32_t B_Encoder_Distance;
// extern volatile int32_t A_Encoder_Distance;

// 								uint32_t Sona[2];
// 								uint32_t Data;
// #define obstale          200*58

// uint32_t __IO STATE		
// #define FREE_FORWARE							1
// #define OBSTACLE						2
// #define	TURN								
// #define OBSERVE							3
// #define ROTATE							2
// ///////////////////////////////////////
// #define OBSTACLE_A					1
// #define OBSTACLE_B					2
// #define NoOBSTACLE					3


// // 		while(1)
// // 		{
// // 			while (i<180)
// // 			{
// // 			Servo_A_Update (Servo_Angle_A);
// // 			Servo_B_Update (Servo_Angle_B);
// // 				SA[i]=Get_Distance_A();						//Danger_Ultrasonic
// // 				SB[i]=Get_Distance_B();
// // 				i+=10;
// // 				Servo_Angle_A+=10;
// // 				Servo_Angle_B+=10;
// // 			}
// // 			i=0;
// // 			Servo_Angle_A=0;
// // 			Servo_Angle_B=0;
// // 			Mili_Delay (200);

// void Speed_Inc(void)
// {
// }
// void Speed_Dec(void)
// {
// }

// ////////////////////////////////////////////////////////////////////////////////
// void Ultrasonic_Analize(void)
// 	{
// 			switch (STATE)
// 									{
// 									case FREE_FORWARE:
// 																		{
// 																			Sona[0]=Get_Distance_A();						
// 																			Sona[1]=Get_Distance_B();
// 																			if (Sona[0]<obstale)					data = OBSTACLE_A	;
// 																			else if (Sona[1]<obstale)			data = OBSTACLE_B	;
// 																			else 													data = NoOBSTACLE ;
// 																		}
// 									case OBSTACLE:
// 																		{

// 																		}
// 									}
// 									
// 	}
// ////////////////////////////////////////////////////////////////////////////////
// void Sensor_process(void)
// 	{
// 		switch (STATE)
// 									{
// 									case FREE_FORWARE:
// 																		{
// 																			Servo_Angle_A=0;
// 																			Servo_Angle_B=0;										
// 																			Servo_A_Update(Servo_Angle_A);
// 																			Servo_B_Update(Servo_Angle_B);
// 																			Speed_Inc();
// 																			Ultrasonic_Analize();
// 																			if ((data==OBSTACLE_A)||(data==OBSTACLE_B)) 
// 																				STATE = OBSTACLE;
// 																			break;
// 																		}
// 									case OBSTACLE:
// 																		{
// 																			Speed_Dec();
// 																			Servo_Angle_A+=15;
// 																			Servo_Angle_A+=15;									
// 																			Servo_A_Update(Servo_Angle_A);
// 																			Servo_B_Update(Servo_Angle_B);
// 																			Data = Ultrasonic_Analize();
// 																			break;
// 																		}
// 									}
// 																		
// 	}
// ////////////////////////////////////////////////////////////////////////////////
// 	void Moving_Process(void)
// 	{
// 		switch (STATE)
// 									case FREE_FORWARE:
// 																		{
// 																			motorA_update(SPEEDA);
// 																			motorB_update(SPEEDB);
// 																			break;
// 																		}
// 									case OBSTACLE:
// 																		{
// 																			if (Data==OBSTACLE_A)
// 																			{
// 																				motorB_update(-100);
// 																				Mili_Delay (100);
// 																				STATE
// 																			}
// 																			if (Data==OBSTACLE_A)
// 																			{
// 																			}
// 																			if (Data==OBSTACLE_A)
// 																			{
// 																			}
// 																			break;
// 																		}
// 	}
// ////////////////////////////////////////////////////////////////////////////////
// void Switch_State(void)	
// 	{
// 		switch(Data)
// 				case OBSTACLE_A :
// 													{
// 														STATE=OBSTACLE;
// 													}
// 				
// 	}
// 		Test_Surface()
// 									{
// 										while ((Command!= LEFT)||(Command!= RIGHT));
// 										if (Command ==LEFT)
// 										{
// 												while (Command==CROSS) testcount=1;
// 											 testcount =0;
// 										}
// 										
// 									}
// ////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////
// void AUTO_MODE(void)
// {
// 	if(Command==START)	
// 									{
// 										Toggle_MODE=1;
// 										STM_EVAL_LEDOff(LED3);
// 										Servo_A_Update(180);
// 										Servo_B_Update(180);
// 										Mili_Delay (200);
// 										Servo_A_Update(0);
// 										Servo_B_Update(0);
// 										Mili_Delay (200);
// 										Servo_A_Update(180);
// 										Servo_B_Update(180);
// 										SPEEDA=0;
// 										SPEEDB=0;
// 										motorA_update(SPEEDA);
// 										motorB_update(SPEEDB);
// 									}

// 									
// 	Sensor_process();
// 	Moving_Process();

// }
