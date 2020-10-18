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

uint8 flag_UART = 0;
uint8 flag_TIMER = 0;


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    uint8 data;
    //uint8 DC_red = 0;
    //uint8 DC_green = 0;
    //uint8 DC_blue = 0;
    uint8 RGB[3] = {'\0'};


    UART_Start();
    ISR_UART_StartEx(Custom_UART_ISR);
    ISR_TIMER_StartEx(Custom_TIMER_ISR);
    CLK_TIMER_Start();
    CLK_PWM_Start();
    PWM_RG_Start();
    PWM_B_Start();
    
    uint8 start = 0;
    uint8 stop = 1;
    //uint8 red = 0;
    //uint8 green = 0;
    //uint8 blue = 0;
    uint8 read = 0;
    int i = 0;
    
    for(;;)
    {
        if (flag_TIMER >= 5)
        {
            UART_PutString(" To Much Time, Repeat\r\n");
            TIMER_UART_Stop();
            flag_TIMER = 0;
            stop = 1;
        }
        else if (flag_UART == 1)
        {
            data = UART_ReadRxData();
            if (data == 'v')
            {
                UART_PutString("RGB LED Program $$$\r\n");
                flag_UART = 0;
            }
            else if((flag_UART) && (data == 0xA0) && (stop))
            {
                //UART_PutString(" Start ");
                TIMER_UART_Start();
                flag_TIMER = 0;
                
                start ++;
                stop = 0;
                flag_UART = 0;
                i=0;
                
                
            }
            else if((flag_UART) && (start) && (flag_TIMER < 5))
            {
                //DC_red = data;
                //UART_PutChar(DC_red);
                RGB[i] = data;
                TIMER_UART_Start();
                flag_TIMER = 0;
                //red ++;
                i++;
                if (i == 3)
                {
                    start = 0;
                    read ++;
                }
                flag_UART = 0;   
                
                
            }
            /*else if((red) && (flag_UART) && (flag_TIMER < 5) )
            {
                DC_green = data;
                //UART_PutChar(DC_green);
                TIMER_UART_Start();
                flag_TIMER = 0;
                green  ++;
                red = 0;
                flag_UART = 0;
                
            }
            else if ((green) && (flag_UART) && (flag_TIMER < 5))
            {
                DC_blue = data;
                //UART_PutChar(DC_blue);
                TIMER_UART_Start();
                flag_TIMER = 0;
                blue ++;
                green = 0;
                flag_UART = 0;
                
            }*/
            else if (/*(blue)*/ read && (data == 0xC0) && (flag_UART) && (flag_TIMER < 5))
            {
                //
                //UART_PutString(" End \r\n");
                
                TIMER_UART_Stop();
                stop ++;
                read = 0;
                //blue = 0;
                
                flag_UART = 0;
                
                
                PWM_RG_WriteCompare1(RGB[0]);
                PWM_RG_WriteCompare2(RGB[1]);
                PWM_B_WriteCompare(RGB[2]);
                
            }
    }
    

            
        
                
            
            
        
        
                
                
                
                
                
            
            
            
            
        

    }
}

/* [] END OF FILE */
