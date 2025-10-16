#ifndef _TIMER_H_
#define _TIMER_H_

// _ INCLUDES __________________________________________________________________

#include <switch.h>

#include "common.h"

// _ DEFINES ___________________________________________________________________

#define TARGET_RENDER_TIME_MS   1000 / TARGET_FPS

// _ MACROS ____________________________________________________________________

#define MS_TO_NS_TIMER(x)       x * 1000000

// _ TYPE DEFINITIONS __________________________________________________________

typedef struct timer_t
{
    bool        is_started; 
    uint64_t    start; 
    uint64_t    stop; 
    uint64_t    elapsed_tick;
    double      elapsed_ms; 
    double      wait_time_ms;

}   TIMER_t; 


// _ FUNCTION DECLARATIONS _____________________________________________________

RETURN_STATUS_t start_timer(TIMER_t* t); 

RETURN_STATUS_t stop_timer(TIMER_t* t); 

double calculate_wait_time(TIMER_t* t); 

#endif