#ifndef __STM_CLOCK_H_
#define __STM_CLOCK_H_

#include "stm32f10x_rtc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_bkp.h"
#include "rtc.h"

#define FIRSTYEAR   2000		// start year
#define FIRSTDAY    6			// 0 = Sunday

static const uint8_t DaysInMonth[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


//Чтение даты и времени
char ReadDateTime(datetime_t *fDateTime);
//Запись даты и времени
void SetRTCTimeStamp(uint32_t cntTime);
//Set Time stamp
uint32_t DateTimeToTimeStamp(datetime_t *fDateTime);

#endif 
