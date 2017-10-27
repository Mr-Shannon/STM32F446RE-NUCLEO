#include "board.h"

int main(void)
{
	
	UART1_Configuration();
//	USART1_NVIC_Configuration();
	printf(" Hello World!\n");
	SCCB_Init();

	delay_ms(100);
	Board_GetSystemClock();
}


