/* 06.09.2020
----------------------------
Configure timer_clock = 8MHz
----------------------------
Configure Pin_1 -->
Digital input
HW connection
Drive mode --> Resistive pull down
Initial drive state --> LOW(0)
значения Input без изменений 
----------------------------
Configure Pin_2 -->
Digital input
HW connection
Drive mode --> Resistive pull down
Initial drive state --> LOW(0)
значения Input без изменений 
----------------------------
Configure Status_Pin -->
Digital output
Strong drive 
Initial drive state --> High(1)
значения Output без изменений 
----------------------------
Configure Pin_LED -->
Digital output
Strong drive 
Initial drive state --> High(1)
значения Output без изменений 
----------------------------
Configure Status_Reg -->
Inputs 1
Bit 0
Mode Transparent
----------------------------
Configure Control_Reg -->
Outputs 1
Bit 0
Mode Direct
Initial value 0
----------------------------
Configure Timer -->
Resolution 32 bit
Implementation UDB
Period 4000000 Period 500 ms
Trigger mode: None
Capture Mode: None
Enable mode: Software only 
Run Mode: One Shot(Halt On Interrupt)
Interrupts: On TC 
----------------------------
+ isr_1 interrupt Timer 
*/
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
