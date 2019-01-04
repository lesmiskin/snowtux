#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include "mysdl.h"

#define WIDTH 640
#define HEIGHT 480

extern SDL_Window *window;
extern bool running;

typedef struct {
    float x;
    float y;
    float z;
} Coord;

extern bool timer(long *lastTime, double hertz);
extern void fatalError(const char *title, const char *message);

#endif