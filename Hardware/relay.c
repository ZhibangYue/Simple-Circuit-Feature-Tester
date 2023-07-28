#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

void Relay_Init()
	{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// ¶ÔPC4ºÍPC5¸´Î»
	GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
	}

void Relay_reset()
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
}

void Relay_set()
{
	GPIO_SetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
}

void Relay_set2()
{
	GPIO_SetBits(GPIOC, GPIO_Pin_5);
}
