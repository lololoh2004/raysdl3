#pragma once

#include <stdbool.h>
#include "common/export_macro.h"


// PLACEHOLDER
typedef enum{
    NONE = 0,
    FLAG_WINDOW_RESIZABLE   = 1u << 0,
    FLAG_WINDOW_TRANSPARENT = 1u << 1,
} windowFlags;

EXPORT_MACRO void clearWindowFlags(void);

EXPORT_MACRO bool hasWindowFlag(unsigned int flag);
EXPORT_MACRO bool hasWindowFlags(unsigned int flags);

EXPORT_MACRO void setWindowFlags(unsigned int flags);
EXPORT_MACRO void addWindowFlags(unsigned int flags);
EXPORT_MACRO void delWindowFlags(unsigned int flags);
