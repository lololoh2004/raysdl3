#pragma once

#include "rsdl/common/export_macro.h"
#include "SDL3/SDL_log.h"


EXPORT_MACRO void rsdlLogHook(void* userdata, int category, SDL_LogPriority priority, const char* text);