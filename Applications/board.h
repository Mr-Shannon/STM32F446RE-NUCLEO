#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdio.h>
#include "stm32f4xx.h"
#include "tools.h"
#include "usart.h"
#include "sccb.h"

#define LED1_PORT_RCC 		RCC_AHB1Periph_GPIOA
#define LED1_PORT       	GPIOA
#define LED1_PIN        	GPIO_Pin_5
#define LED1_ON()					GPIO_SetBits(LED1_PORT,LED1_PIN)
#define LED1_OFF()				GPIO_ResetBits(LED1_PORT,LED1_PIN)
#define LED1_TOGGLE()			GPIO_ToggleBits(LED1_PORT,LED1_PIN)

#define KEY1_PORT_RCC 		RCC_AHB1Periph_GPIOC
#define KEY1_PORT       	GPIOC
#define KEY1_PIN        	GPIO_Pin_13


void Board_GetSystemClock(void);
void Board_LedConfiguration(void);
void Board_KeyConfiguration(void);


#endif

