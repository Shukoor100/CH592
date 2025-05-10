#include "CH59x_common.h"

uint8_t RxBuff[100];

int main()
{
    uint8_t len;

    SetSysClock(CLK_SOURCE_PLL_60MHz);


    GPIOA_SetBits(GPIO_Pin_9);                      //TXD  
    GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeIN_PU);     //RXD
    GPIOA_ModeCfg(GPIO_Pin_9, GPIO_ModeOut_PP_5mA); 
	
	while(1)
   {
   		//Send a string to UART1
   		PRINT("Hell World\r\n");
    	DelayMs(1000);

        while(1){
            //Receive a string from UART1
            len = UART1_RecvString(RxBuff);
            if(len>0)
            {
                //Send the received string back to UART1
                UART1_SendString(RxBuff, len);
                DelayMs(1000);
            }
        }
        
   }
}