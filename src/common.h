#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <SDL.h>

extern bool shouldStopGame;
extern SDL_Window *window;

long getCurrentProgramTime();
bool isDue(long timeOfLastOperation_ms, float timeUntilNextOperation_ms);

// hmmm...
typedef struct {
    float x;
    float y;
    float z;
} Coord;

#endif