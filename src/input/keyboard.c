#include "rsdl/input.h"
#include "SDL3/SDL_keyboard.h"


bool isKeyScanCodeDown(int key){
    int numkeys;
    const bool* keyStates = SDL_GetKeyboardState(&numkeys);

    if (key < 0 || key >= numkeys){
        return false;
    }

    return keyStates[key];
}

