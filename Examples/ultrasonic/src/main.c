#include "CH59x_common.h"

#define TRIG_PIN    GPIO_Pin_7  
#define ECHO_PIN    GPIO_Pin_9  

uint16_t getDistance() {
    uint32_t pulseWidth;
    uint16_t distance;

    GPIOB_ResetBits(TRIG_PIN);  
    DelayUs(2);
    GPIOB_SetBits(TRIG_PIN);    
    DelayUs(10);                 
    GPIOB_ResetBits(TRIG_PIN); 
    
    while (!GPIOA_ReadPortPin(ECHO_PIN));  // Wait for pulse start
    R32_TMR0_FIFO = 0;
    while (GPIOA_ReadPortPin(ECHO_PIN));   // Wait for pulse end

    pulseWidth = TMR0_CAPGetData() &= 0x1FFFFFF;
    distance = ((pulseWidth - 7700) * (15 - 1)) / (50000 - 7700) + 1;
    
    return distance;
}

void DebugInit(void)
{
    GPIOA_SetBits(GPIO_Pin_5);
    GPIOA_ModeCfg(GPIO_Pin_5, GPIO_ModeOut_PP_5mA);
    UART3_DefInit();
}

int main() {
    SetSysClock(CLK_SOURCE_PLL_60MHz);  

    TMR0_CapInit(Edge_To_Edge);
    TMR0_CAPTimeoutCfg(30000000);   

    GPIOB_ModeCfg(TRIG_PIN, GPIO_ModeOut_PP_5mA);
    GPIOA_ModeCfg(ECHO_PIN, GPIO_ModeIN_PU);
    DebugInit();     
    

    while (1) {
        
        PRINT("Distance: %u cm\n", getDistance());
        DelayMs(50);

    }
}
