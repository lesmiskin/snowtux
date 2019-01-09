#include <SDL_opengl.h>
#include <GL/glu.h>
#include "common.h"

void drawWallSide(float size) {
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, size, 0);
	glTexCoord2f(size, 0.0f); glVertex3f(-size, size, 0);
	glTexCoord2f(size, size); glVertex3f(-size, -size, 0);
	glTexCoord2f(0.0f, size); glVertex3f(size, -size, 0);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawWall(point3 pos, float size) {

	glPushMatrix();

	// make it blue (hack)
	glColor3ub(96,96,255);

	// position the object (proportional to a cube grid)
	glTranslatef(pos.x * (size*2), pos.y * (size*2), pos.z * (size*2));

	// front
	glPushMatrix();
		glTranslatef(0.0, 0.0, size * 2);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		drawWallSide(size);
	glPopMatrix();

	// back
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glRotatef(180, 0.0, size, 0.0);
		drawWallSide(size);
	glPopMatrix();

	// left
	glPushMatrix();
		glTranslatef(-size, 0.0, size);
		glRotatef(-90.0, 0.0, size, 0.0);
		drawWallSide(size);
	glPopMatrix();

	// right
	glPushMatrix();
		glTranslatef(size, 0.0, size);
		glRotatef(90.0, 0.0, size, 0.0);
		drawWallSide(size);
	glPopMatrix();

	// top
	glPushMatrix();
		glTranslatef(0.0, -size, size);
		glRotatef(90.0, size, 0.0, 0.0);
		drawWallSide(size);
	glPopMatrix();

	// bottom
	glPushMatrix();
		glTranslatef(0.0, size, size);
		glRotatef(-90.0, size, 0.0, 0.0);
		drawWallSide(size);
	glPopMatrix();

	// close out of our translated mode
	glPopMatrix();
}