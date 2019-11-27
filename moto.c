
#include "moto.h"

uint speed =0;       													//转速
code uint seg[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x02,0xf8,0x00,0x10}; 	//共阳数码管字段编码

/********************************************************************
                             延时程序
*********************************************************************/
void Delay_xms(uint x)	//1ms
{
 	uint i,j;
 	for(i=0;i<x;i++)
  	 for(j=0;j<120;j++);
}
/********************************************************************
                             按键检测
*********************************************************************/
uchar KeyScan()	 														//按键检测
{
	if((KEY&0x0f)!=0x0f)
	{
		Delay_xms(200);								   
		if((KEY&0x0f)!=0x0f)
		{
			return KEY&0x0f;
		}
	}
	return 0x0f;
}
/********************************************************************
                          步进电机延时程序
*********************************************************************/
void Delay_Motor()			
{
	
	uint a=0;
	a=8000+5753*(10-speed);
	while(a--)
	{
		if((KEY&0x0f)!=0x0f)return;  									//在延时里面判断有没有按键按下，有就直接返回
	}
}
/********************************************************************
                          步进电机方向程序
*********************************************************************/
void Motor()		     												//每调用一次步进电机向指定方向走一步
{
	static char j=1;
	if(direction)		 												//判断方向
	{
		j++;
		if(j==5)j=1;
	}
	else
	{
		j--;
		if(j==0)j=4;
	}
	switch(j)			 												//根据拍数选择不同的电压组合
	{
		case 1:
			A1=1;B1=1;A2=0;B2=0;Delay_Motor(); 							//ab
			break;
		case 2:
			A1=0;B1=1;A2=1;B2=0;Delay_Motor(); 							//a~b
			break;
		case 3:
			A1=0;B1=0;A2=1;B2=1;Delay_Motor(); 							//a~b~
			break;
		case 4:
			A1=1;B1=0;A2=0;B2=1;Delay_Motor(); 							//ab~
			break;
	}
}
/********************************************************************
                            显示程序
*********************************************************************/
void DigDisplay()     
{
	P2=seg[speed];														//把速度显示到数码管	
}

