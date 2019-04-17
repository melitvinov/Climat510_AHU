#ifndef _RTC_H_
#define _RTC_H_

typedef struct
{
    uint16_t  year;  /* 1970 .. */
    uint8_t  month; /* 1..12 */
    uint8_t  mday;  /* 1..31 */
    uint8_t  hour;  /* 0..23 */
    uint8_t  min;   /* 0..59 */
    uint8_t  sec;   /* 0..59 */
} datetime_t;


uint32_t rtc_get(void);
void rtc_set(uint32_t ts);
const datetime_t *rtc_dt_from_ts(uint32_t ts);
uint32_t rtc_ts_from_dt(const datetime_t *dt);

#endif
