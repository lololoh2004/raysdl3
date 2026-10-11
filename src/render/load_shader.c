#include "rsdl/log.h"
#include "rsdl/render.h"
#include <SDL3/SDL_gpu.h>
#include "rsdl/common/default_shaders_content.h"
#include <SDL3_shadercross/SDL_shadercross.h>

#define FS_ENTRY_POINT "FSMain"
#define VS_ENTRY_POINT "VSMain"



static void processShader(SDLShaderWrapper* shaderWrap){
    SDL_GPUShaderStage shaderStage = (SDL_GPUShaderStage) shaderWrap->stage;
    const char* entryPoint = shaderStage == SDL_GPU_SHADERSTAGE_VERTEX
        ? VS_ENTRY_POINT
        : FS_ENTRY_POINT;
    const char* shaderContent = shaderWrap->fileInfo.content
        ? shaderWrap->fileInfo.content
        : shaderStage == SDL_GPU_SHADERSTAGE_VERTEX
            ? DEFAULT_VERT_SHADER
            : DEFAULT_FRAG_SHADER;

    rsdlShaderFormat shaderFormat = shaderWrap->fileInfo.format;
    SDL_GPUShaderFormat sdlShaderFormat = SDL_GPU_SHADERFORMAT_INVALID;
    switch (shaderFormat){
        case RSDL_SHADERFORMAT_SPIRV: sdlShaderFormat = SDL_GPU_SHADERFORMAT_SPIRV; break;
        case RSDL_SHADERFORMAT_DXIL : sdlShaderFormat = SDL_GPU_SHADERFORMAT_DXIL ; break;
        default: break;
    }


    switch (shaderFormat){
        case RSDL_SHADERFORMAT_SPIRV:
        case RSDL_SHADERFORMAT_DXIL :{
            SDL_GPUShaderCreateInfo shInfo = {
                .code_size = shaderWrap->fileInfo.size,
                .code = (const Uint8*) shaderContent,
                .entrypoint = entryPoint,
                .stage = shaderStage,

                .format = sdlShaderFormat,

                .num_samplers = 0,
                .num_storage_buffers = 0,
                .num_storage_textures = 0,
                .num_uniform_buffers = 0
            };
            shaderWrap->sdlShader = SDL_CreateGPUShader(g_gpuDevice, &shInfo);
            break;
        }
        default:{
            SDL_ShaderCross_HLSL_Info hlslShInfo = {
                .source = shaderContent,
                .entrypoint = entryPoint,
                .shader_stage = shaderStage == SDL_GPU_SHADERSTAGE_VERTEX
                    ? SDL_SHADERCROSS_SHADERSTAGE_VERTEX
                    : SDL_SHADERCROSS_SHADERSTAGE_FRAGMENT,
            };
                // SDL_ShaderCross_CompileSPIRVFromHLSL(hlslShInfo, &shaderWrap->fileInfo.size);
        }
    }

    if (shaderWrap->sdlShader == NULL) {
        rsdl_logf(
            "Shader compilation failed. Details : \n - SDL_Error : %s",
            SDL_GetError()
        );
    }
}

SDL_GPUShader* loadShaderShared(shaderFileInfo info, rsdlShaderStage inStage){
    SDLShaderWrapper shaderWrap = {
        .fileInfo = info,
        .stage = inStage,
        .sdlShader = NULL,
    };
    processShader(&shaderWrap);
    return shaderWrap.sdlShader;
}

SDL_GPUShader* loadShaderPath(const char* path, rsdlShaderStage stage){
    shaderFileInfo shInfo ={
        .isValid = path != NULL
            ? true
            : false,
        .format = RSDL_SHADERFORMAT_HLSL_TXT,
        .size = 0,
    };
    shInfo.content = shInfo.isValid
        ? SDL_LoadFile(path, &shInfo.size)
        : NULL;
    shInfo.isValid = shInfo.content
        ? true
        : false;

    if (shInfo.isValid){
        const char* vertExt = strrchr(path, '.');
        if (vertExt != NULL){
            if (strcmp(vertExt, ".spv") == 0)
                shInfo.format = RSDL_SHADERFORMAT_SPIRV;
            else if (strcmp(vertExt, ".dxil") == 0)
                shInfo.format = RSDL_SHADERFORMAT_DXIL;
        }
    }

    SDL_GPUShader* outShader = loadShaderShared(shInfo, stage);

    SDL_free(shInfo.content);

    return outShader;
}

void destroyShaders(shader* inShader){
    if (inShader == NULL) return;

    if (inShader->vert != NULL){
        SDL_ReleaseGPUShader(g_gpuDevice, inShader->vert);  inShader->vert = NULL;
    }
    if (inShader->frag != NULL){
        SDL_ReleaseGPUShader(g_gpuDevice, inShader->frag);  inShader->frag = NULL;
    }
}