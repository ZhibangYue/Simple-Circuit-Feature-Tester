/**
 * @file draw.h
 * @author Zhibang Yue (yuezhibang@126.com)
 * @brief 串口屏绘制曲线
 * @version 0.1
 * @date 2023-07-30
 * 
 * @copyright Copyright (c) 2023
 * @attention 本文件为串口屏绘制曲线，串口屏需事先配置好
 * 
 */
#ifndef __DRAW_H
#define __DRAW_H

void Draw_sin(uint16_t t, uint16_t a, uint16_t h);
void Draw_trapezoid(uint8_t height, uint16_t a, uint16_t b);
#endif
