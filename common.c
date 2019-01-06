#include "common.h"
#include <time.h>               // needed for "clock()"

bool stopTheGame = false;       // stored in COMMON.C so we can toggle from anywhere in our code

long getProgramTime_ms() {
	// get the amount of time the program has been running for, in "ticks" (special units of time used by computers)
	long time_ticks = clock();

	// do a calculation to check how many ticks are in a millisecond, as this can change between types of computers
	long ticksPerMillisecond = CLOCKS_PER_SEC / 1000;

	// convert the ticks to milliseconds, now that we have the correct units to do so
	long time_ms = time_ticks / ticksPerMillisecond;

	return time_ms;
}

bool checkIfDue(long timeOfLastOperation_ms, float timeUntilNextOperation_ms) {
	long time_ms = getProgramTime_ms();

	// figure out the amount of time it's been since the last operation happened
	long timeSinceLastOperation_ms = time_ms - timeOfLastOperation_ms;

	// if enough time has elapsed since the last operation, then we want to do the next operation
	bool isDue = timeSinceLastOperation_ms >= timeUntilNextOperation_ms;

	return isDue;
}