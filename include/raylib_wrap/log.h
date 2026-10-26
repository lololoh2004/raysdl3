#pragma once

#include "rsdl/common/structs.h"
#include "SDL3/SDL_log.h"


inline void TraceLog(logType rsdlType, const char* text){
    SDL_LogPriority priority;
    switch (rsdlType) {
    case LOG_TRACE:   priority = SDL_LOG_PRIORITY_TRACE; break;
    case LOG_DEBUG:   priority = SDL_LOG_PRIORITY_DEBUG; break;
    case LOG_INFO:    priority = SDL_LOG_PRIORITY_INFO; break;
    case LOG_WARNING: priority = SDL_LOG_PRIORITY_WARN; break;
    case LOG_ERROR:   priority = SDL_LOG_PRIORITY_ERROR; break;
    case LOG_FATAL:   priority = SDL_LOG_PRIORITY_CRITICAL; break;
    case LOG_NONE:    return;
    default:          priority = SDL_LOG_PRIORITY_INFO; break;
    }

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, priority, "%s", text);
}
