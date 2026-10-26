#pragma once

#include "cglm/struct/vec2.h"


void pollMouseEvents(void);
bool isMousePressed(int sdlButton);
bool IsMouseReleased(int sdlButton);
bool IsMouseDown(int sdlButton);
bool IsMouseUp(int sdlButton);
float getMouseX(void);
float getMouseY(void);
vec2s getMousePos(void);
