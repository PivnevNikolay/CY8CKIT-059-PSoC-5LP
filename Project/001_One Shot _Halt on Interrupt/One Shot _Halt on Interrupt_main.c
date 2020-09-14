// 06.09.2020

#include "project.h"
uint8_t Count = 0;
//***********обработчик_прерывания*******************//
CY_ISR(Timer_interrupt_Handler){
    Count = 1;
    isr_1_ClearPending();
}
//***************************************************//
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */    
    isr_1_StartEx(Timer_interrupt_Handler);
    for(;;)
    {
         switch(Count){      
    case 0:
         if(Status_Reg_Read()==0x1){
            Control_Reg_Write(0x00);
            Timer_Start();
            Count = 2;
        }
    break;
    case 1:
        Control_Reg_Write(0x1);
        Timer_Stop();
        Status_Pin_Write(~Status_Pin_Read());
        Count = 0;
    break;
    case 2:
        Pin_LED_Write(~Pin_LED_Read());
        CyDelay(100);
    break;
        }
    }
}

/* [] END OF FILE */
