#include <switch.h>


#include "common.h"
#include "framebuffer.h"

// Main program entrypoint
int main(int argc, char* argv[])
{
    FRAMEBUFFER_t   fb; 
    NWindow*        nwin;
    RETURN_STATUS_t retval; 
    
    // Get the default native window. 
    nwin = nwindowGetDefault();
    if (!nwindowIsValid(nwin))
        return FAILURE; 

    retval = fb_handler_init(&fb, nwin); 
    if (retval != SUCCESS)
        return FAILURE; 

    // Configure our supported input layout: a single player with standard controller styles
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    // Initialize the default gamepad (which reads handheld mode inputs as well as the first connected controller)
    PadState pad;
    padInitializeDefault(&pad);

    // Main loop
    while (appletMainLoop())
    {
        // Scan the gamepad. This should be done once for each frame
        padUpdate(&pad);

        // padGetButtonsDown returns the set of buttons that have been
        // newly pressed in this frame compared to the previous one
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus)
            break; // break in order to return to hbmenu

        // Retrieve the framebuffer
        retrieve_fb(&fb); 

        fill_screen(&fb, BLACK); 

        draw_pixel(&fb, 0, 0, WHITE); 
        draw_pixel(&fb, FB_WIDTH - 1, FB_HEIGHT - 1, WHITE); 

        draw_line(&fb, 0, 0, FB_WIDTH - 1, FB_HEIGHT - 1, WHITE); 

        framebufferEnd(&(fb.handler));
       
    }

    framebufferClose(&(fb.handler));
    return SUCCESS;
}
