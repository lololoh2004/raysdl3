#pragma once


struct SDL_GPUCommandBuffer;
struct SDL_GPURenderPass;
struct SDL_GPUTexture;
union  SDL_Event;
struct SDL_GPUShader;


typedef struct shaderPair{
    struct SDL_GPUShader* vertShader;
    struct SDL_GPUShader* fragShader;
} shaderPair;

typedef struct color{
    unsigned char r, g, b, a;
} clr;

typedef struct vert{
    float x,y,z;
    float u, v;
    clr color;
} vert;

typedef enum{
    LOG_ALL = 0,
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL,
    LOG_NONE
} logType;


extern struct SDL_Window*    g_window;
extern struct SDL_GPUDevice* g_gpuDevice;
extern struct SDL_GPUGraphicsPipeline* g_graphicPipeln;
extern        unsigned int   g_cfgFlags;
// extern        shaderPair     g_curShaderPair;
