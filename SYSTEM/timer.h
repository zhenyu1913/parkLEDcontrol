#ifndef TIMER_YZY_H
#define TIMER_YZY_H

#include "stdint.h"

#define TIMER_NUM   20
#define TIMER_NIL    (TIMER_NUM+1)

typedef void(*taskPtr)();
typedef int8_t timerHandle;

void timer_ms_isr(void);
int8_t timer_run_task(void);

timerHandle set_timer(taskPtr task,uint32_t ms,uint8_t isPeriod);
int8_t reset_timer(timerHandle timer_handle);
int8_t delete_timer(timerHandle timer_handle);
int8_t check_timer(timerHandle timer_handle);
int8_t cancel_timer(taskPtr task);

#endif
