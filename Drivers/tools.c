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
			printf("�Ƿ��ַ�:%x %d��\r\n",ch[i],i);
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

void delay_us(uint32_t nus) //΢����ʱ
{
	uint32_t temp;
	SysTick->LOAD = 9*nus;
	SysTick->VAL=0X00;//��ռ�����
	SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
	do
	{
	  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	}while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	 
	SysTick->CTRL=0x00; //�رռ�����
	SysTick->VAL =0X00; //��ռ�����
}

void delay_ms(uint16_t nms) //������ʱ
{
	uint32_t temp;
	SysTick->LOAD = 9000*nms;
	SysTick->VAL=0X00;//��ռ�����
	SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
	do
	{
	  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	}while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	SysTick->CTRL=0x00; //�رռ�����
	SysTick->VAL =0X00; //��ռ�����
}

