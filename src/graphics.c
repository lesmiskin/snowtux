#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include "common.h"
#include "controls.h"
#include "shapes.h"

SDL_Renderer *renderer = NULL;

void initOpenGl(void) {
    SDL_GLContext mainContext = SDL_GL_CreateContext(window);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Depth
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);

    // Projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

void loadTexture(void) {
	// init
    int textureId = 0;
    int mode = GL_RGB;
	glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

	SDL_Surface* surface = SDL_LoadBMP("data/wall.bmp");

	// enable alpha-transparency
	if(surface->format->BytesPerPixel == 4) {
        mode = GL_RGBA;
    }

	// make the texture
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // repeating texture support
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void initGraphics(void) {
    //Init SDL renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,							   // insert at default index position for renderer list.
        SDL_RENDERER_ACCELERATED
    );

    initOpenGl();
    loadTexture();
}

void drawCeilingAndFloor() {
	// ceiling
	glClearColor(0.3, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1.0);

	// floor
	glScissor(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
	glEnable(GL_SCISSOR_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);
}

void processGraphics(void) {
    // init
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	drawCeilingAndFloor();

    // adjust camera for player position
	glRotatef(360.0f - playerLookY, 0, 1, 0);
    glTranslatef(-playerPosX, 0, -playerPosZ);

	// draw a 10x10 room, using cubes (WORLD)
	// TODO: should be in WORLD.C
	float size = 1.0f;
	for (int i = -5; i < 5; i++) {
		drawWall(makePoint3(i, 0, -5), size);	// front
		drawWall(makePoint3(i, 0, 5), size);	// back
		drawWall(makePoint3(-5, 0, i), size);	// left
		drawWall(makePoint3(5, 0, i), size);	// right
	}

    SDL_GL_SwapWindow(window);		// show graphics
}

void shutdownGraphics(void) {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
}