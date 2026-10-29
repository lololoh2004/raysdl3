#pragma once

#include <stdbool.h>
#include "common/export_macro.h"


// PLACEHOLDER
typedef enum{
    NONE = 0,
    FLAG_FULLSCREEN_MODE    = 1u << 0,
    FLAG_WINDOW_RESIZABLE   = 1u << 1,
    FLAG_WINDOW_UNDECORATED = 1u << 2,
    FLAG_WINDOW_TRANSPARENT = 1u << 3,
    FLAG_WINDOW_HIDDEN      = 1u << 4,
    FLAG_WINDOW_MINIMIZED   = 1u << 5,
    FLAG_WINDOW_MAXIMIZED   = 1u << 6,
    FLAG_WINDOW_UNFOCUSED   = 1u << 7,
    FLAG_WINDOW_TOPMOST     = 1u << 8,
    FLAG_WINDOW_ALWAYS_RUN  = 1u << 9,
    FLAG_WINDOW_HIGHDPI     = 1u << 10,
    FLAG_WINDOW_MOUSE_PASSTHROUGH = 1u << 11,
    FLAG_BORDERLESS_WINDOWED_MODE = 1u << 12,

    FLAG_MSAA_4X_HINT       = 1u << 13,
    FLAG_INTERLACED_HINT    = 1u << 14,
    FLAG_VSYNC_HINT         = 1u << 15,
} windowFlags;


EXPORT_MACRO void clearWindowFlags(void);

EXPORT_MACRO bool hasWindowFlag(unsigned int flag);
EXPORT_MACRO bool hasWindowFlags(unsigned int flags);

EXPORT_MACRO void setWindowFlags(unsigned int flags);
EXPORT_MACRO void addWindowFlags(unsigned int flags);
EXPORT_MACRO void delWindowFlags(unsigned int flags);

