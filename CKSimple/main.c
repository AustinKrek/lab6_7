/**
 * lab6_template_extra_help.c
 *
 * Description: This is file is meant for those that would like a little
 *              extra help with formatting their code.
 *
 */

#define _RESET 0
#define _PART1 0
#define _PART2 0
#define _PART3 0
#define _PART4 1

#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include "scanAuto.h"
#include "movement.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "uart_extra_help.h"

#if _RESET
//#include "Simulation_User Files_resetSimulation.h"
#endif

// Adding global volatile varibles for communcating between 
// your Interupt Service Routine, and your non-interupt code.

//volatile  char uart_data;  // Your UART interupt code can place read data here
volatile  char move = '0';       // Your UART interupt can update this flag
volatile char flag = '0';                       // to indicate that it has placed new data
                           // in uart_data                     


void main()
{
#if _RESET
    resetSimulationBoard();
#else
    oi_t *sensor = oi_alloc();
    oi_init(sensor);
    uart_initB(115200);
    uart_interrupt_initB();
    timer_init();
    lcd_init();
#if _PART1      // Receive and display text
    // TODO
    while(1)
    {
        lcd_printf("%c",uart_receiveB());
    }
#endif

#if _PART2      // Echo Received Character
	// TODO
    char rece = '\0';
    while(1)
    {
        rece = uart_receiveB();
        uart_sendCharB(rece);
    }
#endif

#if _PART3 // Receive and send characters using interrupts.
 // TODO

    while(1)
    {
    }
#endif

#if _PART4 // Receive and send characters using interrupts.
 // TODO

    while(1)
    {
        if(flag == '1')
        {
            scanAuto(sensor,1);
            flag = 0;

        }

        if (flag == '0'){
            if(move == 'w')
            {
                manualForward(sensor);
            }
            if(move == 'a')
            {
                manualTurnL(sensor);
            }
            if(move == 's')
            {
                manualBackward(sensor);
            }
            if(move == 'd')
            {
                manualTurnR(sensor);
            }
            if(move == 'h')
            {
                manualStop(sensor);
            }
            if(move == 'm')
            {
                manualScan(sensor);
                move = 'k';
            }
        }
    }
#endif
oi_free(sensor);
#endif
}

