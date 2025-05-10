#include "CH59x_common.h"

int main(void) {
    SetSysClock(CLK_SOURCE_PLL_60MHz);
    GPIOA_ModeCfg(GPIO_Pin_4, GPIO_ModeOut_PP_20mA);
    GPIOB_ModeCfg(GPIO_Pin_12, GPIO_ModeOut_PP_20mA);
    

    while (1) {
    	GPIOA_SetBits(GPIO_Pin_4);
        GPIOB_SetBits(GPIO_Pin_12);
        DelayMs(1000);

		GPIOA_ResetBits(GPIO_Pin_4);
        GPIOB_ResetBits(GPIO_Pin_12);
        DelayMs(1000);
    }
}

