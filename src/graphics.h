#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"
#include <SDL.h>

extern SDL_Renderer *renderer;
extern SDL_Texture *renderBuffer;
extern Coord screenBounds;
extern void initGraphics();
extern void shutdownGraphics();
extern void processGraphics();

#endif