#pragma once

#include <cstring>
#include "rsdl.h"

#define RAYWHITE CLR_WHITE
// #define Vector2 vec2


typedef struct Vector2{
    float x, y;
} Vector2;

typedef enum{
    KEY_NULL = 0,

    KEY_UP    = 82, // SDL_SCANCODE_UP
    KEY_DOWN  = 81, // SDL_SCANCODE_DOWN
    KEY_LEFT  = 80, // SDL_SCANCODE_LEFT
    KEY_RIGHT = 79, //S DL_SCANCODE_RIGHT

    KEY_W = 26, // SDL_SCANCODE_W
    KEY_A = 4,  // SDL_SCANCODE_A
    KEY_S = 22, // SDL_SCANCODE_S
    KEY_D = 7,  // SDL_SCANCODE_D

    KEY_SPACE  = 44, // SDL_SCANCODE_SPACE
    KEY_ESCAPE = 41, // SDL_SCANCODE_ESCAPE
    KEY_ENTER  = 40 // SDL_SCANCODE_RETURN
} KeyboardKey;

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

inline bool IsKeyDown(int key){
    return isKeyScanCodeDown(key);
}

inline void TraceLog(logType type, const char* text){
    rsdl_log(type, text);
}

inline void SetConfigFlags(windowFlags flags){
    setWindowFlags(flags);
}