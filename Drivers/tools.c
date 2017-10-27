#include "tools.h"

/*******************************************************************************
 * Function Name  : assert_failed
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{ 
	printf(" file:%s\n  line:%d\n",file,line);
  while (1)
  {		
  }
}
/*******************************************************************************
 * Function Name  : tools_str2num
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
int16_t tools_str2num(uint8_t *ch, uint16_t len)
{
	uint16_t i = 0;
	int16_t num = 0;
	
	for(i = 0; i < len ; i++)
	{
		if((ch[i] >= '0' && ch[i] <= '9') || (ch[0] == '-'));
		else 
		{
			printf("非法字符:%x %d！\r\n",ch[i],i);
			return 0;
		}
	}
	
	if(ch[0] == '-') 
	{
			for( i = 1; i < len; i++)
			{
				num += (ch[i]-'0')*pow(10,(len-1-i));
			}
			num = -num;
	}
	else
	{
			for( i = 0; i < len; i++)
			{
				num += (ch[i]-'0')*pow(10,(len-1-i));
			}
	}
	
	return num;
}

void delay_us(uint32_t nus) //微秒延时
{
	uint32_t temp;
	SysTick->LOAD = 9*nus;
	SysTick->VAL=0X00;//清空计数器
	SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
	do
	{
	  temp=SysTick->CTRL;//读取当前倒计数值
	}while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
	 
	SysTick->CTRL=0x00; //关闭计数器
	SysTick->VAL =0X00; //清空计数器
}

void delay_ms(uint16_t nms) //毫秒延时
{
	uint32_t temp;
	SysTick->LOAD = 9000*nms;
	SysTick->VAL=0X00;//清空计数器
	SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
	do
	{
	  temp=SysTick->CTRL;//读取当前倒计数值
	}while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
	SysTick->CTRL=0x00; //关闭计数器
	SysTick->VAL =0X00; //清空计数器
}

