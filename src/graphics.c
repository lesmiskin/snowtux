#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include "common.h"
#include "controls.h"
#include "shapes.h"

SDL_Renderer *renderer = NULL;

void initOpenGl(void) {
    SDL_GLContext mainContext = SDL_GL_CreateContext(window);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

void loadTexture(char* name) {
    int format = GL_RGB;
    int tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
//    SDL_Surface* wall = SDL_LoadBMP(name);
    SDL_Surface* wall = IMG_Load(name);
    if (wall->format->BytesPerPixel == 4) {
        format = GL_RGBA;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, format, wall->w, wall->h, 0, format, GL_UNSIGNED_BYTE, wall->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void loadTextures(void) {
    loadTexture("data/wall.bmp");
    loadTexture("data/eyeball3.png");
    loadTexture("data/eyeball4.png");
    loadTexture("data/blood.png");
}

void initGraphics(void) {
    renderer = SDL_CreateRenderer(
        window,
        -1,							   // insert at default index position for renderer list.
        SDL_RENDERER_ACCELERATED
    );
    initOpenGl();
    loadTextures();
}

void drawCeilingAndFloor() {
	// clear whole screen for ceiling
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);		// dark grey
	glClear(GL_COLOR_BUFFER_BIT);

	// clear lower part for floor
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);		// mid grey
	glScissor(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
	glEnable(GL_SCISSOR_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);
}

long lastDrip;

void processGraphics(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	drawCeilingAndFloor();

    // adjust camera for player position
	glRotatef(360.0f - playerLookY, 0, 1, 0);
    glTranslatef(-playerPosX, 0, -playerPosZ);


    if (isDue(lastDrip, 500)) {
        spawnBlood();
        lastDrip = clock();
    }
 
    // draw eye
    drawBlood();
    drawEye(makePoint3(0.0f, 0.0f, 0.0f));

    // draw a 10x10 room, using cubes (WORLD)
    float size = 1.0f;
    for (int i = -5; i < 5; i++) {
        drawWall(makePoint3((float)i, 0.0f, -5.0f), size);	// front
        drawWall(makePoint3((float)i, 0.0f, 5.0f), size);	// back
        drawWall(makePoint3(-5.0f, 0.0f, (float)i), size);	// left
        drawWall(makePoint3(5.0f, 0.0f, (float)i), size);	// right
    }

    SDL_GL_SwapWindow(window);
}

void shutdownGraphics(void) {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
}