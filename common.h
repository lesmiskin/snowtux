#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <SDL.h>

extern SDL_Window *window;

long getCurrentProgramTime();
bool isDue(long timeOfLastOperation_ms, float timeUntilNextOperation_ms);



#define WIDTH 640
#define HEIGHT 480

extern bool shouldStopGame;

typedef struct {
    float x;
    float y;
    float z;
} Coord;

#endif