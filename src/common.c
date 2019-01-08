#include "common.h"
#include <time.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window *window = NULL;
bool shouldStopGame = false;

long getCurrentProgramTime(void) {
	return clock() / (CLOCKS_PER_SEC / 1000);		// convert ticks to milliseconds
}

bool isDue(long timeOfLastOperation, float timeUntilNextOperation) {
	return (getCurrentProgramTime() - timeOfLastOperation) >= timeUntilNextOperation;
}

color makeColor(int r, int g, int b) {
    color c = { r, g, b };
    return c;
}

point2 makePoint2(float x, float y) {
    point2 p = { x, y };
    return p;
}

point3 makePoint3(float x, float y, float z) {
    point3 p = { x, y, z };
    return p;
}