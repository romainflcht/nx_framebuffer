#include "framebuffer.h"


RETURN_STATUS_t fb_handler_init(FRAMEBUFFER_t* fb, NWindow* nwin)
{
    Result retval; 

    // Create a linear framebuffer. 
    retval = framebufferCreate(&(fb->handler), nwin, FB_WIDTH, FB_HEIGHT, PIXEL_FORMAT_RGBA_8888, FB_COUNT);
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
    fb->data = framebufferBegin(&(fb->handler), &(fb->stride));
    if (!fb->data)
        return FAILURE; 

    return SUCCESS; 
}


// _ GRAPHIC FUNCTIONS _________________________________________________________


RETURN_STATUS_t fill_screen(FRAMEBUFFER_t* fb, COLOR_t color)
{
    uint32_t x; 
    uint32_t y; 
    uint32_t cursor; 


    if (!fb->data)
        return FAILURE; 

    for (y = 0; y < FB_HEIGHT; y += 1)
    {
        for (x = 0; x < FB_WIDTH; x += 1)
        {
            cursor = y * fb->stride / sizeof(uint32_t) + x;
            ((uint32_t*)fb->data)[cursor] = color;
        }
    }

    return SUCCESS; 
}


RETURN_STATUS_t draw_pixel(FRAMEBUFFER_t* fb, uint32_t x, uint32_t y, COLOR_t color)
{
    uint32_t cursor; 

    if (!fb->data)
        return FAILURE;

    else if (x < 0 || x >= FB_WIDTH || y < 0 || y >= FB_HEIGHT)
        return FAILURE; 

    cursor = y * fb->stride / sizeof(u32) + x;
    ((uint32_t*)fb->data)[cursor] = color;

    return SUCCESS; 
}

RETURN_STATUS_t draw_line(FRAMEBUFFER_t* fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, COLOR_t color)
{
    uint32_t dx; 
    uint32_t dy; 
    uint32_t d; 
    uint32_t y; 
    uint32_t x; 

    if (!fb->data)
    return FAILURE; 

    else if (x0 < 0 || x0 >= FB_WIDTH || y0 < 0 || y0 >= FB_HEIGHT)
        return FAILURE; 

    else if (x1 < 0 || x1 >= FB_WIDTH || y1 < 0 || y1 >= FB_HEIGHT)
        return FAILURE; 

    dx = x1 - x0; 
    dy = y1 - y0; 
    d = 2 * dy - dx; 
    x = x0; 
    y = y0; 

    // Bresenham's line algorithm, see link below to understand how it's work. 
    // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm. 
    while (x < x1)
    {
        draw_pixel(fb, x, y, color); 
        if (d > 0)
        {
            y += 1;
            d -= 2 * dx; 

        }
        d += 2 * dy; 
        x++; 
    }

    return SUCCESS;
}