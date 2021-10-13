/*
*
*   uart_extra_help.c
* Description: This is file is meant for those that would like a little
*              extra help with formatting their code, and followig the Datasheet.
*/

#include "uart.h"
#include "timer.h"
#define REPLACE_ME 0x00
//for | 1=1 0=x ;; for & 1=x 0=0
extern volatile char flag;
extern volatile char move;

void uart_initB(int baud)
{
    SYSCTL_RCGCGPIO_R |= 0b00000010;      // enable clock GPIOB (page 340)
    SYSCTL_RCGCUART_R |= 0b00000010;      // enable clock UART1 (page 344)
    GPIO_PORTB_AFSEL_R |= 0b00000011;      // sets PB0 and PB1 as peripherals (page 671)
    GPIO_PORTB_PCTL_R &= 0xffffff00;     // Force 0's in the disired locations
    GPIO_PORTB_PCTL_R |= 0x00000011;
    GPIO_PORTB_DEN_R  |= 0b00000011;        // enables pb0 and pb1
    GPIO_PORTB_DIR_R &= 0b11111110;      // Force 0's in the disired locations
    GPIO_PORTB_DIR_R |= 0b00000010;        // sets pb0 as output, pb1 as input

    //compute baud values [UART clock= 16 MHz] 
    double fbrd;
    int    ibrd;

    fbrd = 0.5; // page 903
    ibrd = 16000000 / (16* baud);
    fbrd = fbrd + (0.680555*64);

    UART1_CTL_R &= 0b1111111111111110;           // disable UART1 (page 918)
    UART1_IBRD_R = ibrd;                 // write integer portion of BRD to IBRD
    UART1_FBRD_R = fbrd;                 // write fractional portion of BRD to FBRD
    UART1_LCRH_R |= 0b01100000;           // write serial communication parameters (page 916) * 8bit and no parity
   // UART1_LCRH_R &= 0b11110101;           // write serial communication parameters (page 916) * 8bit and no parity
    UART1_CC_R   &= 0b0000;           // use system clock as clock source (page 939)
    UART1_CTL_R |= 0b0000001100000001;           // enable UART1

}

void uart_sendCharB(char data)  //ex char = 0b01010101
{
   //TODO

    while(UART1_FR_R & 0b00100000)
    {

    }


    UART1_DR_R = data;
}

char uart_receiveB(void)
{
 //TODO
    char ret = 0;

    while((UART1_FR_R & 0b00010000) != 0)
        {

        }

    ret = UART1_DR_R & 0b000011111111;
   return ret;
}

void uart_sendStrB(char *data)
{
    //TODO
    int i = 0;
    //int end = sizeof(*data);
    while (data[i] != '\0')
    {
        uart_sendCharB(data[i]);
        i++;
    }
}

// _PART3

void uart_interrupt_handlerB()
{
// STEP1: Check the Masked Interrupt Status
    //recieve
    char ch = uart_receiveB();
    if((UART1_MIS_R & 0b000000010000) == 0b000000010000)
    {
        uart_sendCharB(ch);
    }


    //0 = manual 1 = auto
    if (ch == 't'){
        if (flag == '0')
        {
            flag = '1';
        }

        else if (flag == '1')
        {
            flag = '0';
        }
    }

    if(flag != '1' && flag != '0')
    {
        flag = '0';
    }

    if(flag == '0')
    {
        // CALL MOVE MANUAL
        if(ch == 'w')
        {
            move = 'w';
        }
        if(ch == 'a')
        {
            move = 'a';
        }
        if(ch == 's')
        {
            move = 's';
        }
        if(ch == 'd')
        {
            move = 'd';
        }
        if(ch == 'h')
        {
            move = 'h';
        }
        if(ch == 'm')
        {
            move = 'm';
        }

    }


//STEP3:  Clear the interrupt
    UART1_ICR_R |= 0b000000010000;
}

void uart_interrupt_initB()
{
    // Enable interrupts for receiving bytes through UART1
    UART1_IM_R |= 0b000000010000; //enable interrupt on receive - page 924

    //Find the NVIC enable register and bit responsible for UART1 in table 2-9
    //Note: NVIC register descriptions are found in chapter 3.4
    NVIC_EN0_R |= 0x00000040; //enable uart1 interrupts - page 104

    // Find the vector number of UART1 in table 2-9 ! UART1 is 22 from vector number page 104
    IntRegister(INT_UART1, uart_interrupt_handlerB); //give the microcontroller the address of our interrupt handler - page 104 22 is the vector number
}


