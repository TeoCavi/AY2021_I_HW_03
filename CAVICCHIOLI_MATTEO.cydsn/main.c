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
#include "project.h"
#include "InterruptRoutines.h"
#include "globalvariables.h"

uint8 flag_UART = 0;


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    int start = 0;

    UART_Start();
    ISR_UART_StartEx(Custom_UART_ISR);
    //ISR_TIMER_StartEx(Custom_TIMER_ISR);
    

    for(;;)
    {
        if (flag_UART == 1)
        {
            if(UART_ReadRxData() == 0xA0)
            {
                start = 1;
            }
            
            
            
        

    }
}

/* [] END OF FILE */
