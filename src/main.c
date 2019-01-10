#include <stdlib.h>
#include "common.h"
#include "graphics.h"
#include "input.h"
#include "controls.h"

const char* WINDOW_TITLE = "Easy 3D Engine";
const int FRAMES_PER_SECOND = 60;

static void shutdownSdl(void) {
    shutdownGraphics();
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

static void startSdl(void) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL
    );
    initGraphics();
    atexit(shutdownSdl);		// always shut SDL down cleanly
}

int main(int argc, char *argv[]) {
	startSdl();
	long timeOfLastFrame_ms = 0;
    float timeUntilNextFrame_ms = (float)1000 / (float)FRAMES_PER_SECOND;

    while (!stopGame) {
		// for constant FPS
		if(!isDue(timeOfLastFrame_ms, timeUntilNextFrame_ms)) {
			continue;
		}

		checkForInputAndEvents();
		applyControlsToPlayer();
		processGraphics();
		timeOfLastFrame_ms = getTime();
    }

    return 0;       // no errors
}