# Simple-Circuit-Feature-Tester
C program to test circuit features simply by stm32f407vet6

**2019年电子设计大赛国赛D题《简易电路特性测试仪》**
（文件编码可能存在问题——gb2312/UTF-8）

## 引脚表

| 引脚号 | 外设               | 备注      |
| ------ | ------------------ | --------- |
| PA3    | AD7606**DB7**      | 普通GPIO  |
| PA4    | AD7606**FRSTDATA** | 普通GPIO  |
| PA5    | AD7606**BUSY**     | 普通GPIO  |
| PA6    | AD7606**CS_N**     | 普通GPIO  |
| PA7    | AD7606**RD/SCLK**  | 普通GPIO  |
| PA9    | 串口屏**RX**       | USART1_TX |
| PA10   | 串口屏**TX**       | USART1_RX |
| PB5    | AD7606**RST**      | 普通GPIO  |
| PB10   | AD7606**CONVSTA**  | 普通GPIO  |
| PB12   | AD9833**CS**       | 普通GPIO  |
| PB13   | AD9833**SCK**      | 普通GPIO  |
| PB14   | AD9833**DAT**      | 普通GPIO  |
| PB15   | AD9833**FSYNC**    | 普通GPIO  |
| PC4    | 继电器控制口        | 普通GPIO  |
| PC5    | 继电器控制口        | 普通GPIO  |
| PE12   | AD7606**CONVSTB**  | 普通GPIO  |
| PE13   | AD7606**OS0**      | 普通GPIO  |
| PE14   | AD7606**OS1**      | 普通GPIO  |
| PE15   | AD7606**OS2**      | 普通GPIO  |


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

## v1.1更新(2023/7/30)
添加了**串口屏绘制曲线**函数，收录于User文件夹下`draw.h`和`draw.c`中。

包括：
- 梯形
- 正弦曲线