#include "sccb.h"

static void SCCB_GPIO_Configuration(void);
static void SCCB_WriteMode(void);
static void SCCB_ReadMode(void);
static void SCCB_Start(void);
static void SCCB_Stop(void);
static void SCCB_Ack(void);
static void SCCB_NAck(void);
static void SCCB_SendData(uint8_t data);
static uint8_t SCCB_ReadData(void);
static SCCB_Status SCCB_CheckAck(void);

/*******************************************************************************
 * Function Name  : SCCB_GPIO_Configuration
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
static void SCCB_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(SCCB_SIOD_RCC, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin   	= SCCB_SIOC_PIN | SCCB_SIOD_PIN;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode  	= GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_OD;
	GPIO_InitStruct.GPIO_PuPd  	= GPIO_PuPd_UP;
	GPIO_Init(SCCB_SIOD_PORT, &GPIO_InitStruct);
}
/*******************************************************************************
 * Function Name  : SCCB_WriteMode
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
static void SCCB_WriteMode(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(SCCB_SIOD_RCC, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin   	= SCCB_SIOD_PIN;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_OD;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_UP;
	GPIO_Init(SCCB_SIOD_PORT, &GPIO_InitStruct); 
}
/*******************************************************************************
 * Function Name  : SCCB_ReadMode
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
static void SCCB_ReadMode(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(SCCB_SIOD_RCC, ENABLE);
	GPIO_InitStruct.GPIO_Pin 		= SCCB_SIOD_PIN;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_OD;
	GPIO_Init(SCCB_SIOD_PORT, &GPIO_InitStruct);
}
/*******************************************************************************
 * Function Name  : SCCB_WriteReg
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
SCCB_Status SCCB_WriteReg(uint8_t addr, uint8_t *data, uint16_t len)
{
	uint16_t i = 0;
	
	SCCB_Start();
	SCCB_SendData(SCBB_DRIVER_ADDR);//器件地址
	if (!SCCB_CheckAck())
		return SCCB_False;	
	SCCB_SendData(addr); //寄存器地址	
	if (!SCCB_CheckAck())
		return SCCB_False;
	for (i = 0; i < len; i++)
	{
		SCCB_SendData(data[i]); //写入的数据	
		if(!SCCB_CheckAck())
			return SCCB_False;
	}
	SCCB_Stop();
	return SCCB_True;
}
/*******************************************************************************
 * Function Name  : SCCB_ReadReg
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
SCCB_Status SCCB_ReadReg(uint8_t addr, uint8_t* data,  uint16_t len)
{   
  uint16_t i = 0;
	
	SCCB_Start();
	SCCB_SendData(SCBB_DRIVER_ADDR); //器件写地址
	if (!SCCB_CheckAck())
		return SCCB_False;
	SCCB_SendData(addr);//寄存器地址	
	if (!SCCB_CheckAck())
		return SCCB_False;
	delay_us(10); 
	SCCB_Start();
	SCCB_SendData(SCBB_DRIVER_ADDR|0x01);//器件读地址
	if (!SCCB_CheckAck())
		return SCCB_False;
	for (i = 0;i < len; i++)
	{
		data[i] = SCCB_ReadData();
		if (i == (len - 1))
			SCCB_NAck();
		else
			SCCB_Ack();
	}
	SCCB_Stop();
	return SCCB_True;
}
/*******************************************************************************
 * Function Name  : SCCB_Start
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
static void SCCB_Start(void)
{
	SCCB_SIOD_H;
	SCCB_SIOC_H;
	delay_us(10);
	SCCB_SIOD_L;
	delay_us(10);
	SCCB_SIOC_L;
	delay_us(10);
}
/*******************************************************************************
 * Function Name  : SCCB_Stop
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/	
static void SCCB_Stop(void)
{
	SCCB_SIOD_L;
	SCCB_SIOC_H;
	delay_us(10);
	SCCB_SIOD_H;
	delay_us(10);
}
/*******************************************************************************
 * Function Name  : SCCB_Ack
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/	
static void SCCB_Ack(void)
{
	SCCB_WriteMode();
	SCCB_SIOD_L;
	SCCB_SIOC_H;
	delay_us(10);
	SCCB_SIOC_L;
	delay_us(10);
}
/*******************************************************************************
 * Function Name  : SCCB_NAck
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/	
static void SCCB_NAck(void)
{
	SCCB_WriteMode();
	SCCB_SIOD_H;
	delay_us(10);
	SCCB_SIOC_H;
	delay_us(10);
	SCCB_SIOC_L;
	delay_us(10);
}
/*******************************************************************************
 * Function Name  : SCCB_SendData
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/	
static void SCCB_SendData(uint8_t data)
{
	uint8_t i;
	SCCB_WriteMode();
	for (i = 0; i < 8; i++)
	{
		if((data << i) & 0x80) 
			SCCB_SIOD_H;	
		else 
			SCCB_SIOD_L;
		SCCB_SIOC_H;
		delay_us(10);
		SCCB_SIOC_L;
		delay_us(10);
	}
}
/*******************************************************************************
 * Function Name  : SCCB_ReadData
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/	
static uint8_t SCCB_ReadData(void )
{
	uint8_t i, data = 0;
	
	SCCB_ReadMode();
	for (i = 0; i < 8; i++)
	{
		SCCB_SIOC_H;
		delay_us(10);
		if (1 == GPIO_ReadInputDataBit(SCCB_SIOD_PORT, SCCB_SIOD_PIN))
			data = (data << 1) | 0x01;
		else
			data = data << 1;		
		SCCB_SIOC_L;
		delay_us(10);
	}
	SCCB_WriteMode();
	return data;
}
/*******************************************************************************
 * Function Name  : SCCB_CheckAck
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
static SCCB_Status SCCB_CheckAck(void)
{
	uint8_t i = 255;
	
	SCCB_Status Status;
	SCCB_ReadMode();
	delay_us(10);
	SCCB_SIOC_H;
	delay_us(10);
	do
	{
		if(0 == GPIO_ReadInputDataBit(SCCB_SIOD_PORT, SCCB_SIOD_PIN))
		{
			Status = SCCB_True;
			break;
		}
		else 
			Status = SCCB_False;
	} while(i--);
	SCCB_SIOC_L;
	delay_ms(10); 
	SCCB_WriteMode();
	return Status ;
}
/*******************************************************************************
 * Function Name  : SCCB_Init
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/	
void SCCB_Init(void)
{
	SCCB_GPIO_Configuration();
	SCCB_WriteMode();
	SCCB_Start();
	SCCB_Stop();
}

