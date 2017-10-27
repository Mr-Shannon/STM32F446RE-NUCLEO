#ifndef _SCCB_H_
#define _SCCB_H_

#include <stdint.h>
#include "stm32f4xx.h"
#include "tools.h"

#define SCBB_DRIVER_ADDR				0xd8

#define SCCB_SIOC_PORT 					GPIOB  
#define SCCB_SIOC_PIN  					GPIO_Pin_8
#define SCCB_SIOC_RCC						RCC_AHB1Periph_GPIOB

#define SCCB_SIOD_PORT 					GPIOB  
#define SCCB_SIOD_PIN  					GPIO_Pin_9
#define SCCB_SIOD_RCC						RCC_AHB1Periph_GPIOB

//SCCB ——>SIOC 时钟线
#define SCCB_SIOC_H   					GPIO_SetBits(SCCB_SIOC_PORT,   SCCB_SIOC_PIN)
#define	SCCB_SIOC_L   					GPIO_ResetBits(SCCB_SIOC_PORT, SCCB_SIOC_PIN)

//SCCB ——>SIOD 数据线
#define SCCB_SIOD_H  						GPIO_SetBits(SCCB_SIOD_PORT,   SCCB_SIOD_PIN)
#define	SCCB_SIOD_L  						GPIO_ResetBits(SCCB_SIOD_PORT, SCCB_SIOD_PIN)

typedef enum {
	SCCB_False 	= 0, 
	SCCB_True 	= 1
} SCCB_Status;

SCCB_Status SCCB_WriteReg(uint8_t addr, uint8_t *data, uint16_t len);
SCCB_Status SCCB_ReadReg(uint8_t addr, uint8_t* data,  uint16_t len);
void SCCB_Init(void);

#endif

