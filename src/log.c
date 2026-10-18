#include "rsdl/log.h"

#include <stdarg.h>
#include <stdio.h>


static const char* logPrefixes[] = {
    "[ALL]", "[TRACE]", "[DEBUG]", "[INFO]", "[WARN]", "[ERROR]", "[FATAL]", "[NONE]"
};

static void defltLogHook(logType type, const char* text){
    if (type > LOG_NONE) {
        printf("[UNKNOWN] %s\n", text);
        return;
    }
    printf("%s %s\n", logPrefixes[type], text);
}

static rsdl_logHook curLogHook = defltLogHook;

void setLogFunc(rsdl_logHook inHook){
    if (inHook){
        curLogHook = inHook;
    } else {
        curLogHook = defltLogHook;
    }
}

void rsdl_log(logType type, const char* text){
    curLogHook(type, text);
}

void rsdl_logf(logType type, const char* format, ...) {
    char buffer[1024];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    curLogHook(type, buffer);
}