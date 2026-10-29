#include "rsdl/log.h"
#include "rsdl/render.h"
#include <SDL3/SDL_gpu.h>
#include "rsdl/common/default_shaders_content.h"
#include <SDL3_shadercross/SDL_shadercross.h>

#define FS_ENTRY_POINT "FSMain"
#define VS_ENTRY_POINT "VSMain"


static SDL_GPUShader* processShader(
    const char* codeData,
    size_t size,
    rsdlShaderFormat format,
    SDL_GPUShaderStage stage)
{
    // Common variables
    SDL_GPUShader* result = NULL;
    const char* entryPoint = stage == SDL_GPU_SHADERSTAGE_VERTEX
        ? VS_ENTRY_POINT
        : FS_ENTRY_POINT;

    // ByteCode Variables
    SDL_ShaderCross_ShaderStage scShaderStage = stage == SDL_GPU_SHADERSTAGE_VERTEX
                ? SDL_SHADERCROSS_SHADERSTAGE_VERTEX
                : SDL_SHADERCROSS_SHADERSTAGE_FRAGMENT;

    void*  bCode = NULL;   // bCode = byteCode
    size_t bCodeSize = 0;
    bool   bCodeNeedsFree = false;

    switch (format)
    {
        case RSDL_SHADERFORMAT_SPIRV:
        {
            bCode = (void*)codeData;
            bCodeSize = size;
            bCodeNeedsFree = false;
            break;
        }
        case RSDL_SHADERFORMAT_HLSL_TXT:
        {
            const SDL_ShaderCross_HLSL_Info hlslShInfo = {
                .source = codeData,
                .entrypoint = entryPoint,
                .shader_stage = scShaderStage,
            };
            bCode = SDL_ShaderCross_CompileSPIRVFromHLSL(&hlslShInfo, &bCodeSize);
            bCodeNeedsFree = true;
            break;
        }
        // case RSDL_SHADERFORMAT_DXIL:
        // {
        //     const SDL_GPUShaderCreateInfo shInfo = {
        //         .code_size = size,
        //         .code = (const Uint8*)codeData,
        //         .entrypoint = entryPoint,
        //         .stage = stage,
        //         .format = SDL_GPU_SHADERFORMAT_DXIL,
        //         .num_samplers = 0,
        //         .num_uniform_buffers = 0,
        //     };
        //     result = SDL_CreateGPUShader(g_gpuDevice, &shInfo);
        //
        //     return result;
        // }
        default: break;
    }

    if (bCode != NULL){
        SDL_ShaderCross_GraphicsShaderMetadata* bCodeMetadata = SDL_ShaderCross_ReflectGraphicsSPIRV(
            bCode, bCodeSize, 0
        );
        if (bCodeMetadata != NULL){
            SDL_ShaderCross_SPIRV_Info scInfo = {
                .bytecode = bCode,
                .bytecode_size = bCodeSize,
                .entrypoint = entryPoint,
                .shader_stage = scShaderStage,
                .props = 0,
            };
            result = SDL_ShaderCross_CompileGraphicsShaderFromSPIRV(
                g_gpuDevice, &scInfo, &bCodeMetadata->resource_info, 0
            );

            SDL_free(bCodeMetadata);
        }
        if (bCodeNeedsFree) SDL_free(bCode);
    }

    if (result == NULL) {
        SDL_LogError(
            SDL_LOG_CATEGORY_GPU, "Shader compilation failed. Details : \n - SDL_Error : %s", SDL_GetError()
        );
    }

    return result;
}

SDL_GPUShader* compileShaderStr(const char* codeStr, size_t inSize, rsdlShaderFormat inFormat, rsdlShaderStage inStage){
    // Default variables
    SDL_GPUShaderStage sdlShStage = inStage == RSDL_SHADERSTAGE_VERTEX
        ? SDL_GPU_SHADERSTAGE_VERTEX
        : SDL_GPU_SHADERSTAGE_FRAGMENT;
    const char* shCode = NULL;
    size_t shSize = 0;
    rsdlShaderFormat finalFormat;

    if (codeStr == NULL){
        shCode = inStage == RSDL_SHADERSTAGE_VERTEX
            ? DEFAULT_VERT_SHADER
            : DEFAULT_FRAG_SHADER;
        shSize = SDL_strlen(shCode);
        finalFormat = RSDL_SHADERFORMAT_HLSL_TXT;
    } else{
        shCode = codeStr;
        shSize = inSize;
        finalFormat = inFormat;
    }

    // Compile and return
    return processShader(shCode, shSize, finalFormat, sdlShStage);
}

void destroyShaders(shaderPair* inShader){
    if (inShader == NULL) return;

    if (inShader->vertShader != NULL){
        SDL_ReleaseGPUShader(g_gpuDevice, inShader->vertShader);
        inShader->vertShader = NULL;
    }
    if (inShader->fragShader != NULL){
        SDL_ReleaseGPUShader(g_gpuDevice, inShader->fragShader);
        inShader->fragShader = NULL;
    }
}