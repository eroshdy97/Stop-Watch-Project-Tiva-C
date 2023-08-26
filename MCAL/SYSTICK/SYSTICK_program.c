/*
 * Author:      Ehab Roshdy
 * Version:     0.1
 * Date:        23/8/2023
 * Description: SYSTICK driver program file
*/

#include "MCAL/SYSTICK/SYSTICK_interface.h"
#include "MCAL/SYSTICK/SYSTICK_private.h"
#include "MCAL/SYSTICK/SYSTICK_config.h"

#include "LIB/STD_TYPES.h"

//////////////////////////////////////////////////////////////////////////////////////////////

// Function to implement a busy-wait delay
static bool busy_Wait(uint32 factor, uint64 delay)
{
    switch (GET_BIT(NVIC_ST_CTRL_R, 0))
    {
        case 0:
        {
            // Calculate delay in SysTick ticks
            uint64 delayToTicks = (delay * (SYSTICK_PRESCALER_FREQ * (1 + 3 * useSystemClock)) / factor) - 1;
            numberOfOverflows = (delayToTicks / SYSTICK_MAX_TICKS) + 1;
            uint32 value = (delayToTicks / numberOfOverflows);

            // Configure SysTick for busy-wait delay
            SET_BIT(NVIC_ST_CTRL_R, 0);
            NVIC_ST_RELOAD_R = value;
            NVIC_ST_CURRENT_R = value;

            // Wait for specified number of overflows
            while (numberOfOverflows > 0) {
                while (GET_BIT(NVIC_ST_CTRL_R, 16) == 0);
                --numberOfOverflows;
            }

            // Reinitialize SysTick
            SysTick_Force_Init(useSystemClock);
            return true;
            break;
        }
        default:
            return false;
            break;
    }
}

// Function to implement asynchronous delay with a callback
static bool wait_Async(uint32 factor, uint64 delay, void (*taskCallback)(void)) {
    switch (GET_BIT(NVIC_ST_CTRL_R, 0)) {
        case 0:
        {
            // Calculate delay in SysTick ticks
            uint64 delayToTicks = (delay * (SYSTICK_PRESCALER_FREQ * (1 + 3 * useSystemClock)) / factor) - 1;
            numberOfOverflows = (delayToTicks / SYSTICK_MAX_TICKS) + 1;
            uint32 value = (delayToTicks / numberOfOverflows);

            // Configure SysTick for asynchronous delay
            counter = 0;
            isContinues = false;
            delayCompleteCallback = taskCallback;
            SET_BIT(NVIC_ST_CTRL_R, 1);
            SET_BIT(NVIC_ST_CTRL_R, 0);
            NVIC_ST_RELOAD_R = value;
            NVIC_ST_CURRENT_R = value;
            return true;
            break;
        }
        default:
            return false;
            break;
    }
}

// Function to implement busy-wait periodic task execution
static bool busy_Wait_Periodic_Task(uint32 factor, uint64 delay, void (*taskCallback)(void)) {
    switch (GET_BIT(NVIC_ST_CTRL_R, 0)) {
        case 0:
        {
            // Calculate delay in SysTick ticks
            uint64 delayToTicks = (delay * (SYSTICK_PRESCALER_FREQ * (1 + 3 * useSystemClock)) / factor) - 1;
            numberOfOverflows = (delayToTicks / SYSTICK_MAX_TICKS) + 1;
            uint32 value = (delayToTicks / numberOfOverflows);

            // Configure SysTick for busy-wait periodic task
            counter = numberOfOverflows;
            SET_BIT(NVIC_ST_CTRL_R, 0);
            NVIC_ST_RELOAD_R = value;
            NVIC_ST_CURRENT_R = value;

            // Execute the task periodically
            while (1) {
                while (counter > 0) {
                    while (GET_BIT(NVIC_ST_CTRL_R, 16) == 0);
                    --counter;
                }
                taskCallback();
                counter = numberOfOverflows;
            }

            // Reinitialize SysTick
            SysTick_Force_Init(useSystemClock);
            return true;
            break;
        }
        default:
            return false;
            break;
    }
}

