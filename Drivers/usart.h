#ifndef __USART_H__
#define __USART_H__

#include "board.h"

#define UART1_TX_PORT_RCC 		RCC_AHB1Periph_GPIOA
#define UART1_TX_PORT       	GPIOA
#define UART1_TX_PIN        	GPIO_Pin_9
#define UART1_TX_PIN_SOURCE 	GPIO_PinSource9
#define UART1_TX_AF       		GPIO_AF_USART1

#define UART1_RX_PORT_RCC 		RCC_AHB1Periph_GPIOA
#define UART1_RX_PORT       	GPIOA
#define UART1_RX_PIN        	GPIO_Pin_10
#define UART1_RX_PIN_SOURCE 	GPIO_PinSource10
#define UART1_RX_AF       		GPIO_AF_USART1

#define UART1_PERIPH_RCC 			RCC_APB2Periph_USART1
#define UART1_TX_DMA_CHANNEL  DMA1_Channel4
#define UART1_RX_DMA_CHANNEL  DMA1_Channel5

void UART1_Configuration(void);
void USART1_NVIC_Configuration(void);


#endif
