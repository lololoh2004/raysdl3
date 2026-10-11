#pragma once

#include "rsdl/common/export_macro.h"
#include "rsdl/common/structs.h"
#include <stddef.h>
#include <stdbool.h>


typedef enum rsdlShaderFormat{
    RSDL_SHADERFORMAT_HLSL_TXT,
    RSDL_SHADERFORMAT_SPIRV,
    RSDL_SHADERFORMAT_DXIL,
} rsdlShaderFormat;


EXPORT_MACRO bool initRender();

EXPORT_MACRO void initDraw(void);
EXPORT_MACRO void beginDraw(void);
EXPORT_MACRO void endDraw(void);

EXPORT_MACRO void setBgColor(clr bgColor);
EXPORT_MACRO void drawRectangle(int posX, int posY, int width, int height, clr color);
EXPORT_MACRO void drawCircle   (int centerX, int centerY, float radius, clr color);


EXPORT_MACRO struct SDL_GPUShader* loadShaderStr(char* str, size_t size, rsdlShaderFormat format);
EXPORT_MACRO bool loadShaderPath(const char* path, struct SDL_GPUShader* outShader);
