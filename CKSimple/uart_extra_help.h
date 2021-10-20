/*
*   uart.h
*   Used to set up the UART [UART1 at 115200]
*
 * Description: This is file is meant for those that would like a little
 *              extra help with formatting their code.
*/

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

// These two varbles have been declared
// in the file containing main
extern volatile  char uart_data;  // Your UART interupt code can place read data here
extern volatile char flag;       // Your UART interupt can update this flag
                                  // to indicate that it has placed new data
                                  // in uart_data       


void uart_initB(int baud);

void uart_sendCharB(char data);

char uart_receiveB(void);

void uart_sendStrB(const char *data);

void uart_interrupt_initB();

void uart_interrupt_handlerB();

#endif /* UART_H_ */
