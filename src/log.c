#include "rsdl/log.h"

#include <stdio.h>

#include "SDL3/SDL_log.h"


static const char* logPrefixes[] = {
    "[INVALID]", "[TRACE]", "[VERBOSE]", "[DEBUG]", "[INFO]", "[WARN]", "[ERROR]", "[CRITICAL]", "[COUNT]"
};

void rsdlLogHook(void* userdata, int category, SDL_LogPriority priority, const char* text){
    if (priority < SDL_LOG_PRIORITY_TRACE || priority >= SDL_LOG_PRIORITY_COUNT) {
        printf("[%i] [UNKNOWN] %s\n", category, text);
        return;
    }
    printf("[%i] %s %s\n", category, logPrefixes[priority], text);

    if (userdata != NULL) printf(" - Additional data : %p", userdata);
}
