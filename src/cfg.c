#include "rsdl/cfg.h"


unsigned int g_cfgFlags = 0;

void clearWindowFlags(void){
    g_cfgFlags = 0;
}

bool hasWindowFlag(windowFlags flag){
    return (g_cfgFlags & flag) != 0;
}
bool hasWindowFlags(windowFlags flags){
    return (g_cfgFlags & flags) == flags;
}

void setWindowFlags(windowFlags flags){
    g_cfgFlags =  flags;
}
void addWindowFlags(windowFlags flags){
    g_cfgFlags |= flags;
}
void delWindowFlags(windowFlags flags){
    g_cfgFlags &= ~flags;
}