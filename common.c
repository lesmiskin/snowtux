#include "common.h"
#include <time.h>

SDL_Window *window = NULL;      // TODO: possibly not needed (or at least here)
bool shouldStopGame = false;

long getCurrentProgramTime() {
	return clock() / (CLOCKS_PER_SEC / 1000);		// convert ticks to milliseconds
}

bool isDue(long timeOfLastOperation, float timeUntilNextOperation) {
	return (getCurrentProgramTime() - timeOfLastOperation) >= timeUntilNextOperation;
}