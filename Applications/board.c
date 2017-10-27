#include "board.h"

void Board_GetSystemClock(void)
{
	RCC_ClocksTypeDef RCC_Clocks;
	
	RCC_GetClocksFreq(&RCC_Clocks);
	
	printf("HCLK_Frequency:%d\n", RCC_Clocks.HCLK_Frequency);
	printf("PCLK1_Frequency:%d\n",RCC_Clocks.PCLK1_Frequency);
	printf("PCLK2_Frequency:%d\n",RCC_Clocks.PCLK2_Frequency);
	printf("HCLK_Frequency:%d\n", RCC_Clocks.SYSCLK_Frequency);
}

