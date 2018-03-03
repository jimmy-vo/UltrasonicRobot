#include "stm32f4_discovery_lis302dl.h"
#include "Bluetooth_HC06.h"
#include "Realtime_Manage.h"
#include "acceleration_sensor.h"


uint16_t PrescalerValue = 0;
uint8_t Buffer[6];
__IO uint32_t TimingDelay = 0;
__IO int8_t XOffset;
__IO int8_t YOffset;
__IO int8_t ZOffset;


uint32_t LIS302DL_TIMEOUT_UserCallback(void)
{
  /* MEMS Accelerometer Timeout error occured */
  while (1)
  {   
  }
}


void acceleration_sensor_Init(void)
{
	 uint8_t ctrl = 0;
  
  LIS302DL_InitTypeDef  LIS302DL_InitStruct;
  LIS302DL_InterruptConfigTypeDef LIS302DL_InterruptStruct;  
  
//   /* SysTick end of count event each 10ms */
//   SysTick_Config(SystemCoreClock/ 100);
  
  /* Set configuration of LIS302DL*/
  LIS302DL_InitStruct.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;
  LIS302DL_InitStruct.Output_DataRate = LIS302DL_DATARATE_100;
  LIS302DL_InitStruct.Axes_Enable = LIS302DL_X_ENABLE | LIS302DL_Y_ENABLE | LIS302DL_Z_ENABLE;
  LIS302DL_InitStruct.Full_Scale = LIS302DL_FULLSCALE_2_3;
  LIS302DL_InitStruct.Self_Test = LIS302DL_SELFTEST_NORMAL;
  LIS302DL_Init(&LIS302DL_InitStruct);
    
  /* Set configuration of Internal High Pass Filter of LIS302DL*/
  LIS302DL_InterruptStruct.Latch_Request = LIS302DL_INTERRUPTREQUEST_LATCHED;
  LIS302DL_InterruptStruct.SingleClick_Axes = LIS302DL_CLICKINTERRUPT_Z_ENABLE;
  LIS302DL_InterruptStruct.DoubleClick_Axes = LIS302DL_DOUBLECLICKINTERRUPT_Z_ENABLE;
  LIS302DL_InterruptConfig(&LIS302DL_InterruptStruct);

  /* Required delay for the MEMS Accelerometre: Turn-on time = 3/Output data Rate 
                                                             = 3/100 = 30ms */
  Mili_Delay(30);
  
//   /* Configure Interrupt control register: enable Click interrupt1 */
//   ctrl = 0x07;
//   LIS302DL_Write(&ctrl, LIS302DL_CTRL_REG3_ADDR, 1);
//   
//   /* Enable Interrupt generation on click/double click on Z axis */
//   ctrl = 0x70;
//   LIS302DL_Write(&ctrl, LIS302DL_CLICK_CFG_REG_ADDR, 1);
// 

  
  /* Configure Time Limit */
  ctrl = 0x03;
  LIS302DL_Write(&ctrl, LIS302DL_CLICK_TIMELIMIT_REG_ADDR, 1);
    
  /* Configure Latency */
  ctrl = 0x7F;
  LIS302DL_Write(&ctrl, LIS302DL_CLICK_LATENCY_REG_ADDR, 1);
  
  /* Configure Click Window */
  ctrl = 0x7F;
  LIS302DL_Write(&ctrl, LIS302DL_CLICK_WINDOW_REG_ADDR, 1);


  LIS302DL_Read(Buffer, LIS302DL_OUT_X_ADDR, 6);												///reset offset
                  
  XOffset = Buffer[0];
  YOffset = Buffer[2];
	ZOffset = Buffer[4];
}

void XYZ_Get_Value(void)
{	
LIS302DL_Read(Buffer, LIS302DL_OUT_X_ADDR, 6);		
}
