// TODO: Use spaces not tabs

// GRADE: 10/10

#include "common.h"             // to access the "stopTheGame" variable
#include "graphics.h"           // to show graphics onscreen
#include "input.h"              // to check for key presses

SDL_Window *window = NULL;      // how SDL keeps track of the open game window, and shows graphics

static void startSDL(void) {
    // start up SDL, with graphics capability
    SDL_Init(SDL_INIT_VIDEO);

    // open the game's window onscreen
    window = SDL_CreateWindow(
        "Simple 3D Engine by Les Miskin",       // the title of the window
        SDL_WINDOWPOS_CENTERED,                 // where the window should be positioned onscreen
        SDL_WINDOWPOS_CENTERED,
        800,                                    // the height and width of the window
        600,
        SDL_WINDOW_OPENGL                       // tell SDL we want to use OpenGL, so we can use 3D graphics
    );
}

// politely turn off each part of our game in turn
static void shutDownTheGame(void) {
    // tell the graphics part of the program to turn off
    shutdownRenderer();

    // close our game's window
    SDL_DestroyWindow(window);
    window = NULL;

    // close out of SDL entirely
    SDL_Quit();
}

// this is the first thing that is called when our program starts
int main(int argc, char *argv[]) {
    // on program exit (whenever that may happen), make sure we shut down the game cleanly (good practice)
    atexit(shutDownTheGame);

    // load SDL
    startSDL();
    loadGraphics();

    // calculations to help with game loop operation (i.e. how many milliseconds to wait until doing next frame)
    int FRAMES_PER_SECOND = 60;
    long timeOfLastFrame_ms = 0;
    float timeUntilNextFrame_ms = 1000 / FRAMES_PER_SECOND;


    // -------------
    // THE GAME LOOP
    // Responsible for keeping the game running, doing logic, and causing graphics to show onscreen.
    // -------------
    while (true) {
        // the loop will quit (thereby exiting the game) if this setting is toggled at any time
        if (stopTheGame) {
            break;
        }

        // decide whether to "frame skip" or not, based on how much time has passed since our last frame
        bool isFrameDue = checkIfDue(timeOfLastFrame_ms, timeUntilNextFrame_ms);

        if (isFrameDue) {
            checkForKeyPresses();           // see what the keyboard is (or isn't) doing
            showTheGraphics();              // update the graphics for the current frame

            // record the time, now that we've finished a frame (used to determine "frame skip")
            timeOfLastFrame_ms = getProgramTime_ms();
        }
    }


    // tell the computer we ran OK (i.e. didn't have an error) by returning the code of zero
    return 0;
}