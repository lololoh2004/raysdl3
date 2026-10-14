#pragma once

#include <cstring>
#include "rsdl.h"

#define RAYWHITE CLR_WHITE


inline void InitWindow(int width, int height, const char* title) {
    initWindow(width, height, title);
}
inline void CloseWindow() {
    closeWindow();
}
inline bool WindowShouldClose(){
    checkEvents();
    return !isWindowOpen();
}
inline void BeginDrawing(){
    updateDeltaTime();
    beginDraw();
}
inline void ClearBackground(clr bgClr){
    setBgColor(bgClr);
}
inline void EndDrawing(){
    endDraw();
    sleepBeforeNextFrame();
}
inline float GetFrameTime(){
    return getDeltaFloat();
}
inline void SetTargetFPS(int fps){
    setMaxFPS(fps);
}
inline shader LoadShaderFromMemory(const char* vsCode, const char* fsCode){
    SDL_GPUShader* vsPtr = compileShaderStr(
        vsCode,
        vsCode ? strlen(vsCode) : 0,
        RSDL_SHADERFORMAT_HLSL_TXT,
        RSDL_SHADERSTAGE_VERTEX
    );
    SDL_GPUShader* fsPtr = compileShaderStr(
        fsCode,
        fsCode ? strlen(fsCode) : 0,
        RSDL_SHADERFORMAT_HLSL_TXT,
        RSDL_SHADERSTAGE_FRAGMENT
    );
    return (shader) { vsPtr, fsPtr };
}
inline void UnloadShader(shader* inShader){
    destroyShaders(inShader);
}
