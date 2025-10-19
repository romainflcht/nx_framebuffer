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
    if (FB_ISINVALID(fb))
        return FAILURE; 

    memset(fb->data, color, sizeof(uint32_t) * FB_HEIGHT * FB_WIDTH);

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


RETURN_STATUS_t draw_circle(FRAMEBUFFER_t *fb, uint32_t cx, uint32_t cy, uint32_t r, COLOR_t color)
{
    int32_t x; 
    int32_t y;
    int32_t p; 

    if (FB_ISINVALID(fb))
    return FAILURE; 

    // explaination of how this algorithm works are available here: 
    // https://www.youtube.com/watch?v=hpiILbMkF9w from NoBS Code. 
    x = 0; 
    y = -r; 
    p = -r; 

    while (x < -y)
    {
        if (p > 0)
        {
            y += 1; 
            p += 2 * (x + y) + 1; 
        }

        else 
            p += 2 * x + 1;  

        draw_pixel(fb, cx + x, cy + y, color); 
        draw_pixel(fb, cx - x, cy + y, color); 
        draw_pixel(fb, cx + x, cy - y, color); 
        draw_pixel(fb, cx - x, cy - y, color); 
        draw_pixel(fb, cx + y, cy + x, color); 
        draw_pixel(fb, cx + y, cy - x, color); 
        draw_pixel(fb, cx - y, cy + x, color); 
        draw_pixel(fb, cx - y, cy - x, color); 
        x += 1; 
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


uint32_t fb_printf(FRAMEBUFFER_t* fb, uint32_t x, uint32_t y, COLOR_t fgcolor, COLOR_t bg_color, char* format, ... )
{
    char*   str; 
    size_t  char_count;
    va_list args;
    
    va_start(args, format);

    // Allocate and format the string and print it. 
    char_count = vasprintf(&str, format, args); 
    print_str(fb, str, x, y, fgcolor, bg_color); 
    
    // Free allocated ressources.
    va_end(args);
    free(str); 

    return char_count; 
}


RETURN_STATUS_t print_img(FRAMEBUFFER_t* fb, uint32_t x, uint32_t y, uint32_t w, uint32_t h, const uint32_t* img)
{
    uint32_t cur_x; 
    uint32_t cur_y; 

    if (FB_ISINVALID(fb))
        return FAILURE; 

    // Loop through each pixel of the image and draw it on the screen. 
    for (cur_y = 0; cur_y < h; cur_y += 1)
    {
        for (cur_x = 0; cur_x < w; cur_x += 1)
        {
            if (COORD_ISINVALID(x + cur_x, y + cur_y))
                continue;

            // NX is big-endian which means that RGBA format is ABGR. 
            draw_pixel(fb, x + cur_x, y + cur_y, img[cur_y * w + cur_x]); 
        }
    }

    return SUCCESS; 
}


BMP* load_bmp(char* path)
{
    BMP* img; 

    img = bopen(path); 
    if (!img)
        return NULL;

    return img; 
}


void free_bmp(BMP* bmp)
{
    if (bmp)
        bclose(bmp); 
}


RETURN_STATUS_t print_bmp(FRAMEBUFFER_t* fb, uint32_t x, uint32_t y, BMP* bmp)
{
    uint32_t    height; 
    uint32_t    width; 
    uint32_t    cur_x; 
    uint32_t    cur_y; 
    uint8_t     r; 
    uint8_t     g; 
    uint8_t     b; 

    if (FB_ISINVALID(fb))
        return FAILURE; 

    else if (!bmp)
        return FAILURE;

    height = get_height(bmp); 
    width = get_width(bmp); 

    // Loop through each pixel of the image and draw it on the screen. 
    for (cur_y = 0; cur_y < height; cur_y += 1)
    {
        for (cur_x = 0; cur_x < width; cur_x += 1)
        {
            if (COORD_ISINVALID(x + cur_x, y + cur_y))
                continue;

            // Get pixel from the loaded bmp.
            get_pixel_rgb(bmp, width - 1 - cur_x, height - 1 - cur_y, &r, &g, &b); 
            
            // NX is big-endian which means that RGBA format is ABGR. 
            draw_pixel(fb, x + cur_x, y + cur_y, RGBA8(r, g, b, 0xFF)); 
        }
    }

    return SUCCESS; 
}
