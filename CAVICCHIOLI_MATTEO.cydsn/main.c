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
#include "driver.h"
#include "stdio.h"
#include "InterruptRoutines.h"

uint8 flag_UART = 0;                             //variabili globali per lo stato di UART e Timer
uint8 flag_TIMER = 0;

int main(void)
{
    CyGlobalIntEnable;                           //abilita gli interrupt globali. 
    
    ISR_UART_StartEx(Custom_UART_ISR);           //abilita l'isr dell UART (priorità 6)
    ISR_TIMER_StartEx(Custom_TIMER_ISR);         //abilita l'isr del timer (priorità 7) 
    
                                                 /*se le due isr arrivano in contemporanea voglio 
                                                   che il dato non venga letto (priorità al timer)*/
    
    Starting_comp();                             //accensione dei vari componenti, definita in driver.c
    
    uint8 data;                                  //byte ricevuto
    uint8 RGB[3] = {'\0'};                       /*array che contiene i duty cicle relativi ai vari colori 
                                                   ricevuti come pacchetto di byte*/

    uint8 start = 0;                             //variabili che indicano lo stato; inizialmente siamo in fase di stop.
    uint8 read = 0;
    uint8 stop = 1;
    
    uint8 i = 0;                                 //variabile di memorizzazione array
    
    for(;;)
    {
        if (flag_TIMER >= MAX_TIME)              /*Se il timer, dopo essere attivato in seguito all'inizio 
                                                   della lettura, supera i 5s viene stoppato. i flag viengono resettati
                                                   e si ritorna nella condizione di idle.*/                                        
        {
            UART_PutString(" To Much Time, Repeat\r\n");
            TIMER_UART_Stop();
            flag_TIMER = RESET_TIMER;
            flag_UART = BYTE_WAIT;
            stop = 1;
        }
        else if (flag_UART == BYTE_AVAILABLE)    //se l'UART riceve un byte alza il flag e abilita questo if
        {
            data = UART_ReadRxData();
            if (data == CHECK)                   //se il byte è 'v' allora restituisce su tx la seguente striga
            
            {
                UART_PutString("RGB LED Program $$$\r\n");
                flag_UART = BYTE_WAIT;
            }
            
            else if((data == START) && (stop))   /*se il byte è 0xA0 allora inizia la lettura. imposto start = 1, 
                                                   stop = 0 e avvio il timer*/
            {
                TIMER_UART_Start();
                flag_TIMER = RESET_TIMER;
                
                start ++;
                stop = 0;
                
                flag_UART = BYTE_WAIT;
                i=0;
            }
            
            else if((start) && (flag_TIMER < MAX_TIME)) /*una volta ricevuto lo start vengono inseriti i successivi 3 byte all'interno
                                                          dell'array RGB, in modo da settare successivamente i pwm.*/
            {
                RGB[i] = data;
                TIMER_UART_Start();
                flag_TIMER = RESET_TIMER;
                i++;
                if (i == 3)                     /*se sono stati ricevuti tutti e tre i byte, allora si passa alla fase
                                                  di idle. start = 0, read = 1 (lettura completata) */
                {
                    start = 0;
                    read ++;
                }
                
                flag_UART = BYTE_WAIT;    
            }
            else if ((read) && (data == STOP) && (flag_TIMER < MAX_TIME)) /*finalizzazione della fase di lettura con
                                                                            azzeramento di flag UART. stop = 1. successivamente settaggio PWM.*/
            {
                TIMER_UART_Stop();
                
                stop ++;
                read = 0;
                
                flag_TIMER = RESET_TIMER;
                flag_UART = BYTE_WAIT;
                
                Write_DC(RGB[0],RGB[1], RGB[2]);
            }
    }
    

            
        
                
            
            
        
        
                
                
                
                
                
            
            
            
            
        

    }
}

/* [] END OF FILE */
