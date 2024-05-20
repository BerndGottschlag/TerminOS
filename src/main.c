#include "stm32f4xx.h"

#include "clock_config.h"
#include "debug.h"
#include "system_timer.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


int main(void)
{
	Init_Clock();
	Init_Debug_Pins();
	Init_User_LEDs();

	Init_System_Timer();
	Start_System_Timer();

	while(1)
	{
		Toggle_LD3();
		Delay_For_Micro_Seconds(1000000);
		//Toggle_Debug_Pin_PG5();
		//Delay_For_Micro_Seconds(100);
	}
}
