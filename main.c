/*
 * Author:      Ehab Roshdy
 * Version:     0.1
 * Date:        23/8/2023
 * Description: Main program for a stopwatch application using GPIO switches, LCD display, and SysTick timer
 */

#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/SYSTICK/SYSTICK_interface.h"
#include "HAL/LCD/LCD_interface.h"
#include "LIB/defines.h"
#include "LIB/STD_TYPES.h"
#include "private_defines.h"

/* Global variables */
bool running = false; /* Flag to indicate if the stopwatch is running */
uint64 time = 0;      /* Elapsed time in milliseconds */

void updateTime(void);
void PortF_Int(void);

/* Initialize time components */
uint8 milli = 0;
uint8 sec = 0;
uint8 min = 0;
uint8 hours = 0;

uint32 main(void) {
    /* Initialize GPIO pins for switches and LEDs, and LCD display */
    GPIO_Init_Port(PORTF, (SWITCH_1_PIN | SWITCH_2_PIN), (LED_RED_PIN | LED_BLUE_PIN | LED_GREEN_PIN));
    LcdInit(PORTB, 0x0F, PORTB, PIN4, PORTB, PIN5);

    /* Configure interrupt settings for switches on PORTF */
    GPIO_PORTF_IS_R &= ~(0x11 << 0);
    GPIO_PORTF_IBE_R &= ~(0x11 << 0);
    GPIO_PORTF_IEV_R &= ~(0x11 << 0);
    GPIO_PORTF_IM_R |= (0x11 << 0);
    NVIC_EN0_R |= (1 << 30U);
    __asm(" CPSIE i "); /* Enable global interrupts */

    /* Initialize LCD display with "00:00:00.0" */
    LcdSendString("00:00:00.0"); /* "0x80 0x81 : 0x83 0x84 : 0x86 0x87 . 0x89" */

    while (1) { /* Infinite loop */ }

}

/* Interrupt handler for PORTF switches */
void PortF_Int(void) {

    /* Check if switch 1 is pressed */
    if (GPIO_PORTF_MIS_R & 0x1) {
        time = 0;         /* Reset time */
        running = true;   /* Start the stopwatch */
        LcdSendCommand(0x01); /* Clear LCD display */
        LcdSendCommand(0x80); /* Move cursor to the first line */
        LcdSendString("00:00:00.0"); /* Display "00:00:00.0" */
        Systick_Stop_Timer();
        Systick_Wait_Periodic_Task_Milli_Sec(100, updateTime);
        GPIO_PORTF_ICR_R |= (1 << 0); /* Clear interrupt flag for switch 1 */
    }
    /* Check if switch 2 is pressed */
    else if ((GPIO_PORTF_MIS_R & 0x10) == 0x10) {
        /* Toggle the running state of the stopwatch */
        if (running) {
            Systick_Pause_Timer();
        } else {
            Systick_Continue_Timer();
        }
        running = !running;

        GPIO_PORTF_ICR_R |= (1 << 4); /* Clear interrupt flag for switch 2 */
    }
    else {}
}

void updateTime(void) {
    ++time;
    milli = time % 10;

    if (min == 0 && sec == 0 && milli == 0) {
        hours = time / 36000;
        LcdSendCommand(0x80);
        LcdSendData((hours / 10) + '0');
        LcdSendData((hours % 10) + '0');
        LcdSendData(':');
        LcdSendData('0');
        LcdSendData('0');
        LcdSendData(':');
        LcdSendData('0');
        LcdSendData('0');
        LcdSendData('.');
        /* LcdSendData('0'); */
    }
    if (sec == 0 && milli == 0) {
        min = (time / 600) % 60;
        LcdSendCommand(0x83);
        LcdSendData((min / 10) + '0');
        LcdSendData((min % 10) + '0');
        LcdSendData(':');
        LcdSendData('0');
        LcdSendData('0');
        LcdSendData('.');
        /* LcdSendData('0'); */
    }
    if (milli == 0) {
        sec = (time / 10) % 60;
        LcdSendCommand(0x86);
        LcdSendData((sec / 10) + '0');
        LcdSendData((sec % 10) + '0');
        LcdSendData('.');
        /* LcdSendData('0'); */
    }

    /* Update millisecond part on LCD display */
    LcdSendCommand(0x89);
    LcdSendData(milli + '0');
}
