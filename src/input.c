#include "controls.h"
#include "common.h"

void checkForInputAndEvents(void) {
	resetControls();
	SDL_PumpEvents();							// prepare SDL for event checking

	// examine the events that happened
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0) {
		switch (event.type) {
			// system event: if the OS wants our app to close, let it exit the game loop cleanly
			case SDL_QUIT:
				shouldStopGame = true;
				break;

			// input event: handle single key presses
			case SDL_KEYDOWN: {
				// ignore continually held-down keys (handled separately)
				if (event.key.repeat) {
					break;
				}

				SDL_Keycode keypress = event.key.keysym.scancode;
				if (keypress == SDL_SCANCODE_ESCAPE) {
					shouldStopGame = true;
				}
			}
		}
	}

	const Uint8 *heldKeys = SDL_GetKeyboardState(NULL);

	// handle held-down keys
	if (heldKeys[SDL_SCANCODE_LEFT]) {
		turningLeft = true;
	} else if (heldKeys[SDL_SCANCODE_RIGHT]) {
		turningRight = true;
	}
	if (heldKeys[SDL_SCANCODE_UP]) {
		movingForward = true;
	} else if (heldKeys[SDL_SCANCODE_DOWN]) {
		movingBack = true;
	}
}