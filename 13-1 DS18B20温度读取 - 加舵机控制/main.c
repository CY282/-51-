#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "Delay.h"
#include "timer0.h"

float T;
unsigned int k;
sbit SG_PWM=P2^0;							
unsigned char count=0;					     
unsigned char PWM_count=0;    

void main()
{
	DS18B20_ConvertT();		//上电先转换一次温度，防止第一次读数据错误
	Delay(1000);			//等待转换完成
	LCD_Init();
	Timer0_Init();
	LCD_ShowString(1,1,"Temperature:");
	
	while(1)
	{
		TR0 = 0;
		DS18B20_ConvertT();	//转换温度
		T=DS18B20_ReadT();	//读取温度
		if(T<0)				//如果温度小于0
		{
			LCD_ShowChar(2,1,'-');	//显示负号
			T=-T;			//将温度变为正数
		}
		else				//如果温度大于等于0
		{
			LCD_ShowChar(2,1,'+');	//显示正号
		}
		LCD_ShowNum(2,2,T,3);		//显示温度整数部分
		LCD_ShowChar(2,5,'.');		//显示小数点
		LCD_ShowNum(2,6,(unsigned long)(T*10000)%10000,4);//显示温度小数部分
		if(T > 38.0)
		{
			k++;
			if(k<=1) TR0=1;
			PWM_count = 9;
			Delay(2000);
			PWM_count = 2;
			Delay(1000);
		}
	}
}

void Timer0() interrupt 1    
{
	TL0 = 0x06;				
	TH0 = 0xFF;				 	//0.25ms
  if(count < PWM_count) SG_PWM=1;
  else SG_PWM=0;
	
	count++;  
  count%=80;    
}   

