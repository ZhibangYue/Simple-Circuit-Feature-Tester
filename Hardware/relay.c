#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

/**
  * @brief  继电器初始化
  * @attention  继电器初始状态为开通状态（低电平有效）
  * @note  通过PC4和PC5实现对继电器的控制
  */
void Relay_Init()
	{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// 对PC4和PC5复位
	GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
	}

/**
  * @brief  继电器复位
  * @attention  继电器状态变为开通状态（低电平）
  * @note  通过PC4和PC5实现对继电器的控制
  */
void Relay_reset()
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
}

/**
  * @brief  继电器置位
  * @attention  继电器状态变为关断状态（高电平）
  * @note  通过PC4和PC5实现对继电器的控制
  */
void Relay_set()
{
	GPIO_SetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);
}

/**
  * @brief  继电器调整
  * @attention  继电器2的状态变为关断，继电器1不变
  * @note  通过PC5实现对继电器2的控制
  */
void Relay_set2()
{
	GPIO_SetBits(GPIOC, GPIO_Pin_5);
}
