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
#include "stdio.h"
#include "InterruptRoutines.h"
#include "globalvariables.h"

uint8 flag_UART = 0;
uint8 flag_TIMER = 1;


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    uint8 data;
    uint8 RGB[3] = {'\0'};
    int start = 0, i = 0;

    UART_Start();
    ISR_UART_StartEx(Custom_UART_ISR);
    ISR_TIMER_StartEx(Custom_TIMER_ISR);
    CLK_TIMER_Start();
    
    

    for(;;)
    {
        if (flag_UART == 1 && flag_TIMER == 1)
        {
            data = UART_ReadRxData();
            if (data == 'v' && i == 0)
            {
                UART_PutString("RGB LED Program $$$\r\n");
            }
            else if( data == 0xA0 && i == 0)
            {
                start = 1;
                UART_PutString(" Start ");
                TIMER_UART_Init();
                TIMER_UART_Enable();
                i = 1;
            }
            else if ( data == 0xC0)
            {
                start = 0;
                UART_ClearRxBuffer();
                UART_PutString(" End ");
                TIMER_UART_Stop();
                flag_TIMER = 1;
                i = 0;
            }
            else if (start == 1)
            {
                RGB[i] = data;
                UART_PutChar(RGB[i]);
                TIMER_UART_Stop();
                TIMER_UART_Init();
                TIMER_UART_Enable();

                i ++;
            }
            flag_UART = 0;
        }
        else if (start == 1 && flag_TIMER == 0)
        {
            start = 0;
            UART_ClearRxBuffer();
            TIMER_UART_Stop();
            flag_TIMER = 1;
            UART_PutString(" To Much Time, Repeat ");
            i = 0;
        }

            
        
                
            
            
        
        
                
                
                
                
                
            
            
            
            
        

    }
}

/* [] END OF FILE */
