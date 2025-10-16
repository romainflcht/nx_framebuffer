#include "timer.h"


RETURN_STATUS_t start_timer(TIMER_t* t)
{
    if (t->is_started)
        return FAILURE; 

    t->is_started = true; 
    t->start = armGetSystemTick(); 
    t->stop = t->start; 
    t->elapsed_tick = 0; 
    t->elapsed_ms = 0; 
    t->wait_time_ms = 0; 
    return SUCCESS; 
}


RETURN_STATUS_t stop_timer(TIMER_t* t)
{
    if (!t->is_started)
        return FAILURE;

    t->is_started = false; 
    t->stop = armGetSystemTick(); 
    t->elapsed_tick = t->stop - t->start;
    t->elapsed_ms = t->elapsed_tick / (double)armGetSystemTickFreq() * 1000; 
    return SUCCESS; 
}


double calculate_wait_time(TIMER_t* t)
{

    if (t->is_started)
        return 0; 

    t->wait_time_ms = TARGET_RENDER_TIME_MS - t->elapsed_ms; 
        
    return (t->wait_time_ms < 0) ? 0 : t->wait_time_ms; 
}