#include "board.h"

/*******************************************************************************
 * Function Name  : Board_GetSystemClock
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void Board_GetSystemClock(void)
{
	RCC_ClocksTypeDef RCC_Clocks;
	
	RCC_GetClocksFreq(&RCC_Clocks);
	
	printf("HCLK_Frequency:%d\n", RCC_Clocks.HCLK_Frequency);
	printf("PCLK1_Frequency:%d\n",RCC_Clocks.PCLK1_Frequency);
	printf("PCLK2_Frequency:%d\n",RCC_Clocks.PCLK2_Frequency);
	printf("HCLK_Frequency:%d\n", RCC_Clocks.SYSCLK_Frequency);
}

/*******************************************************************************
 * Function Name  : Board_LedConfiguration
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void Board_LedConfiguration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//Enable clock
	RCC_AHB1PeriphClockCmd(LED1_PORT_RCC, ENABLE);

	//GPIO_config
	GPIO_InitStruct.GPIO_Mode  	= GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd  	= GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;

	GPIO_InitStruct.GPIO_Pin   	= LED1_PIN;
	GPIO_Init(LED1_PORT, &GPIO_InitStruct);
}

/*******************************************************************************
 * Function Name  : Board_KeyConfiguration
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void Board_KeyConfiguration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//Enable clock
	RCC_AHB1PeriphClockCmd(KEY1_PORT_RCC, ENABLE);

	//GPIO_config
	GPIO_InitStruct.GPIO_Mode  	= GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd  	= GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;

	GPIO_InitStruct.GPIO_Pin   	= KEY1_PIN;
	GPIO_Init(KEY1_PORT, &GPIO_InitStruct);
}

