
#include "stm32f4_discovery.h"
#include "main.h"
#include "stdio.h"
#include "stm32f4xx_conf.h"
#include "Manual.h"

#include "Bluetooth_HC06.h"
#include "encoder.h"
#include "motor.h"
#include "Servo.h"
#include "Ultrasonic_SR04.h"
#include "Realtime_Manage.h"

extern int32_t __IO 											Rotate_Speed;
extern int32_t __IO 											Speed;
extern int32_t __IO 											Old_Move;
extern int32_t __IO 											Danger_Ultrasonic;
extern int32_t __IO 											Lock;
extern uint32_t __IO 											Command;
extern uint32_t __IO	 										Toggle_MODE;
extern uint32_t __IO											Toggle_Ultrasonic;

extern int32_t __IO 											Servo_Angle_A;
extern int32_t __IO 											Servo_Angle_B;



extern int16_t B_Encoder_Speed;
extern int16_t A_Encoder_Speed;

extern int32_t B_Encoder_Distance;
extern int32_t A_Encoder_Distance;

uint32_t __IO SeeMe[4];

////////////////////////
void Led_Indicater(void)
	{
			if (Toggle_Ultrasonic)																STM_EVAL_LEDOn(LED3);
							else 																			STM_EVAL_LEDOff(LED3);
		
			if(Toggle_MODE)																			STM_EVAL_LEDOn(LED6);
							else 																			STM_EVAL_LEDOff(LED6);
	}
	
////////////////////////

void Motor_Scaling(void)
	{
			Encoders_Read ();

					
							if ((A_Encoder_Distance-B_Encoder_Distance)>Difference_Scaler)
								
									{				
										motorA_update(Speed- Motor_Scaler_Default);
										motorB_update(Speed +Motor_Scaler_Default);
									}
							if	((B_Encoder_Distance-A_Encoder_Distance)>Difference_Scaler)
									{				
												motorA_update(Speed - Motor_Scaler_Default);
												motorB_update(Speed + Motor_Scaler_Default);
									}
					
					Encoders_Reset ();
	}
//////////////////////
void Ultrasonic_Process(void)
	{
		if((Toggle_Ultrasonic==ON)&&(Lock==0))	
				{
					SeeMe[0]=Get_Distance_A();						//Danger_Ultrasonic
					SeeMe[1]=Get_Distance_B();
					
					if (SeeMe[0]<Danger_Ultrasonic)
								{
										STM_EVAL_LEDOn(LED5);
										Lock=1;
								}
					else	STM_EVAL_LEDOff(LED5);
								
								
					if (SeeMe[1]<Danger_Ultrasonic)
								{
										STM_EVAL_LEDOn(LED4);
										Lock=1;
								}
					else	STM_EVAL_LEDOff(LED4);
				}
	}

