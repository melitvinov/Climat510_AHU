#include <stdint.h>
#include <stdbool.h>
#include "stm32f10x_rtc.h"
#include "stm32f10x_pwr.h"
#include "rtc.h"
#include "time_utils.h"

static uint32_t cached_ts = ~0U;
static datetime_t cached_dt;

uint32_t rtc_get(void)
{
	return RTC_GetCounter();
}


void rtc_set(uint32_t ts)
{
	PWR_BackupAccessCmd(true);
	RTC_WaitForLastTask();
    RTC_SetCounter(ts);
    RTC_WaitForLastTask();
    PWR_BackupAccessCmd(false);
}


const datetime_t *rtc_dt_from_ts(uint32_t ts)
{
    if (ts != cached_ts)
    {
        cached_ts = ts;
        timestamp_to_datetime(&cached_dt, ts);
    }

    return &cached_dt;
}


uint32_t rtc_ts_from_dt(const datetime_t *dt)
{
    return datetime_to_timestamp(dt);
}
