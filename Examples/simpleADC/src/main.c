#include "CH59x_common.h"

uint16_t adcBuff[40];
uint8_t buff[6];
int val;

volatile uint8_t adclen;

void DebugInit(void)
{
    GPIOA_SetBits(GPIO_Pin_5);
    GPIOA_ModeCfg(GPIO_Pin_5, GPIO_ModeOut_PP_5mA);
    UART3_DefInit();
}

int main()
{
    uint8_t      i;
    signed short RoughCalib_Value = 0; // ADC
	
    SetSysClock(CLK_SOURCE_PLL_60MHz);

    DebugInit();
	
    GPIOA_ModeCfg(GPIO_Pin_6, GPIO_ModeIN_Floating);
    ADC_ExtSingleChSampInit(SampleFreq_3_2, ADC_PGA_0);

    RoughCalib_Value = ADC_DataCalib_Rough(); 

    ADC_ChannelCfg(10);

    while(1)
    {

    	val = ADC_ExcutSingleConver() + RoughCalib_Value;
    	if(val < 0) val = 0;
       	snprintf(buff, sizeof(buff), "%d\n", val);
        UART3_SendString(buff, sizeof(buff)-1);
    	DelayMs(10);
    }

}
