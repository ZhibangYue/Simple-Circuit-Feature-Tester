#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "OLED.h"
#include "Delay.h"
#include "AD9833.h"
#include "Serial.h"
#include "tjc_usart_hmi.h"
#include "AD7606.h"
#include "relay.h"

#define FRAMELENGTH 6

uint16_t ADValue;
uint16_t i=0;
char str[100];
uint8_t  temp; // AD7606的BUSY状态
float v0=0; // 初始电压
float v,v1=0;
float ri,ro,a,ui1,uo1 =0.0;
long vf=0;// 截止频率
int16_t DB_data[8] = {0}; // AD7606的数据

// 低电平开通，高电平关断
float Measure_u(uint8_t adc, uint8_t method); 
float Measure_ri(void);
float Measure_ro(void);
float Measure_a(void);
long Change_freq(void);
void Detect(void);
int main(void)
{	
	
	OLED_Init();
	Serial_Init();
	// AD9833发波
	AD9833_Init_GPIO();
	AD9833_WaveSeting(1000.0,0,SIN_WAVE,0);
	AD9833_AmpSet(20);
	// 继电器
	Relay_Init();
	// 7606初始化
	GPIO_AD7606_Configuration();
	AD7606_Init();
	while(1){

//		Measure_ri();
//		Measure_ro();
//		Measure_a();
//		// 扫频
//		vf = Change_freq();
//		Detect();
		Delay_s(3);
		
	}	


	
	
}

float Measure_u(uint8_t adc, uint8_t method)
{	
	float MaxV0,vtemp=0.0;
	float MinV0=10000.0;
	i=1;
	v=0;
	while(i>0){
		AD7606_startconvst();
		Delay_ns(1);
		temp = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);			 // 读取 BUSY的状态 
		while(temp == Bit_SET)				//当busy为低电平时，数据转换完毕，此时可以读取数据 
		{
			Delay_ns(10);
			temp = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);		// 读取 BUSY的状态 	 
		}
		AD7606_read_data(DB_data);
		
		vtemp = (float)DB_data[adc]*10000.0/32768;
		OLED_ShowSignedNum(2,1,i, 5);
		if(MaxV0 < vtemp) MaxV0 = vtemp;
		if(MinV0 > vtemp) MinV0 = vtemp;

		Delay_ms(30);

		// 得到幅值
		if (method == 0)
			v0 = MaxV0 - MinV0;
		else
			v0 = (MaxV0 + MinV0)/2;
//		OLED_ShowSignedNum(1,1,vtemp, 5);
//		OLED_ShowSignedNum(1,7,v0, 5);
//		OLED_ShowSignedNum(3,1,MaxV0, 5);
//		OLED_ShowSignedNum(4,1,MinV0, 5);
		//MM
		if(i==10)
		{	
			MaxV0=0;
			MinV0 = 10000;
		}
		if(i==40){
			MaxV0 = 0;
			MinV0 = 10000;
			i=0;
			return v0;
		}
		i++;
		// 继电器翻转
	}
}

float Measure_ri(void)
{	
	float ui0=0.0;
	// 测输入电阻
	Relay_set(); //继电器置位
	Delay_s(3);
	ui0 = Measure_u(0,0);
	OLED_Clear();
	OLED_ShowSignedNum(1,1,ui0,5);
	Relay_reset();// 继电器复位
	Delay_s(3);
	ui1 = Measure_u(0,0);
	OLED_Clear();
	OLED_ShowSignedNum(2,1,ui1,5);
	Delay_s(1);
	ri=(ui0)/(ui1-ui0)*3200;
	OLED_Clear();
	OLED_ShowSignedNum(1,1,ui0,5);
	OLED_ShowSignedNum(2,1,ui1,5);
	OLED_ShowSignedNum(3,1,ri,5);
	OLED_ShowString(4,1,"ri");
	return ri;
}

float Measure_ro(void)
{	
	float uo0=0.0;
	//开始测输出电阻
	Relay_reset();
	Relay_set2();
	Delay_s(2);
	uo0 = Measure_u(2,1);
	OLED_Clear();
	OLED_ShowSignedNum(1,1,uo0,5);
	Delay_s(1);
	Relay_reset(); // 继电器复位
	Delay_s(2);		
	uo1 = Measure_u(2,1);
	OLED_Clear();
	OLED_ShowSignedNum(2,1,uo1,5);
	Delay_s(1);
	ro=(uo1-uo0)/(uo0)*3260;
	OLED_ShowString(3,1,"ro");
	OLED_ShowSignedNum(4,1,ro,5);
	return ro;
}

