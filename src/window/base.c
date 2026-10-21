#include "rsdl/cfg.h"
#include "rsdl/window.h"
#include "rsdl/log.h"
#include "rsdl/render.h"
#include "rsdl/common/structs.h"

#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_video.h"


SDL_Window* g_window = NULL;
SDL_GPUDevice* g_gpuDevice = NULL;

static bool s_isWindow = false;
static SDL_WindowFlags s_sdlFlags = 0;


void getSdlFlags(){
    if (hasWindowFlag(FLAG_WINDOW_RESIZABLE)){
        s_sdlFlags |= SDL_WINDOW_RESIZABLE;
    } if (hasWindowFlag(FLAG_WINDOW_TRANSPARENT)){
        s_sdlFlags |= SDL_WINDOW_TRANSPARENT;
    }
}

bool initWindow(int width, int height, const char* title){
    if (!SDL_Init(SDL_INIT_VIDEO)){
        rsdl_logf(LOG_ERROR, "SDL root initialization failed : %s", SDL_GetError());
        return false;
    }
    rsdl_log(LOG_INFO, "SDL root initialized");

    getSdlFlags();
    g_window = SDL_CreateWindow(title, width, height, s_sdlFlags);
    if (!g_window){
        rsdl_logf(LOG_ERROR, "Window creation failed : %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    rsdl_log(LOG_INFO, "Window created");

    if (!initRender()) return false;

    s_isWindow = true;
    return true;
}
void closeWindow(void){
    SDL_DestroyWindow(g_window);
    SDL_Quit();
    rsdl_log(LOG_INFO, "Window destroyed");
}

bool isWindowOpen(void){
    return s_isWindow;
}
void setWindowAsClosing(void){
    s_isWindow = false;
}
