#include "board.h"

int main(void)
{
	Board_LedConfiguration();
	
	UART1_Configuration();
	printf(" Hello World!\n");
	SCCB_Init();
	LED1_ON();
	delay_ms(100);
	Board_GetSystemClock();
}


