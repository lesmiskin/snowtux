#include <stdbool.h>

#include "common.h"
#include "input.h"

float piover180 = 0.0174532925f;
float heading;
float xpos;
GLfloat yrot;
GLfloat zpos;

#define MAX_COMMANDS 20

static bool commands[MAX_COMMANDS];

bool checkCommand(int commandFlag) {
    return commands[commandFlag];
}

void pollInput(void) {
    SDL_PumpEvents();
    const Uint8 *keysHeld = SDL_GetKeyboardState(NULL);

    //We're on a new frame, so clear all previous checkCommand (not key) states (i.e. set to false)
    memset(commands, 0, sizeof(commands));

    //Respond to SDL events, or key presses (not holds)
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0) {
		switch (event.type) {
			case SDL_QUIT:
				commands[CMD_QUIT] = true;
				break;
			//Presses
			case SDL_KEYDOWN: {
				//Ignore held keys.
				if (event.key.repeat) break;

				SDL_Keycode keypress = event.key.keysym.scancode;

				//Exit to title.
				if (keypress == SDL_SCANCODE_ESCAPE)
					commands[CMD_QUIT] = true;
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

void processSystemCommands(void) {
    if(checkCommand(CMD_QUIT)) quit();
}
