// #include "rsdl/log.h"
#include "rsdl/render.h"
#include <SDL3/SDL_gpu.h>
#include "rsdl/common/default_shaders_content.h"
#include <SDL3_shadercross/SDL_shadercross.h>

#define FS_ENTRY_POINT "FSMain"
#define VS_ENTRY_POINT "VSMain"


typedef struct shaderFileInfo{
    bool isValid;
    rsdlShaderFormat format;
    size_t size;
    char* content;
} shaderFileInfo;


typedef struct SDLShaderWrapper {
    shaderFileInfo fileInfo;
    SDL_GPUShaderStage stage;
    SDL_GPUShader* sdlShader;
} SDLShaderWrapper;


static void processShader(SDLShaderWrapper* shaderWrap){
    // const char* entryPoint =
    //      shaderWrap->stage == SDL_GPU_SHADERSTAGE_VERTEX
    //      ? VS_ENTRY_POINT
    //      : FS_ENTRY_POINT;
    // SDL_GPUShaderCreateInfo shInfo = {
    //     .code_size = shaderWrap->size,
    //     .code = (const Uint8*) shaderWrap->content,
    //     .entrypoint = entryPoint,
    //     .stage = shaderWrap->stage,
    //
    //     .format = SDL_GetGPUShaderFormats(g_gpuDevice),
    //
    //     .num_samplers = 0,
    //     .num_storage_buffers = 0,
    //     .num_storage_textures = 0,
    //     .num_uniform_buffers = 0
    // };
    // shaderWrap->sdlShader = SDL_CreateGPUShader(g_gpuDevice, &shInfo);
    // if (shaderWrap->sdlShader == NULL) {
    //     rsdl_logf(
    //         "Shader compilation failed. Details : \n - SDL_Error : %s",
    //         SDL_GetError()
    //     );
    // }
}

SDL_GPUShader* loadShaderStr(char* str, size_t size, rsdlShaderFormat format){
    char* finalStr = str
        ? str
        : DEFAULT_VERT_SHADER;

    SDLShaderWrapper shader = {
        .stage = SDL_GPU_SHADERSTAGE_VERTEX,
        .fileInfo.content = finalStr,
        .fileInfo.size = str
            ? size
            : SDL_strlen(DEFAULT_VERT_SHADER),
    };
    processShader(&shader);
    return shader.sdlShader;
}

bool loadShaderPath(const char* path, SDL_GPUShader* outShader){
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

    outShader = loadShaderStr(shInfo.content, shInfo.size, shInfo.format);

    SDL_free(shInfo.content);

    return true;
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