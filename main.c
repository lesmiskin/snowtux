#include <assert.h>
#include <stdbool.h>
#include <time.h>

#include "common.h"
#include "input.h"
#include "mysdl.h"
#include "renderer.h"

const int RENDER_HZ = 1000 / 60;		//60fps
const int GAME_HZ = 1000 / 60;			//60fps

bool running = true;
SDL_Window *window = NULL;

Coord windowSize = { 800, 600 };

static void initSDL(void) {
    if(!IMG_Init(IMG_INIT_PNG)) 
        fatalError("Fatal error", "SDL_Image did not initialise.");

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 64) < 0)
        fatalError("Fatal error", "SDL_Mixer did not initialise.");

    Mix_AllocateChannels(4);

    SDL_InitSubSystem(SDL_INIT_VIDEO);
}

static void initWindow(void) {
    window = SDL_CreateWindow(
        "test",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        (int)windowSize.x,					//dimensions
        (int)windowSize.y,
        SDL_WINDOW_OPENGL
    );

    // stop the application cleanly if something went wrong during window creation
    assert(window != NULL);
}

static void shutdownWindow(void) {
    if(window == NULL) return;			//OK to call if not yet setup (an established subsystem pattern elsewhere)

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
    int main()  {
#endif
    //Seed randomMq number generator
    srand(time(NULL));

    atexit(shutdownMain);

    initSDL();
    initWindow();
    initRenderer();

    long lastRenderFrameTime = clock();
    long lastGameFrameTime = lastRenderFrameTime;
    long lastAnimFrameTime = lastRenderFrameTime;

    //Main game loop (realtime)
    while(running){
        //Game frame
        if(timer(&lastGameFrameTime, GAME_HZ)) {
            pollInput();
            processSystemCommands();
        }

        //Renderer frame
        double renderFPS;
        if(timer(&lastRenderFrameTime, RENDER_HZ)) {
            updateCanvas();
        }
    }

    return 0;
}