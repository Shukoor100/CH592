#include "CH59x_common.h"
#define p1 GPIO_Pin_8
#define p2 GPIO_Pin_6
#define p3 GPIO_Pin_7

int main(void) {
    SetSysClock(CLK_SOURCE_PLL_60MHz);
    GPIOA_ModeCfg(p1, GPIO_ModeIN_PD);
    GPIOA_ModeCfg(p2, GPIO_ModeIN_PD);
    GPIOA_ModeCfg(p3, GPIO_ModeIN_PD);
    GPIOB_ModeCfg(GPIO_Pin_12, GPIO_ModeOut_PP_20mA);

    while (1) {
        if(GPIOA_ReadPortPin(p1) && GPIOA_ReadPortPin(p2) && GPIOA_ReadPortPin(p3))
        	GPIOB_SetBits(GPIO_Pin_12);
        else
        	GPIOB_ResetBits(GPIO_Pin_12);
    }
}

