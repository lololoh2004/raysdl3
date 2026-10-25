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

inline void TraceLog(logType rsdlType, const char* text){
    SDL_LogPriority priority;
    switch (rsdlType) {
        case LOG_TRACE:   priority = SDL_LOG_PRIORITY_TRACE; break;
        case LOG_DEBUG:   priority = SDL_LOG_PRIORITY_DEBUG; break;
        case LOG_INFO:    priority = SDL_LOG_PRIORITY_INFO; break;
        case LOG_WARNING: priority = SDL_LOG_PRIORITY_WARN; break;
        case LOG_ERROR:   priority = SDL_LOG_PRIORITY_ERROR; break;
        case LOG_FATAL:   priority = SDL_LOG_PRIORITY_CRITICAL; break;
        case LOG_NONE:    return;
        default:          priority = SDL_LOG_PRIORITY_INFO; break;
    }

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, priority, "%s", text);
}

inline void SetConfigFlags(unsigned int flags){
    setWindowFlags(flags);
}

inline Vector2 GetMousePosition(void){
    vec2 pos = getMousePos();
    return (Vector2){pos.x, pos.y};
}