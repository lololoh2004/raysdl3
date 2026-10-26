#include "rsdl/input.h"

#include "SDL3/SDL_mouse.h"
#include "cglm/struct/vec2.h"


static SDL_MouseButtonFlags s_prevButtons = 0;
static SDL_MouseButtonFlags s_curButtons = 0;
static float s_mouseX;
static float s_mouseY;

void pollMouseEvents(void){
    s_prevButtons = s_curButtons;
    s_curButtons = SDL_GetMouseState(&s_mouseX, &s_mouseY);
}

bool isMousePressed(int sdlButton){
    Uint32 buttonMask = SDL_BUTTON_MASK(sdlButton);
    return (s_curButtons & buttonMask) && !(s_prevButtons & buttonMask);
}
bool IsMouseReleased(int sdlButton){
    Uint32 buttonMask = SDL_BUTTON_MASK(sdlButton);
    return !(s_curButtons & buttonMask) && (s_prevButtons & buttonMask);
}
bool IsMouseDown(int sdlButton){
    Uint32 buttonMask = SDL_BUTTON_MASK(sdlButton);
    return (s_curButtons & buttonMask);
}
bool IsMouseUp(int sdlButton){
    Uint32 buttonMask = SDL_BUTTON_MASK(sdlButton);
    return !(s_curButtons & buttonMask);
}

float getMouseX(void){
    return s_mouseX;
}
float getMouseY(void){
    return s_mouseY;
}
vec2s getMousePos(void){
    return (vec2s){s_mouseX, s_mouseY};
}