float Measure_a(void)
{
	a=uo1/ui1*2.828*10*10;// 放大倍数的10倍，因为输出变成了直流量（有效值），所以乘2.828
	OLED_ShowSignedNum(1,1,a,5);
	OLED_ShowString(1,7,"a");
	return a;
}

long Change_freq(void)
{	
	uint16_t vf,vf_temp=0;
	uint8_t k=0;
	// 扫频从继电器的低电平开始
	Relay_reset();
	AD9833_WaveSeting(1000,0,SIN_WAVE,0);
	Delay_s(1);
	vf = Measure_u(2,1);
	OLED_Clear();
	OLED_ShowString(1,1,"vf0:");
	OLED_ShowSignedNum(1,5,vf,6);
	
	while(k<18)
	{	
		//AD9833_WaveSeting(1000-k*50,0,SIN_WAVE,0);
		AD9833_WaveSeting(10000*k+1000,0,SIN_WAVE,0);
		vf_temp = Measure_u(2,1);
		OLED_ShowSignedNum(4,1,vf_temp,6);
		if(vf_temp>0.6*vf&&vf_temp<0.7*vf)
		{	
			//OLED_ShowSignedNum(3,4,1000-k*50,6);
			OLED_ShowSignedNum(3,4,10000*k+1000,6);
			Delay_s(2);
			AD9833_WaveSeting(1000,0,SIN_WAVE,0);
			return 10000*k+1000;
			//return 1000-k*50;
		}
		k++;
	}
	AD9833_WaveSeting(1000,0,SIN_WAVE,0);
	OLED_ShowSignedNum(3,4,10000*k+1000,6);
	return 300000;
}

long Change_wave(uint8_t kmax, int16_t step,uint16_t vf)
{	
	uint8_t k=0;
	// 采样电压值
	uint16_t vf_temp=0;
	while(k<kmax)
	{	
		AD9833_WaveSeting(1000+k*step,0,SIN_WAVE,0);
		vf_temp = Measure_u(2,1);
		OLED_ShowSignedNum(4,1,vf_temp,6);
		if(vf_temp>0.6*vf&&vf_temp<0.7*vf)
		{	
			// 可认为已截止
			OLED_ShowSignedNum(3,4,1000+k*step,6);
			Delay_s(5);
			return step*k+1000;
		}
		k++;
	}
	return 0;
}

void Show_details(void)
{
		OLED_ShowString(1,1,"ri:");
		OLED_ShowSignedNum(1,4,ri,5);
		OLED_ShowString(2,1,"a:");
		OLED_ShowSignedNum(2,4,a,5);
		OLED_ShowString(3,1,"vf:");
		OLED_ShowNum(3,4,vf,7);
}
void Detect(void)
{	

	float DC=0.0;
	Relay_reset();// 继电器低电平测量 
	DC=Measure_u(3, 1);
	OLED_Clear();
	OLED_ShowSignedNum(4,1,DC,5);
	OLED_ShowString(4,7,"<-DC");
//	OLED_ShowSignedNum(3,1,ri,5);
//	OLED_ShowString(3,7,"<-Ri");	
	if(DC>=4000&&DC<=4900)
		// 无需扫频
		OLED_ShowString(1,1,"R2open");
	else if(DC>=160&&DC<=200)
		OLED_ShowString(1,1,"R3open");
	else if(DC>=1600&&DC<=1900)
		OLED_ShowString(1,1,"R4short");
	else if(DC>=9000)
		{
			ri = Measure_ri();
			Delay_s(1);
			OLED_Clear();
			if(ri>130&&ri<200)			OLED_ShowString(1,1,"R1short");
			else if(ri>10000&&ri<12500) OLED_ShowString(1,1,"R4open");
			else if(ri>2900&&ri<3300)	OLED_ShowString(1,1,"R3short");
			else if(ri<130)				OLED_ShowString(1,1,"R2short");
			else if(ri>13000&&ri<17000)	OLED_ShowString(1,1,"R1open");
		}	
	else if(DC>=7200&&DC<=7800)
		{	
			ri = Measure_ri();
			Delay_s(1);
			OLED_Clear();
			if(ri<0||ri>11500)OLED_ShowString(1,1,"C1open");
			else if(ri>9500&&ri<11500)OLED_ShowString(1,1,"C2open");
			else if(ri>2600&&ri<2800)
			{	
				ro = Measure_ro();
				a = Measure_a();
				if(a>130)OLED_ShowString(1,1,"C2double");
			}
			else 
				{
					vf = Change_freq();
					if(vf<60000)OLED_ShowString(1,1,"C3double");
					else if(vf>250000)OLED_ShowString(1,1,"C3open");
					else OLED_ShowString(1,1,"No problems");
				}
		}	
	else OLED_ShowString(1,1,"No problems");
}


