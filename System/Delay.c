#include "stm32f4xx.h"

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 

//-----------------------------------------------------------------
// void Delay_ns (unsigned char t)
//-----------------------------------------------------------------
//
// 函数功能: 时基为ns的延时
// 入口参数: 无符号8bit整数
// 返回参数: 无
// 全局变量: 无
// 调用模块: 无
// 注意事项:  
//
//测得延时如下：(SYSCLK=72MHz) 
//													延时个数		延时				误差
//				Delay_ns(1):       17       236ns				500ns
//				Delay_ns(2):	     26       361ns				550ns
//				Delay_ns(10)														1.625us
//
//-----------------------------------------------------------------
void Delay_ns (uint8_t t)
{
	do {
			;
	} while (--t); 
}
