/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "InterruptRoutines.h"
#include "stdio.h"
#include "UART.h"
#include "TIMER_UART.h"

extern uint8 flag_UART;
extern uint8 flag_TIMER;

CY_ISR(Custom_UART_ISR)
{
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY) //se è arrivato un byte la costante del registro è uguale a 1 e mi permette l'incremento del flag
        flag_UART = 1;
}

CY_ISR(Custom_TIMER_ISR)
{
    flag_TIMER ++;  //all'overflow del timer settato ad 1s il flag viene incrementato di 1.
    TIMER_UART_ReadStatusRegister(); //mantiene bassa la linea di interrupt.
}

    

/* [] END OF FILE */
