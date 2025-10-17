#include "graphic.h"


RETURN_STATUS_t draw_pixel(FRAMEBUFFER_t* fb, uint32_t x, uint32_t y, COLOR_t color)
{
    uint32_t cursor; 

    if (FB_ISINVALID(fb)) 
        return FAILURE; 

    else if (COORD_ISINVALID(x, y)) 
        return FAILURE; 

    cursor = y * fb->stride / sizeof(uint32_t) + x; 
    ((uint32_t*)fb->data)[cursor] = color; 

    return SUCCESS; 
}


RETURN_STATUS_t fill_screen(FRAMEBUFFER_t* fb, COLOR_t color)
{
    uint32_t x; 
    uint32_t y; 


    if (FB_ISINVALID(fb))
        return FAILURE; 

    for (y = 0; y < FB_HEIGHT; y += 1)
    {
        for (x = 0; x < FB_WIDTH; x += 1)
            draw_pixel(fb, x, y, color); 
    }

    return SUCCESS; 
}


RETURN_STATUS_t draw_line(FRAMEBUFFER_t* fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, COLOR_t color)
{
    int32_t dx; 
    int32_t dy; 
    int32_t d; 
    int32_t y; 
    int32_t x; 

    if (FB_ISINVALID(fb))
    return FAILURE; 

    else if (COORD_ISINVALID(x0, y0) || COORD_ISINVALID(x1, y1))
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


RETURN_STATUS_t print_char(FRAMEBUFFER_t* fb, char c, uint32_t x, uint32_t y, COLOR_t fgcolor, COLOR_t bgcolor)
{
    unsigned char*  char_addr; 
    unsigned char   current_byte; 
    int             i; 
    int             j; 

    if (FB_ISINVALID(fb))
        return FAILURE; 

    else if (COORD_ISINVALID(x, y))
        return FAILURE; 

    // Get the address of the first byte of the character. 
    char_addr = FONT + (c * FONT_CHAR_HEIGHT); 

    for (i = 0; i < FONT_CHAR_HEIGHT; i++)
    {
        // Get the first byte value of the character (the first line). 
        current_byte = *char_addr;

        for (j = 0; j < FONT_CHAR_WIDTH; j++)
        {
            // Check each bits of the bytes and draw a pixel according to zeros 
            // and ones. 
            if (current_byte & 0x01)
                draw_pixel(fb, x + j, y + i, fgcolor); 
            
            else
                draw_pixel(fb, x + j, y + i, bgcolor); 
            
            // Offset the byte by one to see the next bit. 
            current_byte = current_byte >> 1; 

        }

        // Increment the address to get all 16 lines. 
        char_addr++; 
    }

    return SUCCESS; 
}



RETURN_STATUS_t print_str(FRAMEBUFFER_t* fb, char* str, uint32_t x, uint32_t y, COLOR_t fgcolor, COLOR_t bgcolor)
{
    uint32_t i;
    uint32_t row; 
    uint32_t line; 

    // Check if str in sot empty, x and y boundary. 
    if (!str)
        return FAILURE; 
    
    else if (FB_ISINVALID(fb))
        return FAILURE; 

    else if (COORD_ISINVALID(x, y))
        return FAILURE; 

    row = x; 
    line = y; 

    // Loop through each char of the string and draw it to the screen, stop the
    // drawing if the string is too long. 
    i = 0; 
    while (str[i])
    {
        print_char(fb, str[i], row, line, fgcolor, bgcolor); 

        row += FONT_CHAR_WIDTH; 

        if (row > FB_WIDTH)
        {
            row = x; 
            line += FONT_CHAR_HEIGHT; 
        }
        
        i++; 
    }

    return SUCCESS;
}


RETURN_STATUS_t print_img(FRAMEBUFFER_t* fb, uint32_t x, uint32_t y, uint32_t w, uint32_t h, const uint32_t* img)
{
    uint32_t cur_x; 
    uint32_t cur_y; 

    if (FB_ISINVALID(fb))
        return FAILURE; 

    else if (COORD_ISINVALID(x, y))
        return FAILURE; 

    // Loop through each pixel of the image and draw it on the screen. 
    for (cur_y = 0; cur_y < h; cur_y += 1)
    {
        for (cur_x = 0; cur_x < w; cur_x += 1)
            // NX is big-endian which means that RGBA format is ABGR. 
            draw_pixel(fb, x + cur_x, y + cur_y, img[cur_y * w + cur_x]); 
    }

    return SUCCESS; 
}

