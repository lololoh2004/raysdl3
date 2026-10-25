#include "rsdl/render.h"

#include "SDL3/SDL_error.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"


SDL_GPUGraphicsPipeline* g_graphicPipln = NULL;


bool initBasePipLn(){
    SDL_GPUShader* vert = compileShaderStr(
        NULL, 0, RSDL_SHADERFORMAT_HLSL_TXT, RSDL_SHADERSTAGE_VERTEX
    );
    SDL_GPUShader* frag = compileShaderStr(
        NULL, 0, RSDL_SHADERFORMAT_HLSL_TXT, RSDL_SHADERSTAGE_VERTEX
    );

    SDL_GPUGraphicsPipelineCreateInfo piplnInfo = {
        .vertex_shader = vert,
        .fragment_shader = frag,
    };
    g_graphicPipln = SDL_CreateGPUGraphicsPipeline(g_gpuDevice, &piplnInfo);

    return true;
}

bool initRender(){
    SDL_GPUShaderFormat formats = SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_DXIL;
    g_gpuDevice = SDL_CreateGPUDevice(formats, true, NULL);
    if (!g_gpuDevice){
        SDL_LogError(SDL_LOG_CATEGORY_GPU, "GPU device creation failed : %s", SDL_GetError());
        SDL_DestroyWindow(g_window);
        SDL_Quit();
        return false;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_GPU, "GPU device created");

    if (!SDL_ClaimWindowForGPUDevice(g_gpuDevice, g_window)){
        SDL_LogError(SDL_LOG_CATEGORY_GPU, "Failed to bind GPU to window : %s", SDL_GetError());
        return false;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_GPU, "GPU bound to window");

    // compileShaderStr(NULL, NULL);

    return true;
}