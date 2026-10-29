#pragma once

#include "rsdl/render.h"
#include "rsdl/window.h"

#include <cstring>


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


inline shaderPair LoadShaderFromMemory(const char* vsCode, const char* fsCode){
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
    return (shaderPair) { vsPtr, fsPtr };
}
inline void UnloadShader(shaderPair* inShader){
    destroyShaders(inShader);
}