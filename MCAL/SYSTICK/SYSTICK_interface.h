/*
 * Author:      Ehab Roshdy
 * Version:     0.1
 * Date:        23/8/2023
 * Description: SYSTICK driver interface file
*/

#pragma once
#include "LIB/STD_TYPES.h"

/**************************           MACROS           **************************/

/**************************          VARIABLES         **************************/

/**************************          FUNCTIONS         **************************/

/* Initialize the SysTick timer */
bool SysTick_Init(bool useSystemClock);

/* Busy-wait delay in milliseconds */
bool SysTick_Busy_Wait_Milli_Sec(uint64 delay);

/* Busy-wait delay in microseconds */
bool SysTick_Busy_Wait_Micro_Sec(uint64 delay);

/* Asynchronous delay with callback in milliseconds */
bool Systick_Wait_Async_Milli_Sec(uint64 delay, void (*taskCallback)(void));

/* Asynchronous delay with callback in microseconds */
bool Systick_Wait_Async_Micro_Sec(uint64 delay, void (*taskCallback)(void));

/* Periodic task with busy-wait in milliseconds */
bool Systick_Busy_Wait_Periodic_Task_Milli_Sec(uint64 delay, void (*taskCallback)(void));

/* Periodic task with busy-wait in microseconds */
bool Systick_Busy_Wait_Periodic_Task_Micro_Sec(uint64 delay, void (*taskCallback)(void));

/* Periodic task with interrupt in milliseconds */
bool Systick_Wait_Periodic_Task_Milli_Sec(uint64 delay, void (*taskCallback)(void));

/* Periodic task with interrupt in microseconds */
bool Systick_Wait_Periodic_Task_Micro_Sec(uint64 delay, void (*taskCallback)(void));

/* Stop the timer and reset the driver's state */
void Systick_Stop_Timer(void);

void Systick_Pause_Timer(void);

void Systick_Continue_Timer(void);
