#include <SDL_opengl.h>
#include <GL/glu.h>
#include "common.h"
#include "controls.h"
#include "shapes.h"

SDL_Renderer *renderer = NULL;

void initOpenGl() {
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

void loadTexture() {
    GLuint TextureID = 0;
    int Mode = GL_RGB;
    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

	SDL_Surface* Surface = SDL_LoadBMP("data/grass.bmp");

	// enable alpha-transparency
	if(Surface->format->BytesPerPixel == 4) {
        Mode = GL_RGBA;
    }
 
    glTexImage2D(GL_TEXTURE_2D, 0, Mode, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE, Surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // for repeating textures only
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // for repeating textures only

    glBindTexture(GL_TEXTURE_2D, TextureID);  
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
    playerPosZ = 10;
}

void processGraphics() {
	// frame initialisation
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();

    // rotation
    float sceneroty = 360.0f - playerLookY;
    glRotatef(sceneroty, 0, 1, 0);

    // translation
    float xtrans = -playerPosX;
    float ztrans = -playerPosZ;
    glTranslatef(xtrans, 0, ztrans);

	// draw our objects
	drawSolidCube();
	drawTexturedFace();

    SDL_GL_SwapWindow(window);		// show graphics on window
}

void shutdownGraphics() {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
}