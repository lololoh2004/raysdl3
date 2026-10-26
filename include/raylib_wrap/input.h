#pragma once

#include "structs.h"

#include "rsdl/input.h"
#include "rsdl/window.h"
#include <SDL3/SDL_mouse.h>


inline Vector2 GetMousePosition(void){
    return getMousePos();
}

inline int GetMouseX(void){
    return (int)getMouseX();
}
inline int GetMouseY(void){
    return (int)getMouseY();
}

inline bool IsMouseButtonPressed(int button){
    return isMousePressed(button);
}
inline bool IsMouseButtonReleased(int button){
    return IsMouseReleased(button);
}
inline bool IsMouseButtonDown(int button){
    return IsMouseDown(button);
}
inline bool IsMouseButtonUp(int button){
    return IsMouseUp(button);
}


inline bool IsKeyDown(int key){
    return isKeyScanCodeDown(key);
}