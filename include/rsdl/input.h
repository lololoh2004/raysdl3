#pragma once

#include "cglm/struct/vec2.h"
#include "common/export_macro.h"


EXPORT_MACRO void pollMouseEvents(void);
EXPORT_MACRO bool isMousePressed(int sdlButton);
EXPORT_MACRO bool IsMouseReleased(int sdlButton);
EXPORT_MACRO bool IsMouseDown(int sdlButton);
EXPORT_MACRO bool IsMouseUp(int sdlButton);
EXPORT_MACRO float getMouseX(void);
EXPORT_MACRO float getMouseY(void);
EXPORT_MACRO vec2s getMousePos(void);

EXPORT_MACRO bool isKeyScanCodeDown(int key);
