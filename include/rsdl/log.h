#pragma once

#include "common/structs.h"
#include "rsdl/common/export_macro.h"

typedef void (*rsdl_logHook)(logType type, const char* text);

EXPORT_MACRO void setLogFunc(rsdl_logHook inHook);
EXPORT_MACRO void rsdl_log(logType type, const char* text);
EXPORT_MACRO void rsdl_logf(logType type, const char* format, ...);