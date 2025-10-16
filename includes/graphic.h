#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include <switch.h>
#include <stdio.h>

#include "framebuffer.h"
#include "common.h"
#include "color.h"
#include "font.h"

// _ DEFINES ___________________________________________________________________


// _ MACROS ____________________________________________________________________

#define COORD_ISINVALID(x, y) (x < 0 || x >= FB_WIDTH || y < 0 || y >= FB_HEIGHT)


// _ FUNCTION DECLARATIONS _____________________________________________________

/// @fn RETURN_STATUS_t fill_screen(FRAMEBUFFER_t* fb, uint32_t color);
/// @brief fill the screen with the passed color.  
/// @param fb    framebuffer to fill. 
/// @param color color of the filling. 
/// @return error code described in \ref common.h.
RETURN_STATUS_t fill_screen(FRAMEBUFFER_t* fb, uint32_t color);


/// @fn RETURN_STATUS_t draw_pixel(FRAMEBUFFER_t* fb, uint32_t x, uint32_t y, COLOR_t color); 
/// @brief draw a pixel at x, y coordinate. 
/// @param fb    frambuffer where the pixel will be drawn. 
/// @param x     x coordinate. 
/// @param y     y coordinate. 
/// @param color color of the pixel. 
/// @return error code described in \ref common.h.
RETURN_STATUS_t draw_pixel(FRAMEBUFFER_t* fb, uint32_t x, uint32_t y, COLOR_t color); 


/// @fn RETURN_STATUS_t draw_line(FRAMEBUFFER_t* fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, COLOR_t color); 
/// @brief draw a line between two x, y coordinates. 
/// @param fb    framebuffer where to draw the line. 
/// @param x0    first x coordinate. 
/// @param y0    first y coordinate. 
/// @param x1    second x coordinate. 
/// @param y1    second y coordinate. 
/// @param color color of the line. 
/// @return error code described in \ref common.h.
RETURN_STATUS_t draw_line(FRAMEBUFFER_t* fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, COLOR_t color); 


/// @fn RETURN_STATUS_t print_char(FRAMEBUFFER_t* fb, char c, uint32_t x, uint32_t y, COLOR_t fgcolor, COLOR_t bgcolor); 
/// @brief draw a character contained in the ACSII table. 
/// @param fb framebuffer where to draw the character. 
/// @param c  character to draw. 
/// @param x  x coordinate. 
/// @param y  y coordinate. 
/// @param fgcolor forefround color (text color). 
/// @param bgcolor background color. 
/// @return error code described in \ref common.h.
RETURN_STATUS_t print_char(FRAMEBUFFER_t* fb, char c, uint32_t x, uint32_t y, COLOR_t fgcolor, COLOR_t bgcolor); 

/// @fn RETURN_STATUS_t print_str(FRAMEBUFFER_t* fb, char* str, uint32_t x, uint32_t y, COLOR_t fgcolor, COLOR_t bgcolor); 
/// @brief draw a string on the screen with text wrapping. 
/// @param fb framebuffer where to draw the text. 
/// @param str string to draw. 
/// @param x x coordinate. 
/// @param y y coordinate. 
/// @param fgcolor forefround color (text color). 
/// @param bgcolor background color. 
/// @return error code described in \ref common.h.
RETURN_STATUS_t print_str(FRAMEBUFFER_t* fb, char* str, uint32_t x, uint32_t y, COLOR_t fgcolor, COLOR_t bgcolor); 



RETURN_STATUS_t print_img(FRAMEBUFFER_t* fb, uint32_t x, uint32_t y, uint32_t w, uint32_t h, const uint32_t* img); 

#endif