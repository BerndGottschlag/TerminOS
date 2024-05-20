#ifndef SYSTEM_TIMER_H
#define SYSTEM_TIMER_H

void Init_System_Timer(void);
void Start_System_Timer(void);
void Reset_System_Timer(void);
uint32_t Get_Time_In_Micro_Seconds(void);
void Delay_For_Micro_Seconds(uint32_t delayValue);
void Delay_Until_Micro_Seconds(uint32_t endTimeInMicroSeconds);

#endif
