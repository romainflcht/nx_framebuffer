#include "input.h"


void init_input(INPUT_t* input)
{
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    padInitializeDefault(&(input->pad));

    input->key_up = 0; 
    input->key_held = 0; 
    input->key_pressed = 0; 
    return; 
}


void update_input(INPUT_t* input)
{
    padUpdate(&(input->pad));

    // Update keys. 
    input->key_pressed = padGetButtonsDown(&(input->pad));
    input->key_held    = padGetButtons(&(input->pad));
    input->key_up      = padGetButtonsUp(&(input->pad));

    // Update joystick analog value. 
    input->left_stick  = padGetStickPos(&(input->pad), LEFT_STICK);
    input->right_stick = padGetStickPos(&(input->pad), RIGHT_STICK);
    return;
}


void process_pressed_key(INPUT_t* input)
{
    INPUT_ID_t key_id; 

    for (key_id = 0; key_id < INPUT_COUNT; key_id += 1)
    {
        if (input->key_held & BIT(key_id))
            _pressed_key_action(key_id); 
    }
}


void _pressed_key_action(INPUT_ID_t key_id)
{
    switch (key_id)
    {
        case KEY_A:
            // Action pour KEY_A
            break;
        case KEY_B:
            // Action pour KEY_B
            break;
        case KEY_X:
            // Action pour KEY_X
            break;
        case KEY_Y:
            // Action pour KEY_Y
            break;
        case KEY_STICK_LEFT:
            // Action pour KEY_STICK_LEFT
            break;
        case KEY_STICK_RIGHT:
            // Action pour KEY_STICK_RIGHT
            break;
        case KEY_L:
            // Action pour KEY_L
            break;
        case KEY_R:
            // Action pour KEY_R
            break;
        case KEY_ZL:
            // Action pour KEY_ZL
            break;
        case KEY_ZR:
            // Action pour KEY_ZR
            break;
        case KEY_PLUS:
            app_is_running = false; 
            break;
        case KEY_MINUS:
            // Action pour KEY_MINUS
            break;
        case KEY_LEFT:
            // Action pour KEY_LEFT
            break;
        case KEY_UP:
            // Action pour KEY_UP
            break;
        case KEY_RIGHT:
            // Action pour KEY_RIGHT
            break;
        case KEY_DOWN:
            // Action pour KEY_DOWN
            break;
        case STICK_L_LEFT:
            // Action pour STICK_L_LEFT
            xx -= 10; 
            break;
        case STICK_L_UP:
            yy -= 10; 
            break;
        case STICK_L_RIGHT:
            // Action pour STICK_L_RIGHT
            xx += 10; 
            break;
        case STICK_L_DOWN:
            // Action pour STICK_L_DOWN
            yy += 10; 
            break;
        case STICK_R_LEFT:
            // Action pour STICK_R_LEFT
            break;
        case STICK_R_UP:
            // Action pour STICK_R_UP
            break;
        case STICK_R_RIGHT:
            // Action pour STICK_R_RIGHT
            break;
        case STICK_R_DOWN:
            // Action pour STICK_R_DOWN
            break;
        case KEY_LEFT_SL:
            // Action pour KEY_LEFT_SL
            break;
        case KEY_LEFT_SR:
            // Action pour KEY_LEFT_SR
            break;
        case KEY_RIGHT_SL:
            // Action pour KEY_RIGHT_SL
            break;
        case KEY_RIGHT_SR:
            // Action pour KEY_RIGHT_SR
            break;
        case INPUT_COUNT:
            // Action spéciale pour INPUT_COUNT (rarement utilisée)
            break;
        default:
            // Cas par défaut (sécurité)
            break;
    }
}
