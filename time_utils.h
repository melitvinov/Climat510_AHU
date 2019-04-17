#ifndef _TIME_UTILS_H_
#define _TIME_UTILS_H_

uint32_t datetime_to_timestamp(const datetime_t *dt);
bool timestamp_to_datetime(datetime_t *dt, uint32_t ts);

#endif
