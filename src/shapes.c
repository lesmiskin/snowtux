#include <SDL_opengl.h>
#include <GL/glu.h>
#include "common.h"

void sideOfWall(float size) {
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(size, size, 0);
		glTexCoord2f(size, 0.0f); glVertex3f(-size, size, 0);
		glTexCoord2f(size, size); glVertex3f(-size, -size, 0);
		glTexCoord2f(0.0f, size); glVertex3f(size, -size, 0);
	glEnd();
}

void drawWall(point3 pos, float size) {
	glPushMatrix();
	glColor3ub(96,96,255);		// blue
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 1);

	// position the object (proportional to a cube grid)
	glTranslatef(pos.x * (size*2), pos.y * (size*2), pos.z * (size*2));

	for (int i = 0; i < 6; i++) {
		glPushMatrix();

		switch (i) {
			// front
			case 0:
				glTranslatef(0.0, 0.0, size * 2);
				glRotatef(0.0, 0.0, 0.0, 0.0);
				break;
			// back
			case 1:
				glTranslatef(0.0, 0.0, 0.0);
				glRotatef(180, 0.0, size, 0.0);
				break;
			// left
			case 2:
				glTranslatef(-size, 0.0, size);
				glRotatef(-90.0, 0.0, size, 0.0);
				break;
			// right
			case 3:
				glTranslatef(size, 0.0, size);
				glRotatef(90.0, 0.0, size, 0.0);
				break;
			// top
			case 4:
				glTranslatef(0.0, -size, size);
				glRotatef(90.0, size, 0.0, 0.0);
				break;
			// bottom
			case 5:
				glTranslatef(0.0, size, size);
				glRotatef(-90.0, size, 0.0, 0.0);
				break;
		}
		sideOfWall(size);
		glPopMatrix();
	}

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}