#include "rsdl/window.h"
#include "SDL3/SDL_events.h"


static SDL_Event event;

void checkEvents(void){
    while (SDL_PollEvent(&event)){
        switch (event.type){
        case SDL_EVENT_TERMINATING:
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
        case SDL_EVENT_QUIT:
            setWindowAsClosing(); break;

        // case SDL_EVENT_KEY_DOWN:
        //     event.key.scancode
        default: break;
        }
    }
}

bool isKeyScanCodeDown(int key){
    int numkeys;
    const bool* keyStates = SDL_GetKeyboardState(&numkeys);

    if (key < 0 || key >= numkeys){
        return false;
    }

    return keyStates[key];
}




