// draw a cube, of X dimensions, at X position

#include <SDL_opengl.h>
#include <GL/glu.h>
#include "common.h"

void resetColor(void) {
    glColor3ub(255, 255, 255);
}

void applyColor(color color) {
    glColor3ub(color.r, color.g, color.b);
}

void applyState(point3 angle, point3 pos) {
    glRotatef(angle.x, 1, 0, 0);
    glRotatef(angle.y, 0, 1, 0);
    glRotatef(angle.z, 0, 0, 1);

    glTranslatef(pos.x, pos.y, pos.z);
}

void drawFace(point2 scale, color color, point3 angle, point3 pos) {
    applyColor(color);
    applyState(angle, pos);

    glBegin(GL_QUADS);
        glVertex3f(scale.x, scale.y, 0);
        glVertex3f(-scale.x, scale.y, 0);
        glVertex3f(-scale.x, -scale.y, 0);
        glVertex3f(scale.x, -scale.y, 0);
    glEnd();

    resetColor();
}

void drawPlainCube(float size, point3 pos) {
    glBegin(GL_QUADS);

    // topright, topleft, bottomleft, bottomright

    // top
    glColor3f(0.0f, 1.0f, 0.0f);                
    glVertex3f(1.0f, 1.0f, -1.0f);              
    glVertex3f(-1.0f, 1.0f, -1.0f);             
    glVertex3f(-1.0f, 1.0f, 1.0f);              
    glVertex3f(1.0f, 1.0f, 1.0f);               

    // bottom
    glColor3f(1.0f, 0.5f, 0.0f);                
    glVertex3f(1.0f, -1.0f, 1.0f);              
    glVertex3f(-1.0f, -1.0f, 1.0f);             
    glVertex3f(-1.0f, -1.0f, -1.0f);            
    glVertex3f(1.0f, -1.0f, -1.0f);             

    // front
    glColor3f(1.0f, 0.0f, 0.0f);                
    glVertex3f(1.0f, 1.0f, 1.0f);               
    glVertex3f(-1.0f, 1.0f, 1.0f);              
    glVertex3f(-1.0f, -1.0f, 1.0f);             
    glVertex3f(1.0f, -1.0f, 1.0f);              

    // back
    glColor3f(1.0f, 1.0f, 0.0f);                
    glVertex3f(1.0f, -1.0f, -1.0f);             
    glVertex3f(-1.0f, -1.0f, -1.0f);            
    glVertex3f(-1.0f, 1.0f, -1.0f);             
    glVertex3f(1.0f, 1.0f, -1.0f);              

    // left
    glColor3f(0.0f, 0.0f, 1.0f);                
    glVertex3f(-1.0f, 1.0f, 1.0f);              
    glVertex3f(-1.0f, 1.0f, -1.0f);             
    glVertex3f(-1.0f, -1.0f, -1.0f);            
    glVertex3f(-1.0f, -1.0f, 1.0f);             

    // right
    glColor3f(1.0f, 0.0f, 1.0f);                
    glVertex3f(1.0f, 1.0f, -1.0f);              
    glVertex3f(1.0f, 1.0f, 1.0f);               
    glVertex3f(1.0f, -1.0f, 1.0f);              
    glVertex3f(1.0f, -1.0f, -1.0f);             

    glEnd();

    // reset colors
    glColor3f(1.0, 1.0, 1.0);
}

void drawSolidCube(void) {
	// NB: 2.0 repeats twice etc.
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f);                      // Set The Color To Green
	glVertex3f(1.0f, 1.0f, -1.0f);                  // Top Right Of The Quad (Top)
	glVertex3f(-1.0f, 1.0f, -1.0f);                  // Top Left Of The Quad (Top)
	glVertex3f(-1.0f, 1.0f, 1.0f);                  // Bottom Left Of The Quad (Top)
	glVertex3f(1.0f, 1.0f, 1.0f);                  // Bottom Right Of The Quad (Top)

	glColor3f(1.0f, 0.5f, 0.0f);                      // Set The Color To Orange
	glVertex3f(1.0f, -1.0f, 1.0f);                  // Top Right Of The Quad (Bottom)
	glVertex3f(-1.0f, -1.0f, 1.0f);                  // Top Left Of The Quad (Bottom)
	glVertex3f(-1.0f, -1.0f, -1.0f);                  // Bottom Left Of The Quad (Bottom)
	glVertex3f(1.0f, -1.0f, -1.0f);                  // Bottom Right Of The Quad (Bottom)

	glColor3f(1.0f, 0.0f, 0.0f);                      // Set The Color To Red
	glVertex3f(1.0f, 1.0f, 1.0f);                  // Top Right Of The Quad (Front)
	glVertex3f(-1.0f, 1.0f, 1.0f);                  // Top Left Of The Quad (Front)
	glVertex3f(-1.0f, -1.0f, 1.0f);                  // Bottom Left Of The Quad (Front)
	glVertex3f(1.0f, -1.0f, 1.0f);                  // Bottom Right Of The Quad (Front)

	glColor3f(1.0f, 1.0f, 0.0f);                      // Set The Color To Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);                  // Top Right Of The Quad (Back)
	glVertex3f(-1.0f, -1.0f, -1.0f);                  // Top Left Of The Quad (Back)
	glVertex3f(-1.0f, 1.0f, -1.0f);                  // Bottom Left Of The Quad (Back)
	glVertex3f(1.0f, 1.0f, -1.0f);                  // Bottom Right Of The Quad (Back)

	glColor3f(0.0f, 0.0f, 1.0f);                      // Set The Color To Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);                  // Top Right Of The Quad (Left)
	glVertex3f(-1.0f, 1.0f, -1.0f);                  // Top Left Of The Quad (Left)
	glVertex3f(-1.0f, -1.0f, -1.0f);                  // Bottom Left Of The Quad (Left)
	glVertex3f(-1.0f, -1.0f, 1.0f);                  // Bottom Right Of The Quad (Left)

	glColor3f(1.0f, 0.0f, 1.0f);                      // Set The Color To Violet
	glVertex3f(1.0f, 1.0f, -1.0f);                  // Top Right Of The Quad (Right)
	glVertex3f(1.0f, 1.0f, 1.0f);                  // Top Left Of The Quad (Right)
	glVertex3f(1.0f, -1.0f, 1.0f);                  // Bottom Left Of The Quad (Right)
	glVertex3f(1.0f, -1.0f, -1.0f); // Bottom Right Of The Quad (Right)
	glEnd();

	// reset colors
	glColor3f(1.0, 1.0, 1.0);
}

void drawTexturedFace(void) {
	float i = -10.1f;

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, i + 1);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, i + 1);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, i + 1);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, i + 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}