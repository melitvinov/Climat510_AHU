/* ������ � ������*/

#include "stm32f10x_rtc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_bkp.h"

#define FIRSTYEAR   2000		// start year
#define FIRSTDAY    6			// 0 = Sunday

static const uint8_t DaysInMonth[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


typedef struct {
	uint16_t year;	/* 1..4095 */
	uint8_t  month;	/* 1..12 */
	uint8_t  mday;	/* 1.. 31 */
	uint8_t  wday;	/* 0..6, Sunday = 0*/
	uint8_t  hour;	/* 0..23 */
	uint8_t  min;	/* 0..59 */
	uint8_t  sec;	/* 0..59 */
	uint8_t  dst;	/* 0 Winter, !=0 Summer */
} eDateTime;


/*struct TDateTime {
        uchar Addr;
		uchar Sec;
        uchar Min;
        uchar Hr;
		uchar Day;
        uchar Date;
        uchar Month;
        uchar Year;
        } DateTime;*/


//������ ���� � �������
char ReadDateTime(eDateTime *fDateTime);
//������ ���� � �������
void WriteDateTime(eDateTime *fDateTime);
