#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

// _ INCLUDES __________________________________________________________________

#include <switch.h>
#include <string.h>

#include "common.h"
#include "color.h"

// _ DEFINES ___________________________________________________________________


#define FB_COUNT        2

#define CHANNEL_COUNT   4

// _ MACROS ____________________________________________________________________

#define FB_HANDLER_ISINVALID(x)   (!x)
#define FB_DATA_ISINVALID(x)      (!(x->data))
#define FB_ISINVALID(x)           (FB_HANDLER_ISINVALID(x) || FB_DATA_ISINVALID(x))

// _ ENUMERATION DEFINITIONS ___________________________________________________

typedef enum fb_buffering_mode_t
{
    SINGLE_BUFFERING, 
    DOUBLE_BUFFERING, 
    TRIPLE_BUFFERING, 
} FB_BUFFERING_MODE_t; 

// _ STRUCTURE DEFINITIONS _____________________________________________________

typedef struct framebuffer_t
{
    Framebuffer handler; 
    uint32_t    width; 
    uint32_t    height; 
    uint32_t    stride; 
    uint8_t     pixel_size; 
    void*       data; 
} FRAMEBUFFER_t;

// _ FUNCTION DECLARATIONS _____________________________________________________

/// @fn RETURN_STATUS_t fb_handler_init(FB_HANDLER_t* handler, NWindow* nwin); 
/// @brief Initialize the framebuffer structure. 
/// @param handler pointer to the structure to initialize. 
/// @param nwin    pointer to a native window to draw on. 
/// @return        error code described in \ref common.h. 
RETURN_STATUS_t fb_handler_init(FRAMEBUFFER_t* handler, NWindow* nwin); 


/// @brief Update the data and stride field with data of the next framebuffer to 
///        display. 
/// @param fb pointer the the framebuffer structure. 
/// @return error code described in \ref common.h. 
RETURN_STATUS_t retrieve_fb(FRAMEBUFFER_t* fb); 

#endif