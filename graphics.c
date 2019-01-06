#include <assert.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>

#include "graphics.h"
#include "input.h"
#include "mysdl.h"

// take out render scaling stuff (simpler just to have 1:1 scale)

SDL_Texture *renderBuffer;
SDL_Renderer *renderer = NULL;
static int renderScale;
Coord screenBounds;
SDL_GLContext mainContext;

Coord makeCoord(float x, float y, float z) {
    Coord c = { x, y, z };
    return c;
}

void initOpenGl() {
    mainContext = SDL_GL_CreateContext(window);

    //Resize GL scene
    glViewport(0,0,WIDTH,HEIGHT);                       // Reset The Current Viewport

    // Depth stuff
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);

    // Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);                         // Select The Modelview Matrix
}

void loadTexture() {
    GLuint TextureID = 0;
    int Mode = GL_RGB;
     
    SDL_Surface* Surface = SDL_LoadBMP("data/grass.bmp");

    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);
     
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

void loadGraphics(void) {
    //Init SDL renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,							                                    // insert at default index position for renderer list.
        SDL_RENDERER_ACCELERATED
    );

    //Set virtual screen size and pixel doubling ratio.
    screenBounds = makeCoord(WIDTH, HEIGHT, 0);		//virtual screen size

    //Rachaie's background.
    SDL_RenderClear(renderer);

    // SDL_SetRenderTarget(renderer, renderBuffer);
    assert(renderer != NULL);

    initOpenGl();
    loadTexture();
    zpos = 10;
}

void shutdownRenderer(void) {
    if(renderer == NULL) return;			//OK to call if not yet setup (thanks, encapsulation)

    SDL_DestroyRenderer(renderer);
    renderer = NULL;
}

float blurg = 0;

void showTheGraphics(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);              // Clear the frame.

    glLoadIdentity();                          // Reset The Current Matrix (fucks out otherwise)
    glPushMatrix();

    // looking around 
    GLfloat sceneroty = 360.0f - yrot;         // 360 Degree Angle For Player Direction
    glRotatef(sceneroty, 0, 1, 0);             // Rotate Depending On Direction Player Is Facing

    // camera translation     
    GLfloat xtrans = -xpos;                    // Used For Player Translation On The X Axis
    GLfloat ztrans = -zpos;                    // Used For Player Translation On The Z Axis
    glTranslatef(xtrans, 0, ztrans);           // Translate The Scene Based On Player Position

    float i = -10.1f;

    // glTranslatef(0, 0, i);            // translate to quad origin.
    // glRotatef(blurg++, 0, 1, 0);             // perform desired rotation.
    // glTranslatef(0, 0, -i);          // reverse the the previous translation.

    // NB: 2.0 repeats twice etc.
    glBegin(GL_QUADS);
        glColor3f(0.0f,1.0f,0.0f);                      // Set The Color To Green
        glVertex3f( 1.0f, 1.0f,-1.0f);                  // Top Right Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f,-1.0f);                  // Top Left Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f, 1.0f);                  // Bottom Left Of The Quad (Top)
        glVertex3f( 1.0f, 1.0f, 1.0f);                  // Bottom Right Of The Quad (Top)

        glColor3f(1.0f,0.5f,0.0f);                      // Set The Color To Orange
        glVertex3f( 1.0f,-1.0f, 1.0f);                  // Top Right Of The Quad (Bottom)
        glVertex3f(-1.0f,-1.0f, 1.0f);                  // Top Left Of The Quad (Bottom)
        glVertex3f(-1.0f,-1.0f,-1.0f);                  // Bottom Left Of The Quad (Bottom)
        glVertex3f( 1.0f,-1.0f,-1.0f);                  // Bottom Right Of The Quad (Bottom)

        glColor3f(1.0f,0.0f,0.0f);                      // Set The Color To Red
        glVertex3f( 1.0f, 1.0f, 1.0f);                  // Top Right Of The Quad (Front)
        glVertex3f(-1.0f, 1.0f, 1.0f);                  // Top Left Of The Quad (Front)
        glVertex3f(-1.0f,-1.0f, 1.0f);                  // Bottom Left Of The Quad (Front)
        glVertex3f( 1.0f,-1.0f, 1.0f);                  // Bottom Right Of The Quad (Front)

        glColor3f(1.0f,1.0f,0.0f);                      // Set The Color To Yellow
        glVertex3f( 1.0f,-1.0f,-1.0f);                  // Top Right Of The Quad (Back)
        glVertex3f(-1.0f,-1.0f,-1.0f);                  // Top Left Of The Quad (Back)
        glVertex3f(-1.0f, 1.0f,-1.0f);                  // Bottom Left Of The Quad (Back)
        glVertex3f( 1.0f, 1.0f,-1.0f);                  // Bottom Right Of The Quad (Back)

        glColor3f(0.0f,0.0f,1.0f);                      // Set The Color To Blue
        glVertex3f(-1.0f, 1.0f, 1.0f);                  // Top Right Of The Quad (Left)
        glVertex3f(-1.0f, 1.0f,-1.0f);                  // Top Left Of The Quad (Left)
        glVertex3f(-1.0f,-1.0f,-1.0f);                  // Bottom Left Of The Quad (Left)
        glVertex3f(-1.0f,-1.0f, 1.0f);                  // Bottom Right Of The Quad (Left)

        glColor3f(1.0f,0.0f,1.0f);                      // Set The Color To Violet
        glVertex3f( 1.0f, 1.0f,-1.0f);                  // Top Right Of The Quad (Right)
        glVertex3f( 1.0f, 1.0f, 1.0f);                  // Top Left Of The Quad (Right)
        glVertex3f( 1.0f,-1.0f, 1.0f);                  // Bottom Left Of The Quad (Right)
        glVertex3f( 1.0f,-1.0f,-1.0f); // Bottom Right Of The Quad (Right)
    glEnd();

    glColor3f(1.0,1.0,1.0);

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, i+1);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, i+1);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, i+1);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, i+1);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Blank out screen using OpenGL
    // glClearColor(0.0, 0.0, 1.0, 1.0);
    // glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(window);
}
