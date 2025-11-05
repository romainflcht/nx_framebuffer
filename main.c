#include <switch.h>
#include <stdio.h>


#include "common.h"
#include "timer.h"
#include "input.h"
#include "framebuffer.h"
#include "graphic.h"
#include "cbmp.h"
#include "jpeglib/jpeglib.h"

// Handle app exit on key press. 
bool app_is_running = true; 

uint32_t xx = 0; 
uint32_t yy = 0; 

int main(int argc, char* argv[])
{
    RETURN_STATUS_t retval; 
    FRAMEBUFFER_t   fb; 
    TIMER_t         timer; 
    INPUT_t         input; 
    // BMP*            img; 

    
    // Initialize framebuffer handler. 
    retval = fb_handler_init(&fb); 
    if (retval != SUCCESS)
        return FAILURE; 

    // Initialize input handler. 
    init_input(&input);

    Result rc = romfsInit();
    if (R_FAILED(rc))
        return FAILURE; 

    // img = load_bmp("romfs:/assets/img2.bmp");


    while (appletMainLoop())
    {
        // Break the main loop in case a SIGINT is sent. 
        if(!app_is_running)
            break; 

        // Calculate how much time to wait between each frame to reach 
        // TARGET_FPS
        start_timer(&timer);

        // _ INPUT _____________________________________________________________
        // Update key and joystick information and execute actions depending on 
        // which key is pressed/actioned
        update_input(&input); 
        process_pressed_key(&input); 

        // _ RENDER ____________________________________________________________
        // Retrieve the framebuffer. 
        fb_retrieve(&fb); 


        // Clear the screen. 
        fill_screen(&fb, WHITE);

        print_str(&fb, "Hello world!", 0, 0, BLACK, WHITE);

        fb_printf(&fb, 1, 16, BLACK, WHITE, "L_STICK (x): %d", input.left_stick.x); 
        fb_printf(&fb, 1, 32, BLACK, WHITE, "L_STICK (y): %d", input.left_stick.y); 

        // print_bmp(&fb, xx, yy, img);

        

        draw_circle(&fb, xx, yy, 10, BLACK); 

        // Stop the timer and wait the calculated time to reach TARGET_FPS.
        stop_timer(&timer); 
        svcSleepThread(MS_TO_NS_TIMER(calculate_wait_time(&timer)));

        fb_render(&fb);
    }

    // Free ressources and exit. 
    // free_bmp(img);
    fb_close(&fb); 
    romfsExit(); 
    return SUCCESS;
}
