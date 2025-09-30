#include "framebuffer.h"


RETURN_STATUS_t fb_handler_init(FRAMEBUFFER_t* fb)
{
    Result retval; 

    // Get the default native window. 
    fb->nwin = nwindowGetDefault();
    if (!nwindowIsValid(fb->nwin))
        return FAILURE; 

    // Create a linear framebuffer. 
    retval = framebufferCreate(&(fb->handler), fb->nwin, FB_WIDTH, FB_HEIGHT, PIXEL_FORMAT_RGBX_8888, FB_COUNT);
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


RETURN_STATUS_t fb_retrieve(FRAMEBUFFER_t* fb)
{
    if (FB_STRUCT_ISINVALID(fb))
        return FAILURE; 

    fb->data = framebufferBegin(&(fb->handler), &(fb->stride));
    if (FB_DATA_ISINVALID(fb))
        return FAILURE; 

    return SUCCESS; 
}


RETURN_STATUS_t fb_render(FRAMEBUFFER_t* fb)
{
    if (FB_ISINVALID(fb))
        return FAILURE;

    // Render the last retrieved framebuffer and free it. 
    framebufferEnd(&(fb->handler)); 
    fb->data = NULL; 

    return SUCCESS;
}


RETURN_STATUS_t fb_close(FRAMEBUFFER_t* fb)
{
    if (FB_ISINVALID(fb))
        return FAILURE;

    else if (FB_NWIN_ISINVALID(fb))
        return FAILURE; 

    // Free framebuffer handler and native window. 
    framebufferClose(&(fb->handler));
    nwindowClose(fb->nwin);

    return SUCCESS; 
}

