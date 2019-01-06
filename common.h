#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <SDL.h>

extern SDL_Window *window;

long getProgramTime_ms();
bool checkIfDue(long timeOfLastOperation_ms, float timeUntilNextOperation_ms);



#define WIDTH 640
#define HEIGHT 480

extern bool stopTheGame;

typedef struct {
    float x;
    float y;
    float z;
} Coord;

#endif