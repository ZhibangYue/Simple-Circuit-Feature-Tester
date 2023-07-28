#ifndef __TJCUSARTHMI_H_
#define __TJCUSARTHMI_H_

#include "stm32f4xx.h" 

/**
	��ӡ����Ļ����
*/
void TJCPrintf (const char *str, ...);
void initRingBuff(void);
void writeRingBuff(uint8_t data);
void deleteRingBuff(uint16_t size);
uint16_t getRingBuffLenght(void);
uint8_t read1BFromRingBuff(uint16_t position);
void USART1_Init(uint32_t bound);
void USART1_printf(char* fmt,...); //����1��ר��printf����

#define RINGBUFF_LEN	(500)     //�����������ֽ��� 500

#define usize getRingBuffLenght()
#define code_c() initRingBuff()
#define udelete(x) deleteRingBuff(x)
#define u(x) read1BFromRingBuff(x)


extern uint8_t RxBuff[1];

#endif
