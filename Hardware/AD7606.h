#ifndef _AD7606_H
#define _AD7606_H


#define sampling_0times 0 
#define sampling_2times 1 
#define sampling_4times 2 
#define sampling_8times 3 
#define sampling_16times 4 
#define sampling_32times 5 
#define sampling_64times 6

#define STby_Set 	  GPIO_SetBits(GPIOB,GPIO_Pin_11)

#define OS10_Set 	  GPIO_SetBits(GPIOE,GPIO_Pin_15)
#define OS10_Reset   GPIO_ResetBits(GPIOE,GPIO_Pin_15)
#define OS11_Set 	  GPIO_SetBits(GPIOE,GPIO_Pin_14)
#define OS11_Reset   GPIO_ResetBits(GPIOE,GPIO_Pin_14)
#define OS12_Set 	  GPIO_SetBits(GPIOE,GPIO_Pin_13)
#define OS12_Reset   GPIO_ResetBits(GPIOE,GPIO_Pin_13)
#define convstA_Set 	  GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define convstA_Reset   GPIO_ResetBits(GPIOB,GPIO_Pin_10)
//#define convstB_Set 	  GPIO_SetBits(GPIOB,GPIO_Pin_9)
//#define convstB_Reset   GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define convstB_Set 	  GPIO_SetBits(GPIOE,GPIO_Pin_12)
#define convstB_Reset   GPIO_ResetBits(GPIOE,GPIO_Pin_12)
//#define rst_Set 	 		  GPIO_SetBits(GPIOB,GPIO_Pin_8)
//#define rst_Reset  		  GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define rst_Set 	 		  GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define rst_Reset  		  GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define clk_Set 	  			GPIO_SetBits(GPIOA,GPIO_Pin_7)
#define clk_Reset   			GPIO_ResetBits(GPIOA,GPIO_Pin_7)
#define cs_Set 	  			GPIO_SetBits(GPIOA,GPIO_Pin_6)
#define cs_Reset   			GPIO_ResetBits(GPIOA,GPIO_Pin_6)
#define frstdata_Set 	  GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define frstdata_Reset  GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define busy_Set 	  		GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define busy_Reset   		GPIO_ResetBits(GPIOA,GPIO_Pin_5)

extern void GPIO_AD7606_Configuration(void);
extern void AD7606_Init(void);
extern void AD7606_startconvst(void);
extern void AD7606_reset(void);
extern void AD7606_read_data(int16_t * DB_data) ;

#endif

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
