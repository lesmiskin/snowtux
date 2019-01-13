#include "common.h"
#include <time.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
SDL_Window *window = NULL;
bool stopGame = false;
float RADIAN_CIRCLE = 3.141592 * 2;

long getTime(void) {
	return clock() / (CLOCKS_PER_SEC / 1000);		// convert ticks to milliseconds
}

bool isDue(long timeOfLastOperation, float timeUntilNextOperation) {
	return (getTime() - timeOfLastOperation) >= timeUntilNextOperation;
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

float sineInc(float offset, float *sineInc, float speed, float magnitude) {
    *sineInc = *sineInc >= RADIAN_CIRCLE ? 0 : *sineInc + speed;

    float sineOffset = (sin(*sineInc) * magnitude);
    return offset - sineOffset;
}

int randomMq(int min, int max) {
    return (rand() % (max + 1 - min)) + min;
}