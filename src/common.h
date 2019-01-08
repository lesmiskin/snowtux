#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <SDL.h>

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

extern bool shouldStopGame;
extern SDL_Window *window;

typedef struct {
    float x; 
    float y;
} point2;

typedef struct {
    float x; 
    float y; 
    float z;
} point3;

typedef struct {
    int r;
    int g;
    int b;
} color;

long getCurrentProgramTime(void);
bool isDue(long timeOfLastOperation_ms, float timeUntilNextOperation_ms);
color makeColor(int r, int g, int b);
point2 makePoint2(float x, float y);
point3 makePoint3(float x, float y, float z);

#endif