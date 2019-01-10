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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

int TEX_WALL = 0;
int TEX_EYE = 1;

//void make_tex(void)
//{
//	unsigned char data[256][256][3];
//	for (int y = 0; y < 255; y++) {
//		for (int x = 0; x < 255; x++) {
//			unsigned char *p = data[y][x];
//			p[0] = p[1] = p[2] = (x ^ y) & 8 ? 255 : 0;
//		}
//	}
//	glGenTextures(1, &TEX_EYE);
//	glBindTexture(GL_TEXTURE_2D, TEX_EYE);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *)data);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//}

void loadTexture(void) {
    int format = GL_RGB;

	glGenTextures(1, &TEX_WALL);
    glBindTexture(GL_TEXTURE_2D, TEX_WALL);
	SDL_Surface* wall = SDL_LoadBMP("data/wall.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, format, wall->w, wall->h, 0, format, GL_UNSIGNED_BYTE, wall->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(1, &TEX_EYE);
	glBindTexture(GL_TEXTURE_2D, TEX_EYE);
	SDL_Surface* eye = SDL_LoadBMP("data/eyeball.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, format, eye->w, eye->h, 0, format, GL_UNSIGNED_BYTE, eye->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//if(wall->format->BytesPerPixel == 4) {
 //       format = GL_RGBA;
 //   }
}

void initGraphics(void) {
    renderer = SDL_CreateRenderer(
        window,
        -1,							   // insert at default index position for renderer list.
        SDL_RENDERER_ACCELERATED
    );
    initOpenGl();
    loadTexture();
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

void processGraphics(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	drawCeilingAndFloor();

    // adjust camera for player position
	glRotatef(360.0f - playerLookY, 0, 1, 0);
    glTranslatef(-playerPosX, 0, -playerPosZ);

	// draw eye
	glPushMatrix();
	glColor3ub(255, 255, 255);		// blue
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	GLUquadric* sphere = gluNewQuadric();
	glEnable(GL_TEXTURE_2D);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, TEX_EYE);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluSphere(sphere, 1.0, 32, 4);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

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