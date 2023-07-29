# Simple-Circuit-Feature-Tester
C program to test circuit features simply by stm32f407vet6

**2019年电子设计大赛国赛D题《简易电路特性测试仪》**

## v0.0初版(2023/7/28)

硬件Hardware中：

- AD9833输出正弦信号
- AD7606实现电压采样
- OLED和淘晶驰串口屏实现数据显示与人机交互
- relay为继电器模块
- key为按键

## v1.0更新(2023/7/29)

添加了`Show()`函数，以实现串口屏控制波形发生器，具体指：

- 改变波形
- 改变频率
- 频率显示