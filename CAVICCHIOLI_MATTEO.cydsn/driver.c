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
#include "driver.h"

void Starting_comp(void) //avvio di uart, pwm e clock
{
    UART_Start();
    CLK_TIMER_Start();
    CLK_PWM_Start();
    PWM_RG_Start();
    PWM_B_Start();
}

void Write_DC(uint8 R, uint8 G, uint8 B) /*il clock è settato ad una frequenza molto elevata (> flicker fusion threshold)
                                          quindi settando i DC relativi ai byte ricevuti ottengo i colori desiderati.*/
{
    PWM_RG_WriteCompare1(R);  //scrivo il DC nel compare dei vari PWM
    PWM_RG_WriteCompare2(G);
    PWM_B_WriteCompare(B);
}
    
/* [] END OF FILE */
