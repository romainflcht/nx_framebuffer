#ifndef _INPUT_H_
#define _INPUT_H_

#include <switch.h>
#include "common.h"


// _ EXTERN DEFINITIONS ________________________________________________________
extern bool app_is_running; ///< Used to exit app on key press. 


// _ ENUMERATION DEFINITIONS ___________________________________________________

typedef enum stick_id_t
{
    LEFT_STICK,
    RIGHT_STICK,
}   STICK_ID_t;

typedef enum input_id_t
{
    KEY_A, 
    KEY_B, 
    KEY_X, 
    KEY_Y, 
    KEY_STICK_LEFT, 
    KEY_STICK_RIGHT, 
    KEY_L, 
    KEY_R, 
    KEY_ZL, 
    KEY_ZR, 
    KEY_PLUS,
    KEY_MINUS, 
    KEY_LEFT, 
    KEY_UP, 
    KEY_RIGHT, 
    KEY_DOWN, 
    STICK_L_LEFT, 
    STICK_L_UP, 
    STICK_L_RIGHT, 
    STICK_L_DOWN, 
    STICK_R_LEFT, 
    STICK_R_UP, 
    STICK_R_RIGHT, 
    STICK_R_DOWN, 
    KEY_LEFT_SL, 
    KEY_LEFT_SR, 
    KEY_RIGHT_SL, 
    KEY_RIGHT_SR, 
    INPUT_COUNT, 
}   INPUT_ID_t;


// _ STRUCTURE DEFINITIONS _____________________________________________________

typedef struct input_t
{
    PadState            pad; 
    uint64_t            key_up; 
    uint64_t            key_held; 
    uint64_t            key_pressed; 
    HidAnalogStickState left_stick; 
    HidAnalogStickState right_stick; 
}   INPUT_t; 


// _ FUNCTION DECLARATIONS _____________________________________________________

/// @fn void init_input(INPUT_t* input); 
/// @brief initialize input structure. 
/// @param input pointer to the structure to initialize. 
void init_input(INPUT_t* input); 


/// @fn void update_input(INPUT_t* input); 
/// @brief get latest user input. 
/// @param input pointer to the input structure handling a controller. 
void update_input(INPUT_t* input); 

/// @fn void process_pressed_key(INPUT_t* input);
/// @brief identify and execute action based on which input has been pressed. 
/// @param input pointer to the input structure handling a controller. 
void process_pressed_key(INPUT_t* input);


/// @fn static void _pressed_key_action(INPUT_ID_t key_id); 
/// @brief execute action depending on which key has been pressed. 
/// @param key_id id of the key that is pressed. 
void _pressed_key_action(INPUT_ID_t key_id); 

#endif