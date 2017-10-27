#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "stm32f4xx.h"
#include "stdint.h"
#include "stdio.h"
#include "math.h"


int16_t tools_str2num(uint8_t *ch, uint16_t len);
void delay_us(uint32_t nus);//Œ¢√Î—” ±
void delay_ms(uint16_t nms); //∫¡√Î—” ±

#endif
