#include <switch.h>
#include <stdio.h>


#include "common.h"
#include "timer.h"
#include "input.h"
#include "framebuffer.h"
#include "graphic.h"

// Handle app exit, on key press. 
bool app_is_running = true; 


int main(int argc, char* argv[])
{
    RETURN_STATUS_t retval; 
    NWindow*        nwin;
    FRAMEBUFFER_t   fb; 

    TIMER_t         timer; 

    INPUT_t         input; 
    
    // Get the default native window. 
    nwin = nwindowGetDefault();
    if (!nwindowIsValid(nwin))
        return FAILURE; 

    retval = fb_handler_init(&fb, nwin); 
    if (retval != SUCCESS)
        return FAILURE; 

    // Initialize input handler. 
    init_input(&input);

    while (appletMainLoop())
    {
        // Timer that calculate how much time to wait between each frame to 
        // reach TARGET_FPS
        start_timer(&timer);

        // Update key and joystick information and execute actions depending on 
        // which key is pressed/actioned
        update_input(&input); 
        process_pressed_key(&input); 

        if(!app_is_running)
            break; 
        
        // Retrieve the framebuffer. 
        retrieve_fb(&fb); 


        // Clear the screen. 
        fill_screen(&fb, WHITE);

        print_str(&fb, "Hello world", 0, 0, BLACK, WHITE);
        
        // Stop the timer and wait the calculated time.
        stop_timer(&timer); 
        svcSleepThread(MS_TO_NS_TIMER(calculate_wait_time(&timer)));

        // Free the framebuffer. 
        framebufferEnd(&(fb.handler));
    }

    nwindowClose(nwin); 
    framebufferClose(&(fb.handler));
    return SUCCESS;
}
