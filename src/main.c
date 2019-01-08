#include "common.h"
#include "graphics.h"
#include "input.h"
#include "controls.h"

const char* WINDOW_TITLE = "Easy 3D Engine";
const int FRAMES_PER_SECOND = 60;

static void shutdownSdl() {
    shutdownGraphics();

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

static void startSdl() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL
    );

    initGraphics();

    // ensure SDL is always shut down cleanly when the program quits.
    atexit(shutdownSdl);
}

int main(int argc, char *argv[]) {
	startSdl();

    // ensure game runs at constant FPS
    long timeOfLastFrame_ms = 0;
    float timeUntilNextFrame_ms = 1000 / FRAMES_PER_SECOND;

    // the main game loop (important!)
    while (!shouldStopGame) {
        bool isFrameDue = isDue(timeOfLastFrame_ms, timeUntilNextFrame_ms);

        // main game frame starts here
        if (isFrameDue) {
            checkForInputAndEvents();
			applyControlsToPlayer();
			processGraphics();

            timeOfLastFrame_ms = getCurrentProgramTime();
        }
    }

    return 0;       // no errors
}