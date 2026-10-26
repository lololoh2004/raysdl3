#pragma once
#include "rsdl/window.h"


inline void InitWindow(int width, int height, const char* title) {
    initWindow(width, height, title);
}
inline void CloseWindow() {
    closeWindow();
}
inline bool WindowShouldClose(){
    checkEvents();
    pollMouseEvents();
    return !isWindowOpen();
}

inline void SetTargetFPS(int fps){
    setMaxFPS(fps);
}
inline int GetFPS(void){
    return getFPS();
}
inline double GetTime(void){
    return getTime();
}
inline float GetFrameTime(){
    return getDeltaFloat();
}