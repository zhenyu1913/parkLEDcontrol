#include "timer.h"
#include "string.h"


typedef struct timer_t
{
    taskPtr task_ptr;
    uint32_t count;
    uint32_t set_count;
    uint8_t isPeriod;
}timer_t;

timer_t timer_list[TIMER_NUM];

void timer_ms_isr()
{
    int i;
    for(i = 0; i < TIMER_NUM; i++)
    {
        if(timer_list[i].count > 0)
        {
            timer_list[i].count--;
        }
    }
}

int8_t check_timer(timerHandle timer_handle)
{
    if(timer_list[timer_handle].task_ptr != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int8_t reset_timer(timerHandle timer_handle)
{
    timer_list[timer_handle].count = timer_list[timer_handle].set_count;
    return 0;
}

int8_t delete_timer(timerHandle timer_handle)
{
    memset(&timer_list[timer_handle],0,sizeof(timer_t));
    return 0;
}

timerHandle set_timer(taskPtr task,uint32_t ms,uint8_t isPeriod)
{
    int i;
    for(i = 0; i < TIMER_NUM; i++)
    {
        if(check_timer(i) == 0)
        {
            timer_list[i].count = ms;
            timer_list[i].set_count = ms;
            timer_list[i].isPeriod = isPeriod;
            timer_list[i].task_ptr = task;
            return i;
        }
    }
    return -1;
}
 
int8_t cancel_timer(taskPtr task)
{
    int i;
    for(i = 0; i < TIMER_NUM; i++)
    {
        if(timer_list[i].task_ptr == task)
        {
            delete_timer(i);
        }
    }
    return 0;
}

int8_t timer_run_task(void)
{
    int i;
    for(i = 0; i < TIMER_NUM; i++)
    {
        if(check_timer(i) != 0 && timer_list[i].count == 0)
        {
            timer_list[i].task_ptr();
            if(timer_list[i].isPeriod)
            {
                timer_list[i].count = timer_list[i].set_count;
            }
            else
            {
               delete_timer(i);
            }
        }
    }
    return 0;
}

