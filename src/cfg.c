#include "rsdl/cfg.h"

#include "rsdl/common/structs.h"
#include "SDL3/SDL_gpu.h"


unsigned int g_cfgFlags = 0;

void clearWindowFlags(void){
    g_cfgFlags = 0;
}

bool hasWindowFlag(unsigned int flag){
    return (g_cfgFlags & flag) != 0;
}
bool hasWindowFlags(unsigned int flags){
    return (g_cfgFlags & flags) == flags;
}

void setWindowFlags(unsigned int flags){
    g_cfgFlags =  flags;
}
void addWindowFlags(unsigned int flags){
    g_cfgFlags |= flags;
}
void delWindowFlags(unsigned int flags){
    g_cfgFlags &= ~flags;
}