void Lock_Move(void)
	{
		if(Lock)
			if(Old_Move==1)
					{
						motorA_update(-Speed);
						motorB_update(-Speed);
						SeeMe[0]=Get_Distance_A();					
						SeeMe[1]=Get_Distance_B();
						Timeout_SetStatus(300,'m');
						while (Lock)
								{
								SeeMe[2]=Get_Distance_A();						//Danger_Ultrasonic
								SeeMe[3]=Get_Distance_B();
									if((SeeMe[2]>SeeMe[0]) || (SeeMe[3]>SeeMe[1]) || Timeout_GetStatus('m'))
										Lock=0;
								}

						motorA_update(0);
						motorB_update(0);
						while ((Command==UP||Command==LOW));
					}
	}
	

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void MANUAL_MODE(void)   																																	 
	{
		Ultrasonic_Process();
		Lock_Move();
		Led_Indicater();
		if(Command==START)
				{
					switch(Toggle_MODE)
					{
								case 	Free :
														{
															Toggle_MODE = Hand;
															Led_Indicater();
																										
														//Reset all cache
															Old_Move=0;
															Speed=0;
															motorA_update(Speed);
															motorB_update(Speed);
															
															Servo_A_Update(180);
															Servo_B_Update(180);
															while(Command==START);
															
															Servo_A_Update(0);
															Servo_B_Update(0);
															Mili_Delay (300);
															Servo_A_Update(180);
															Servo_B_Update(180);
															/////////////////		
															Old_Move=0;
															Speed=SPEED_Mid;
															Lock=0;
															Toggle_Ultrasonic=OFF;
															STM_EVAL_LEDOff(LED4);
															STM_EVAL_LEDOff(LED5);
															Led_Indicater();
															break;
														}
								case 	Hand :
														{
															Toggle_MODE = Free;
															Led_Indicater();
															
															Servo_A_Update(0);
															Servo_B_Update(0);
															while(Command==START);
															
															Servo_A_Update(180);
															Servo_B_Update(180);
															Mili_Delay (300);
															Servo_A_Update(0);
															Servo_B_Update(0);
															/////////////////				
															Old_Move=0;
															Speed=0;
															Lock=0;
															Toggle_Ultrasonic=ON;
															Led_Indicater();
															
															break;
														}					
					}
					
								}
		if(Command==SELECT)	
								{
									switch(Toggle_Ultrasonic)
									{
										case ON:
												{	
												Toggle_Ultrasonic=OFF;
												Led_Indicater();
												STM_EVAL_LEDOff(LED4);
												STM_EVAL_LEDOff(LED5);
												Servo_B_Update (180);
												Servo_A_Update (180);
												while(Command==SELECT);
												Servo_B_Update (0);
												Servo_A_Update (0);
												Mili_Delay (300);
												motorA_update(0);
												motorB_update(0);
												Servo_B_Update (180);
												Servo_A_Update (180);
												break;
												}
										case OFF:		
												{
												Toggle_Ultrasonic=ON;
												Led_Indicater();
												Servo_B_Update (0);
												Servo_A_Update (0);		
												while(Command==SELECT);
												Servo_B_Update (180);
												Servo_A_Update (180);
												Mili_Delay (300);
												Servo_Angle_A=0;
												Servo_Angle_B=0;
												Servo_B_Update (0);
												Servo_A_Update (0);		
												break;
												}
									}
							}	
		if(Command==ROUND)		 
								{
									Speed=SPEED_Low;
									if(Toggle_MODE==Free)
										{	
													Rotate_Speed=SPEED_Low;
											
														if(Old_Move==UP)
													{
														motorA_update(Speed);
														motorB_update(Speed);
													}
													else if(Old_Move==DOWN)
													{
														motorA_update(-Speed);
														motorB_update(-Speed);
													}
												Servo_Angle_A=0;
												Servo_Angle_B=0;
													
										}
									else
										{
											Rotate_Speed = 99;
											Servo_Angle_A=0;
											Servo_Angle_B=0;
										}
									Danger_Ultrasonic=20*58;
								}	
		if(Command==DELTA) 	 
								{ 
									Speed=SPEED_Mid;
									if(Toggle_MODE==Free)
											{	
													Rotate_Speed=SPEED_Mid;
											
													if(Old_Move==UP)
													{
														motorA_update(Speed);
														motorB_update(Speed);
													}
													else if(Old_Move==DOWN)
													{
														motorA_update(-Speed);
														motorB_update(-Speed);
													}
										Servo_Angle_A=0;
										Servo_Angle_B=0;
											}
									else
										{
											Rotate_Speed = 99;
											Servo_Angle_A=0;
											Servo_Angle_B=0;
										}
									Danger_Ultrasonic=30*58;
									
								}										
		if(Command==SQUARE) 
								{
									Speed=SPEED_High;
									if(Toggle_MODE==Free)
										{	
													Rotate_Speed=SPEED_High;
											
													if(Old_Move==UP)
													{
														motorA_update(Speed);
														motorB_update(Speed);
													}
													else if(Old_Move==DOWN)
													{
														motorA_update(-Speed);
														motorB_update(-Speed);
													}
										Servo_Angle_A=0;
										Servo_Angle_B=0;
										}
									else
										{
											Rotate_Speed = 99;
											Servo_Angle_A=0;
											Servo_Angle_B=0;
										}
									Danger_Ultrasonic=45*58;
								}							
	
		if(Command==CROSS)	 
								{ 
									if(Toggle_MODE==Free)
										{	
											motorA_update(Speed*(-Old_Move));
											motorB_update(Speed*(-Old_Move));
											Mili_Delay(300);
											motorA_update(0);
											motorB_update(0);
											Old_Move=0;
											Speed=0;
										}
									}
		
		
		if(Command==LOW)		
								{	
									if((Toggle_MODE==Free)&&(Old_Move!=-1))
										{
											motorA_update(Speed*Old_Move);
											motorB_update(Speed*Old_Move);
										}
									else
										{
											motorA_update(0);
											motorB_update(0);
										}
									if(Toggle_Ultrasonic==ON)
										{
										Servo_A_Update(0);
										Servo_B_Update(0);
										}
								}
					
		if(Command==RIGHT)			
								{	
											if(	Toggle_Ultrasonic==ON)	 Servo_B_Update(Servo_Angle_B);
											motorA_update(Rotate_Speed);
											motorB_update(-Rotate_Speed);
								}	
		if(Command==LEFT)			
								{
											if(	Toggle_Ultrasonic==ON)	 Servo_A_Update(Servo_Angle_A);
											motorA_update(-Rotate_Speed);
											motorB_update(Rotate_Speed);
								}		
		if(Command==UP)		
								{							
									motorA_update(Speed);
									motorB_update(Speed);
									Old_Move=1;
								}
		if(Command==DOWN)		
								{
									motorA_update(-Speed);
									motorB_update(-Speed);
									Old_Move=-1;						
								}

}
		
