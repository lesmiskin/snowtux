#include <SDL_opengl.h>
#include <GL/glu.h>

void drawSolidCube() {
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

void drawTexturedFace() {
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