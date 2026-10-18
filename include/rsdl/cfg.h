#pragma once

#include <stdbool.h>
#include "common/export_macro.h"


// PLACEHOLDER
typedef enum{
    NONE = 0,
    FLAG_WINDOW_RESIZABLE,
} windowFlags;

EXPORT_MACRO void clearWindowFlags(void);

EXPORT_MACRO bool hasWindowFlag(windowFlags flag);
EXPORT_MACRO bool hasWindowFlags(windowFlags flags);

EXPORT_MACRO void setWindowFlags(windowFlags flags);
EXPORT_MACRO void addWindowFlags(windowFlags flags);
EXPORT_MACRO void delWindowFlags(windowFlags flags);
