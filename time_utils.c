// Code borrowed from http://git.musl-libc.org/cgit/musl/tree/src/time/__secs_to_tm.c?h=v0.9.15

#include <time.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include "rtc.h"
#include "time_utils.h"

#define CLAMP(min, a, max)  ({ typeof(min) _min = (min); typeof(a) _a = (a); typeof(max) _max = (max); (_a > _max) ? _max : ((_a < min) ? _min : _a);})

/* 2000-03-01 (mod 400 year, immediately after feb29 */
#define LEAPOCH (946684800LL + 86400*(31+29))

#define DAYS_PER_400Y (365*400 + 97)
#define DAYS_PER_100Y (365*100 + 24)
#define DAYS_PER_4Y   (365*4   + 1)

void __secs_to_tm(long long t, struct tm *tm)
{
    long long days, secs;
    int remdays, remsecs, remyears;
    int qc_cycles, c_cycles, q_cycles;
    int years, months;
    int wday, yday, leap;
    static const char days_in_month[] = {31,30,31,30,31,31,30,31,30,31,31,29};

    t = CLAMP(INT_MIN * 31622400LL, t, INT_MAX * 31622400LL);

    secs = t - LEAPOCH;
    days = secs / 86400;
    remsecs = secs % 86400;
    if (remsecs < 0)
    {
        remsecs += 86400;
        days--;
    }

    wday = (3+days)%7;
    if (wday < 0) wday += 7;

    qc_cycles = days / DAYS_PER_400Y;
    remdays = days % DAYS_PER_400Y;
    if (remdays < 0)
    {
        remdays += DAYS_PER_400Y;
        qc_cycles--;
    }

    c_cycles = remdays / DAYS_PER_100Y;
    if (c_cycles == 4) c_cycles--;
    remdays -= c_cycles * DAYS_PER_100Y;

    q_cycles = remdays / DAYS_PER_4Y;
    if (q_cycles == 25) q_cycles--;
    remdays -= q_cycles * DAYS_PER_4Y;

    remyears = remdays / 365;
    if (remyears == 4) remyears--;
    remdays -= remyears * 365;

    leap = !remyears && (q_cycles || !c_cycles);
    yday = remdays + 31 + 28 + leap;
    if (yday >= 365+leap) yday -= 365+leap;

    years = remyears + 4*q_cycles + 100*c_cycles + 400*qc_cycles;

    for (months=0; days_in_month[months] <= remdays; months++)
        remdays -= days_in_month[months];

    years = CLAMP(INT_MIN + 100, years, INT_MAX - 100);

    tm->tm_year = years + 100;
    tm->tm_mon = months + 2;
    if (tm->tm_mon >= 12)
    {
        tm->tm_mon -=12;
        tm->tm_year++;
    }
    tm->tm_mday = remdays + 1;
    tm->tm_wday = wday;
    tm->tm_yday = yday;

    tm->tm_hour = remsecs / 3600;
    tm->tm_min = remsecs / 60 % 60;
    tm->tm_sec = remsecs % 60;
}

static int __month_to_secs(int month, int is_leap)
{
    static const int secs_through_month[] = {
        0, 31*86400, 59*86400, 90*86400,
        120*86400, 151*86400, 181*86400, 212*86400,
        243*86400, 273*86400, 304*86400, 334*86400};
    int t = secs_through_month[month];
    if (is_leap && month >= 2) t+=86400;
    return t;
}

static long long __year_to_secs(long long year, int *is_leap)
{
    if (year-2ULL <= 136)
    {
        int y = year;
        int leaps = (y-68)>>2;
        if (!((y-68)&3))
        {
            leaps--;
            if (is_leap) *is_leap = 1;
        }
        else if (is_leap) *is_leap = 0;
        return 31536000*(y-70) + 86400*leaps;
    }

    int cycles, centuries, leaps, rem;

    if (!is_leap) is_leap = &(int)
        {
            0
        };
    cycles = (year-100) / 400;
    rem = (year-100) % 400;
    if (rem < 0)
    {
        cycles--;
        rem += 400;
    }
    if (!rem)
    {
        *is_leap = 1;
        centuries = 0;
        leaps = 0;
    }
    else
    {
        if (rem >= 200)
        {
            if (rem >= 300) centuries = 3, rem -= 300;
            else centuries = 2, rem -= 200;
        }
        else
        {
            if (rem >= 100) centuries = 1, rem -= 100;
            else centuries = 0;
        }
        if (!rem)
        {
            *is_leap = 0;
            leaps = 0;
        }
        else
        {
            leaps = rem / 4U;
            rem %= 4U;
            *is_leap = !rem;
        }
    }

    leaps += 97*cycles + 24*centuries - *is_leap;

    return(year-100) * 31536000LL + leaps * 86400LL + 946684800 + 86400;
}

static long long __tm_to_secs(const struct tm *tm)
{
    int is_leap;
    long long year = tm->tm_year;
    int month = tm->tm_mon;
    if (month >= 12 || month < 0)
    {
        int adj = month / 12;
        month %= 12;
        if (month < 0)
        {
            adj--;
            month += 12;
        }
        year += adj;
    }
    long long t = __year_to_secs(year, &is_leap);
    t += __month_to_secs(month, is_leap);
    t += 86400LL * (tm->tm_mday-1);
    t += 3600LL * tm->tm_hour;
    t += 60LL * tm->tm_min;
    t += tm->tm_sec;
    return t;
}


bool timestamp_to_datetime(datetime_t *dt, uint32_t ts)
{
    struct tm tm;
    __secs_to_tm(ts, &tm);

    dt->mday = tm.tm_mday;
    dt->hour = tm.tm_hour;
    dt->min = tm.tm_min;
    dt->month = tm.tm_mon + 1;
    dt->sec = tm.tm_sec;
    dt->year = tm.tm_year + 1900;
    return 1;
}


uint32_t datetime_to_timestamp(const datetime_t *dt)
{
    // be on a safe side and clamp all vals
    struct tm tm =
    {
        .tm_mday = CLAMP(1, dt->mday, 31),
        .tm_hour = CLAMP(0, dt->hour, 23),
        .tm_min = CLAMP(0, dt->min, 59),
        .tm_mon = CLAMP(1, dt->month, 12) - 1,
        .tm_sec = CLAMP(0, dt->sec, 59),
        .tm_year = CLAMP(2000, dt->year, 2100) - 1900,
    };

    return __tm_to_secs(&tm);
}
