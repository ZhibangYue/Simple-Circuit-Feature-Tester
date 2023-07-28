#include <stm32f4xx.h>
#include "Delay.h"
#include "AD7606.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
//#include "lze_lcd.h"

extern uint8_t IO_TAG;	
//-----------------------------------------------------------------
// ��ʼ��������
//-----------------------------------------------------------------
//-----------------------------------------------------------------
// void GPIO_AD7606_Configuration(void)
//-----------------------------------------------------------------
//
// ��������: AD7606�������ú���
// ��ڲ���: ��
// ���ز���: ��
// ȫ�ֱ���: ��
// ����ģ��: RCC_APB2PeriphClockCmd(); GPIO_Init();
// ע������: ��GPIO������ʽ��FSMC������ʽ�µ��������ò�һ��
//			
//-----------------------------------------------------------------
void GPIO_AD7606_Configuration(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;

	// ʹ��IO��ʱ��
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA |	RCC_AHB1Periph_GPIOB |
													RCC_AHB1Periph_GPIOC |	RCC_AHB1Periph_GPIOD |	
													RCC_AHB1Periph_GPIOE,
													 ENABLE);  
//	GPIO_DeInit(GPIOA);//��GPIOx����Ĵ�����ʼ��ΪĬ�ϸ�λֵ
//	GPIO_DeInit(GPIOB);
//	GPIO_DeInit(GPIOC);
//	GPIO_DeInit(GPIOD);
//	GPIO_DeInit(GPIOE);
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// AD7606 
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// ���������� 
	//             CS_N       RD/SCLK      
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;							
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	//                 FRSTDATA     BUSY  
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5 	;							
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd =GPIO_PuPd_NOPULL ;						 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
					 
	//        rst  convstA STby  
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_5 	|GPIO_Pin_10 | GPIO_Pin_11 ;																
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// OS12 OS11 OS10 COB
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	//����������(1)
	// DoutA
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;								
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	
	GPIO_InitStructure.GPIO_PuPd =GPIO_PuPd_NOPULL ;	//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//-----------------------------------------------------------------
// void AD7606_Init(void)
//-----------------------------------------------------------------
//
// ��������: AD7606��ʼ������
// ��ڲ���: ��
// ���ز���: ��
// ȫ�ֱ���: ��
// ����ģ��:    
// ע������: ��
//-----------------------------------------------------------------
void AD7606_Init(void)
{
	convstA_Set;
	convstB_Set;
	Delay_ms(1);
	STby_Set;
	clk_Set;
	cs_Set;	
  OS10_Reset;
	OS11_Reset;
	OS12_Reset;
	AD7606_reset();  
	Delay_ms(1);
	AD7606_startconvst();	
}

/*   * ���ƣ�AD7606_startconvst()  * ���ܣ�����ת��  */  
void AD7606_startconvst(void)
{  
	convstA_Reset;	
	convstB_Reset;	
	Delay_ns (100);
	convstA_Set;
	convstB_Set;
}
  
/*   * ���ƣ�AD7606_reset()  * ���ܣ���λģ��  */
void AD7606_reset(void) 
{ 
	rst_Reset;
	Delay_ns (10);
	rst_Set; 
	Delay_us(1);
	rst_Reset; 
}  

/* 
* ���ƣ�AD7606_read_data() 
* ���ܣ���ȡ���� 
* ����ֵ������һ���ṹ��ָ�룬��ָ��Ϊָ��ṹ��������׵�ַ  
*/ 
void AD7606_read_data(int16_t * DB_data) 
{  
	uint8_t i,j; 	
	for(i=0;i<8;i++)  
	{
		uint16_t DB_data1 = 0;
		cs_Reset; 
		Delay_ns(20);	
		for(j=0;j<16;j++)
		{		
		clk_Reset;
		Delay_ns(25);			
		DB_data1 = ((uint16_t)(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))<< (15-j)) + DB_data1 ;
	  clk_Set;
		Delay_ns(35);				
		}		
		cs_Set;	
		DB_data[i] = (uint16_t)DB_data1;
	}	
} 

