#ifndef RENDERER_H
#define RENDERER_H

#include "mysdl.h"
#include "common.h"

extern SDL_Renderer *renderer;
extern SDL_Texture *renderBuffer;
extern Coord screenBounds;
extern void initRenderer();
extern void shutdownRenderer();
extern void updateCanvas();

#endif