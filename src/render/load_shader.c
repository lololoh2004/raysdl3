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

    SDL_GPUShaderFormat sdlShaderFormat = SDL_GPU_SHADERFORMAT_INVALID;
    switch (shaderWrap->fileInfo.format){
        case RSDL_SHADERFORMAT_SPIRV: sdlShaderFormat = SDL_GPU_SHADERFORMAT_SPIRV; break;
        case RSDL_SHADERFORMAT_DXIL : sdlShaderFormat = SDL_GPU_SHADERFORMAT_DXIL ; break;
        default: break;
    }

    switch (sdlShaderFormat){
        case SDL_GPU_SHADERFORMAT_SPIRV:
        case SDL_GPU_SHADERFORMAT_DXIL :{
            const SDL_GPUShaderCreateInfo shInfo = {
                .code_size = shaderWrap->fileInfo.size,
                .code = (const Uint8*) shaderWrap->fileInfo.content,
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
            SDL_ShaderCross_ShaderStage scShaderStage = ( shaderStage == SDL_GPU_SHADERSTAGE_VERTEX )
                ? SDL_SHADERCROSS_SHADERSTAGE_VERTEX
                : SDL_SHADERCROSS_SHADERSTAGE_FRAGMENT;

            const SDL_ShaderCross_HLSL_Info hlslShInfo = {
                .source = shaderWrap->fileInfo.content,
                .entrypoint = entryPoint,
                .shader_stage = scShaderStage,
            };
            void* byteCode = SDL_ShaderCross_CompileSPIRVFromHLSL(&hlslShInfo, &shaderWrap->fileInfo.size);
            if (byteCode == NULL){ break; }

            SDL_ShaderCross_GraphicsShaderMetadata* shMetadata = SDL_ShaderCross_ReflectGraphicsSPIRV(byteCode, shaderWrap->fileInfo.size, 0);
            SDL_ShaderCross_SPIRV_Info scInfo = {
                .bytecode = byteCode,
                .bytecode_size = shaderWrap->fileInfo.size,
                .entrypoint = entryPoint,
                .shader_stage = scShaderStage,
                .props = 0,
            };

            shaderWrap->sdlShader = SDL_ShaderCross_CompileGraphicsShaderFromSPIRV(g_gpuDevice, &scInfo, &shMetadata->resource_info, 0);
            SDL_free(byteCode);
            SDL_free(shMetadata);
        }
    }

    if (shaderWrap->sdlShader == NULL) {
        rsdl_logf(
            "Shader compilation failed. Details : \n - SDL_Error : %s",
            SDL_GetError()
        );
    }
}

SDL_GPUShader* compileShaderStr(const char* codeStr, size_t inSize, rsdlShaderFormat inFormat, rsdlShaderStage inStage){
    // Shader file info init
    // Just default values
    shaderFileInfo shFileInfo = {
        .isValid = false,
        .format = RSDL_SHADERFORMAT_HLSL_TXT,
        .size = inSize,
        .content = NULL,
    };
    // Code FOR shader file info
    if (codeStr == NULL){
        shFileInfo.isValid = false;
        shFileInfo.content = inStage == RSDL_SHADERSTAGE_VERTEX
            ? (char*) DEFAULT_VERT_SHADER
            : (char*) DEFAULT_FRAG_SHADER;
        shFileInfo.size = SDL_strlen(shFileInfo.content);
    } else {
        shFileInfo.isValid = true;
        shFileInfo.format = inFormat;
        shFileInfo.content = (char*) codeStr;
    }

    // Shader wrap struct
    SDLShaderWrapper shaderWrap = {
        .fileInfo = shFileInfo,
        .stage = inStage,
        .sdlShader = NULL,
    };

    // Compile and return
    processShader(&shaderWrap);
    return shaderWrap.sdlShader;
}

// void destroyShader(SDL_GPUShader* inShader){
//     if (inShader == NULL) return;
//     SDL_ReleaseGPUShader(g_gpuDevice, inShader);
// }
void destroyShaders(shader* inShader){
    if (inShader == NULL) return;

    if (inShader->vert != NULL){
        SDL_ReleaseGPUShader(g_gpuDevice, inShader->vert);  inShader->vert = NULL;
    }
    if (inShader->frag != NULL){
        SDL_ReleaseGPUShader(g_gpuDevice, inShader->frag);  inShader->frag = NULL;
    }
}