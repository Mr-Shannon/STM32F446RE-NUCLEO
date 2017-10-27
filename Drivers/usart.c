#include "usart.h"

int16_t data;
uint8_t str_flag = 0;

/*******************************************************************************
 * Function Name  : usart1_init_config
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void UART1_Configuration(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		USART_InitTypeDef USART_InitStruct;
	
		//Enable clock
		RCC_AHB1PeriphClockCmd(UART1_TX_PORT_RCC | UART1_RX_PORT_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(UART1_PERIPH_RCC, ENABLE);
	
		//GPIO_config
		GPIO_InitStruct.GPIO_Mode  	= GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  	= GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;
	
		GPIO_InitStruct.GPIO_Pin   	= UART1_TX_PIN;
		GPIO_Init(UART1_TX_PORT, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin   	= UART1_RX_PIN;
		GPIO_Init(UART1_RX_PORT, &GPIO_InitStruct);
    
		GPIO_PinAFConfig(UART1_TX_PORT, UART1_TX_PIN_SOURCE, GPIO_AF_USART1);
    GPIO_PinAFConfig(UART1_TX_PORT, UART1_RX_PIN_SOURCE, GPIO_AF_USART1);
	
		//USART1_config
		USART_DeInit(USART1);
		USART_InitStruct.USART_BaudRate        			= 115200;//921600;
		USART_InitStruct.USART_StopBits   					= USART_StopBits_1;
		USART_InitStruct.USART_WordLength 					= USART_WordLength_8b;
	  USART_InitStruct.USART_Parity 							= USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;
		USART_OverSampling8Cmd(USART1, ENABLE);
    USART_Init(USART1, &USART_InitStruct);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		USART_Cmd(USART1, ENABLE);
}

/*******************************************************************************
 * Function Name  : usart1_nvic_config
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void USART1_NVIC_Configuration(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;
	
    /* Enable the USART1 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel 										= USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority 				= 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd 								= ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
 * Function Name  : fputc
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (uint8_t) ch );
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    return ch;
}

/*******************************************************************************
 * Function Name  : USART1_IRQHandler
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
static uint8_t str_data[10];
static uint8_t str_len = 0;
void USART1_IRQHandler(void)
{
	uint8_t ch;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		ch = USART_ReceiveData(USART1);
		if(ch != 0x0A)//½áÊø·û"\n"
		{
			str_data[str_len] = ch;
			str_len ++;
		}
		else
		{
			data = tools_str2num(str_data, str_len);
			str_len = 0;
			str_flag = 1;
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}

