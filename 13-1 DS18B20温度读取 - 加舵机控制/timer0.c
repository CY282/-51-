#include <REGX52.H>

void Timer0_Init()	
{
	TMOD = 0x01;		//设置定时器模式
	TL0 = 0x06;			//0.25ms
	TH0 = 0xFF;
	ET0 = 1;      		//打开定时器0的中断
	TF0 = 0;			//清除溢出中断标志位
	//TR0 = 1;			//定时器0开始计时
	EA = 1;      		//开总中断
	PT0 = 0;            //设置定时器0的中断优先级
}
