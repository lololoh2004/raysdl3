#include "rsdl/input.h"

#include "SDL3/SDL_mouse.h"


vec2 getMousePos(void){
    vec2 pos = { 0, 0 };
    SDL_GetMouseState(&pos.x, &pos.y);
    return pos;
}
