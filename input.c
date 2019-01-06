#include <stdbool.h>

#include "common.h"
#include "input.h"
#include <SDL_opengl.h>

float piover180 = 0.0174532925f;
float heading = 0;
float xpos = 0;
GLfloat yrot = 0;
GLfloat zpos = 0;

#define MAX_COMMANDS 20

static bool commands[MAX_COMMANDS];

bool checkCommand(int commandFlag) {
    return commands[commandFlag];
}

void checkForKeyPresses(void) {
    SDL_PumpEvents();
    const Uint8 *keysHeld = SDL_GetKeyboardState(NULL);

    //We're on a new frame, so clear all previous checkCommand (not key) states (i.e. set to false)
    memset(commands, 0, sizeof(commands));

    //Respond to SDL events, or key presses (not holds)
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0) {
		switch (event.type) {
			// when the user tries to close the program in the normal fashion (e.g. clicks the "X" button)
			case SDL_QUIT:
				stopTheGame = true;
				break;

			//Presses
			case SDL_KEYDOWN: {
				//Ignore held keys.
				if (event.key.repeat) break;

				SDL_Keycode keypress = event.key.keysym.scancode;

				// TODO: respond to command key presses here

				// if the user presses the ESCAPE key, then we should also quit the game
				if (keypress == SDL_SCANCODE_ESCAPE) {
					stopTheGame = true;
				}
			}
		}
	}

	if (keysHeld[SDL_SCANCODE_LEFT]) {
		heading += 1.5f;
	    yrot = heading;
	}
	else if (keysHeld[SDL_SCANCODE_RIGHT]) {
		heading -= 1.5f;
	    yrot = heading;
	}

	if (keysHeld[SDL_SCANCODE_UP]) {
	    xpos -= (float)sin(yrot*piover180) * 0.15f;          // Move On The X-Plane Based On Player Direction
	    zpos -= (float)cos(yrot*piover180) * 0.15f;          // Move On The Z-Plane Based On Player Direction
	}
	else if (keysHeld[SDL_SCANCODE_DOWN]) {
	    xpos += (float)sin(yrot*piover180) * 0.15f;          // Move On The X-Plane Based On Player Direction
	    zpos += (float)cos(yrot*piover180) * 0.15f;          // Move On The Z-Plane Based On Player Direction
	}
}