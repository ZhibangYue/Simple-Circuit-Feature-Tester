/**
 * @file draw.c
 * @author Zhibang Yue (yuezhibang@126.com)
 * @brief 与串口屏绘制曲线相关的函数
 * @version 0.1
 * @date 2023-07-30
 * 
 * @copyright Copyright (c) 2023
 * @attention 本文件为串口屏绘制曲线，串口屏需事先配置好
 * 
 */
#include "stm32f4xx.h"
#include "Serial.h"
#include "tjc_usart_hmi.h"
#include <math.h>

/**
 * @brief  串口屏文本显示浮点数
 * @param  index 文本框编号
 * @param  value 浮点数
 * @note   串口屏文本编辑示例：串口通信发送字符串t0.txt="123"，其中t0为文本框编号，"123"为文本框显示内容
 */
void Print_float(uint8_t index, float value)
{
  char str[40];
  sprintf(str, "t%d.txt=\"%f\"\xff\xff\xff", index, value);
  Serial_SendString(str);
  return;
}

/**
 * @brief  绘制等腰梯形
 * @param  height 梯形的高度
 * @param  a 梯形的上底
 * @param  b 梯形的下底
 * @note   绘制的梯形是下底贴合横轴的
 */
void Draw_trapezoid(uint8_t height, uint16_t a, uint16_t b)
{	
	uint16_t j=0;
	uint16_t total = 500;
	char add[40];
	uint16_t c = (b-a)/2;
	int num1 = total/b * c;
	for(j=0;j<num1;j++){
	sprintf(add, "add s0.id,0,%d\xff\xff\xff", height*j/num1);
	Serial_SendString(add);
	}
	int num2 = total/b * a;
	for(j=0;j<num2;j++){
	sprintf(add, "add s0.id,0,%d\xff\xff\xff", height);
	Serial_SendString(add);
	} 
	for(j=num1;j>0;j--){
	sprintf(add, "add s0.id,0,%d\xff\xff\xff", height*j/num1);
	Serial_SendString(add);
	}
	return;
}

/**
 * @brief  绘制正弦曲线
 * @param  t 正弦曲线的周期
 * @param  a 正弦曲线的幅值（0~127）
 * @param  h 正弦曲线的偏移，据幅值而定
 * @note   曲线从0开始，绘制一个周期后结束
 * @attention 曲线的输出范围为0~255，计算方式为a*(sin+1)+h，因此需合理选择a和h的值
 */
void Draw_sin(uint16_t t, uint16_t a, uint16_t h)
{
  char str[40];
  double y, k;
  double max = 3.1415926 * 3.1415926 * 2 / 180 * t;
  for (int n = 0; n <= (int)max; n++)
  {
    // 正弦函数变量的弧度值
    k = n * 180 / 3.1415926 / t;
    // 正弦函数值
    y = a * (sin(k) + 1) + h;
    sprintf(str, "add s0.id,0,%d\xff\xff\xff", (int)y);
    Serial_SendString(str);
  }
  return;
}
