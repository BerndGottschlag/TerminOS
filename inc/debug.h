#ifndef DEBUG_H
#define DEBUG_H

#include "stdbool.h"

void Init_User_Button(void);
bool Is_User_Button_Pressed(void);

void Init_User_LEDs(void);

void Set_LD3_High(void);
void Set_LD3_Low(void);
void Toggle_LD3(void);

void Set_LD4_High(void);
void Set_LD4_Low(void);
void Toggle_LD4(void);

void Init_Debug_Pins(void);
void Toggle_Debug_Pin_PG5(void);
void Toggle_Debug_Pin_PG7(void);
void Set_Debug_Pin_PG7_High(void);
void Set_Debug_Pin_PG7_Low(void);

#endif
