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

CY_ISR(Custom_UART_ISR)
{
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY) // && flag_TIMER == 0)
        flag_UART ++;
}

/*CY_ISR_PROTO(Custom_TIMER_ISR);
{
    if(UART_ReadRxStatus() != UART_RX_STS_FIFO_NOTEMPTY && flag_UART == 1)
        flag_TIMER = 1;
}*/

    

/* [] END OF FILE */
