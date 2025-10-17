#include "framebuffer.h"


RETURN_STATUS_t fb_handler_init(FRAMEBUFFER_t* fb, NWindow* nwin)
{
    Result retval; 

    // Create a linear framebuffer. 
    retval = framebufferCreate(&(fb->handler), nwin, FB_WIDTH, FB_HEIGHT, PIXEL_FORMAT_RGBX_8888, FB_COUNT);
    if (R_FAILED(retval))
        return FAILURE; 
    
    retval = framebufferMakeLinear(&(fb->handler));
    if (R_FAILED(retval))
        return FAILURE; 

    // Initialize the framebuffer structure. 
    fb->width = FB_WIDTH; 
    fb->height = FB_HEIGHT; 
    fb->pixel_size = sizeof(uint8_t) * CHANNEL_COUNT; 
    fb->data = NULL; 

    return SUCCESS; 
}


RETURN_STATUS_t retrieve_fb(FRAMEBUFFER_t* fb)
{
    if (FB_HANDLER_ISINVALID(fb))
        return FAILURE; 

    fb->data = framebufferBegin(&(fb->handler), &(fb->stride));
    if (FB_DATA_ISINVALID(fb))
        return FAILURE; 

    return SUCCESS; 
}
