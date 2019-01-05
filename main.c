// GRADE: 0/10

#include <assert.h>
#include <stdbool.h>
#include <time.h>

#include "common.h"
#include "input.h"
#include "mysdl.h"
#include "renderer.h"

// Shrink code down.
// Stop bringing up console window when starting on Win32.

const int FRAMES_PER_SECOND = 60;

bool running = true;
SDL_Window *window = NULL;

static void initSDL(void) {
	SDL_InitSubSystem(SDL_INIT_VIDEO);
}

static void initWindow(void) {
	window = SDL_CreateWindow(
		"test",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_OPENGL
	);

	// stop the application cleanly if something went wrong during window creation
	assert(window != NULL);
}

static void shutdownWindow(void) {
	if (window == NULL) return;			//OK to call if not yet setup (an established subsystem pattern elsewhere)

	SDL_DestroyWindow(window);
	window = NULL;
}

static void shutdownMain(void) {
	shutdownRenderer();
	shutdownWindow();

	SDL_Quit();
}

#if defined(_WIN32)
int main(int argc, char *argv[]) {
#else
int main() {
#endif
	atexit(shutdownMain);

	initSDL();
	initWindow();
	initRenderer();

	long timeOfLastFrame_ms = -1;
	float timeUntilNextFrame_ms = 1000 / FRAMES_PER_SECOND;

	// -----------------------------------
	// THE MAIN GAME LOOP (very important)
	// -----------------------------------
	while (running) {
		bool isFrameDue = checkIfDue(timeOfLastFrame_ms, timeUntilNextFrame_ms);

		if (isFrameDue) {
			pollInput();
			processSystemCommands();
			updateCanvas();

			timeOfLastFrame_ms = getProgramTime_ms();
		}
	}

	return 0;
}
