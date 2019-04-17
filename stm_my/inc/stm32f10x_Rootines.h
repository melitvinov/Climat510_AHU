//---------------------- Подпрограммы для функционирования STM32 -------------------------------

#ifndef _STM_MY_ROOTINES_H_
#define _STM_MY_ROOTINES_H_

#include "stm32f10x_clock.h"


typedef  struct __attribute__ ((packed))
{
    uint16_t 	Time;
    uint16_t 	Date;
    uchar 		Year;
} eTime;

#define PORT_KEYB_IN	GPIOA
#define PORT_KEYB_OUT	GPIOC
#define KEYB_IN		0x000f
#define KEYB_OUT	0x000f
#define KEYB_STARTUP RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)

int16_t saveAHUOutTemp[8];

void Init_IWDG(uint16_t* fIWDG_reset);

void Check_IWDG(void);

void CheckWithoutPC(void);


void Init_STM32(void);

void InitMainTimer(void);

void InitIPCTimer(void);

void InitRTC(void);

void Keyboard_Init(void);

char CheckKeyboardSTM();

void SendBlockFRAM(uint16_t fStartAddr,uint8_t* AdrBlock,uint16_t sizeBlock);

void RecvBlockFRAM(uint16_t fStartAddr,uint8_t* AdrBlock,uint16_t sizeBlock);

void WriteToFRAM();

void ReadFromFRAM();

void CopyEEP();
void CalcEEPSum();
void w1Init();
void w1_check();
int16_t w1reset();
void w1_wr();
void w1_rd();
void CrcCalc();
void Reg48ToI2C();
void OutReg();

void Measure();
void CheckInputConfig();


void datetime_to_control_time(eTime *dst, const datetime_t *src);

void control_time_to_datetime(datetime_t *dst, eTime *src, int second);
#endif 
