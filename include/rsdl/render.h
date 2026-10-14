#pragma once

#include "rsdl/common/export_macro.h"
#include "rsdl/common/structs.h"
#include <stddef.h>
#include <stdbool.h>


typedef enum rsdlShaderStage {
    RSDL_SHADERSTAGE_VERTEX,
    RSDL_SHADERSTAGE_FRAGMENT
} rsdlShaderStage;

typedef enum rsdlShaderFormat{
    RSDL_SHADERFORMAT_HLSL_TXT,
    RSDL_SHADERFORMAT_SPIRV,
    RSDL_SHADERFORMAT_DXIL,
} rsdlShaderFormat;

typedef struct shaderFileInfo{
    bool isValid;
    rsdlShaderFormat format;
    size_t size;
    char* content;
} shaderFileInfo;

typedef struct SDLShaderWrapper {
    shaderFileInfo fileInfo;
    struct SDL_GPUShader* sdlShader;
    rsdlShaderStage stage;
} SDLShaderWrapper;


EXPORT_MACRO bool initRender();

EXPORT_MACRO void initDraw(void);
EXPORT_MACRO void beginDraw(void);
EXPORT_MACRO void endDraw(void);

EXPORT_MACRO void setBgColor(clr bgColor);
EXPORT_MACRO void drawRectangle(int posX, int posY, int width, int height, clr color);
EXPORT_MACRO void drawCircle   (int centerX, int centerY, float radius, clr color);


EXPORT_MACRO struct SDL_GPUShader* compileShaderStr(const char* codeStr, size_t inSize, rsdlShaderFormat inFormat, rsdlShaderStage inStage);
EXPORT_MACRO void destroyShaders(shader* inShader);