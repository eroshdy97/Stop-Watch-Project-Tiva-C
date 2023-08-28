/*
 * Author:      Ehab Roshdy                                                                      
 * Version:     0.1                                                                       
 * Date:        23/8/2023                                                                             
 * Description: SYSTICK driver private file                                       
*/

#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H
/**************************           MACROS           **************************/


#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

#define SYSTICK_PRESCALER_FREQ 4000000           /* CPUF/4 = 16000000/4 */
#define SYSTICK_MAX_TICKS 16777215          /* 2^n - 1 = 2^24 - 1 */

/**************************          VARIABLES         **************************/

static bool useSystemClock;
static bool isContinues;
static uint32 counter;
static uint32 numberOfOverflows;
static void (*delayCompleteCallback)(void);

/**************************          FUNCTIONS         **************************/

static bool busy_Wait(uint32 factor, uint64 delay);
static bool wait_Async(uint32 factor, uint64 delay, void (*taskCallback)(void));
static bool busy_Wait_Periodic_Task(uint32 factor, uint64 delay, void (*taskCallback)(void));
static bool periodic_Task(uint32 factor, uint64 delay, void (*taskCallback)(void));

#endif
