/// need to extern uint8_t Buffer[6];



#define X_axis					Buffer[0]
#define Y_axis					Buffer[2]
#define Z_axis					Buffer[4]

void acceleration_sensor_Init(void);
uint32_t LIS302DL_TIMEOUT_UserCallback(void);
void XYZ_Get_Value(void);
