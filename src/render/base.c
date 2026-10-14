#include "rsdl/log.h"
#include "rsdl/render.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_init.h"


bool initRender(){
    SDL_GPUShaderFormat formats = SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_DXIL;
    g_gpuDevice = SDL_CreateGPUDevice(formats, true, NULL);
    if (!g_gpuDevice){
        rsdl_logf("GPU device creation failed : %s", SDL_GetError());
        SDL_DestroyWindow(g_window);
        SDL_Quit();
        return false;
    }
    rsdl_log("GPU device created");

    if (!SDL_ClaimWindowForGPUDevice(g_gpuDevice, g_window)){
        rsdl_logf("Failed to bind GPU to window : %s", SDL_GetError());
    }
    rsdl_log("GPU bound to window");

    // compileShaderStr(NULL, NULL);

    return true;
}