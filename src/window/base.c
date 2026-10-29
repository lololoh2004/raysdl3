#include "rsdl/window.h"

#include "rsdl/cfg.h"
#include "rsdl/log.h"
#include "rsdl/render.h"

#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_log.h>


SDL_Window* g_window = NULL;
SDL_GPUDevice* g_gpuDevice = NULL;

static bool s_isWindow = false;
static SDL_WindowFlags s_sdlFlags = 0;


static void convertRLibFlags(void){
    if (hasWindowFlag(FLAG_WINDOW_RESIZABLE)){
        s_sdlFlags |= SDL_WINDOW_RESIZABLE;
    } if (hasWindowFlag(FLAG_WINDOW_TRANSPARENT)){
        s_sdlFlags |= SDL_WINDOW_TRANSPARENT;
    }
}

bool initWindow(int width, int height, const char* title){
    SDL_SetLogOutputFunction(rsdlLogHook, NULL);
    SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);

    if (!SDL_Init(SDL_INIT_VIDEO)){
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "SDL root initialization failed : %s", SDL_GetError());
        return false;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "SDL root initialized");

    convertRLibFlags();
    g_window = SDL_CreateWindow(title, width, height, s_sdlFlags);
    if (!g_window){
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Window creation failed : %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Window created");

    if (!initRender()) return false;

    s_isWindow = true;
    return true;
}
void closeWindow(void){
    SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Destroying window..");
    SDL_DestroyWindow(g_window);
    SDL_Quit();
}

bool isWindowOpen(void){
    return s_isWindow;
}
void setWindowAsClosing(void){
    s_isWindow = false;
}