// Function to implement periodic task execution
static bool periodic_Task(uint32 factor, uint64 delay, void (*taskCallback)(void)) {
    switch (GET_BIT(NVIC_ST_CTRL_R, 0)) {
        case 0:
        {
            // Calculate delay in SysTick ticks
            uint64 delayToTicks = (delay * (SYSTICK_PRESCALER_FREQ * (1 + 3 * useSystemClock)) / factor) - 1;
            numberOfOverflows = (delayToTicks / SYSTICK_MAX_TICKS) + 1;
            uint32 value = (delayToTicks / numberOfOverflows);

            // Configure SysTick for periodic task execution
            counter = numberOfOverflows;
            isContinues = true;
            delayCompleteCallback = taskCallback;
            SET_BIT(NVIC_ST_CTRL_R, 1);
            SET_BIT(NVIC_ST_CTRL_R, 0);
            NVIC_ST_RELOAD_R = value;
            NVIC_ST_CURRENT_R = value;
            return true;
            break;
        }
        default:
            return false;
            break;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////

// Initialize the SysTick timer
bool SysTick_Init(bool useSystemClock) {
    switch (GET_BIT(NVIC_ST_CTRL_R, 0)) {
        case 0:
        {
            useSystemClock = useSystemClock;
            // Configure SysTick control registers
            NVIC_ST_CTRL_R = (useSystemClock << 2);
            NVIC_ST_RELOAD_R = 0;
            NVIC_ST_CURRENT_R = 0;
            counter = 0;
            numberOfOverflows = 0;
            isContinues = false;
            return true;
            break;
        }
        default:
            return false;
            break;
    }
}

// Forcefully reinitialize the SysTick timer
void SysTick_Force_Init(bool useSystemClock) {
    useSystemClock = useSystemClock;
    // Reconfigure SysTick control registers and reset state
    NVIC_ST_CTRL_R = (useSystemClock << 2);
    NVIC_ST_RELOAD_R = 0;
    NVIC_ST_CURRENT_R = 0;
    counter = 0;
    numberOfOverflows = 0;
    isContinues = false;
}

// Provide busy-wait delay in milliseconds
bool SysTick_Busy_Wait_Milli_Sec(uint64 delay) {
    return busy_Wait(1000, delay);
}

// Provide busy-wait delay in microseconds
bool SysTick_Busy_Wait_Micro_Sec(uint64 delay) {
    return busy_Wait(1000000, delay);
}

// Provide asynchronous delay in milliseconds with a callback
bool Systick_Wait_Async_Milli_Sec(uint64 delay, void (*taskCallback)(void)) {
    return wait_Async(1000, delay, taskCallback);
}

// Provide asynchronous delay in microseconds with a callback
bool Systick_Wait_Async_Micro_Sec(uint64 delay, void (*taskCallback)(void)) {
    return wait_Async(1000000, delay, taskCallback);
}

// Provide busy-wait periodic task execution in milliseconds
bool Systick_Busy_Wait_Periodic_Task_Milli_Sec(uint64 delay, void (*taskCallback)(void)) {
    return busy_Wait_Periodic_Task(1000, delay, taskCallback);
}

// Provide busy-wait periodic task execution in microseconds
bool Systick_Busy_Wait_Periodic_Task_Micro_Sec(uint64 delay, void (*taskCallback)(void)) {
    return busy_Wait_Periodic_Task(1000000, delay, taskCallback);
}

// Provide periodic task execution in milliseconds
bool Systick_Wait_Periodic_Task_Milli_Sec(uint64 delay, void (*taskCallback)(void)) {
    return periodic_Task(1000, delay, taskCallback);
}

// Provide periodic task execution in microseconds
bool Systick_Wait_Periodic_Task_Micro_Sec(uint64 delay, void (*taskCallback)(void)) {
    return periodic_Task(1000000, delay, taskCallback);
}

// Forcefully stop the timer
void Systick_Stop_Timer() {
    SysTick_Force_Init(useSystemClock);
}

void Systick_Pause_Timer()
{
    CLEAR_BIT(NVIC_ST_CTRL_R, 0);
}

void Systick_Continue_Timer()
{
    SET_BIT(NVIC_ST_CTRL_R, 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////

// SysTick interrupt handler
void SysTickInterruptHandler(void)
{
    switch (isContinues) {
        case false:
            switch (numberOfOverflows) {
                case 1:
                    // Execute task callback and reset timer
                    delayCompleteCallback();
                    SysTick_Force_Init(useSystemClock);
                    break;

                default:
                    --numberOfOverflows;
                    break;
            }
            break;

        case true:
            switch (counter) {
                case 1:
                    // Execute task callback and reset counter
                    delayCompleteCallback();
                    counter = numberOfOverflows;
                    break;

                default:
                    --counter;
                    break;
            }
            break;
    }
}
