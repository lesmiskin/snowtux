#include "common.h"                 // for access to some commonly-used functions and variables
#include "graphics.h"               // to trigger graphics updates
#include "input.h"                  // to check for key presses

static void shutDownSdl(void) {
    shutdownRenderer();

    // close our game's window
    SDL_DestroyWindow(window);
    window = NULL;

    // quit SDL completely
    SDL_Quit();
}

// this is the first thing that is called when our program starts
int main(int argc, char *argv[]) {
    // start up SDL officially
    SDL_Init(SDL_INIT_VIDEO);

    // bring up the window of our game
    window = SDL_CreateWindow(
        "Simple 3D Engine by Les Miskin",       // the title
        SDL_WINDOWPOS_CENTERED,                 // where it should be positioned
        SDL_WINDOWPOS_CENTERED,
        640,                                    // its dimensions (width & height)
        480,
        SDL_WINDOW_OPENGL                       // we want to use OpenGL (for 3D graphics)
    );

    // TODO: better name...
    loadGraphicsSubsystem();

    // when our program is closed, always make sure we shut down SDL cleanly (good practice)
    atexit(shutDownSdl);

    // calculations to keep game running at a constant speed
    int framesPerSecond = 60;
    long timeOfLastFrame_ms = 0;
    float timeUntilNextFrame_ms = 1000 / framesPerSecond;


    /* 
    ==========================
    the game loop (important!)
    * keeps the game running (rather than quitting automatically at program end)
    * performs game logic, input polling, and graphics updating per-frame
    ==========================
    */
    // this style of loop means the app stays running forever, until we break out of it
    while (true) {
        // if someone triggers this variable, then we break the loop and quit the game
        if (stopTheGame) {
            break;
        }

        // make sure we're not running too fast for our target FPS
        bool isFrameDue = checkIfDue(timeOfLastFrame_ms, timeUntilNextFrame_ms);

        if (isFrameDue) {
            checkForInput();            // see what keys / buttons are being pressed
            updateGraphics();          // update the graphics for the current frame

            // record the time, now that we've finished a frame (used to determine "frame skip")
            timeOfLastFrame_ms = getProgramTime_ms();
        }
    }


    // tell the computer we ran OK (i.e. didn't have an error) by returning the code of zero
    return 0;
}