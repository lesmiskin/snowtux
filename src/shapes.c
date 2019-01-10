#include <SDL_opengl.h>
#include <GL/glu.h>
#include "common.h"
#include "graphics.h"

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

float RADIAN_CIRCLE = 3.141592*2;

float sineInc(float offset, float *sineInc, float speed, float magnitude) {
    *sineInc = *sineInc >= RADIAN_CIRCLE ? 0 : *sineInc + speed;

    float sineOffset = (sin(*sineInc) * magnitude);
    return offset - sineOffset;
}

float eyeBobInc = 0;
float eyePosY = 0;

// blinking.
// red eye (using PNG?)
// tendrils billboard

int randomMq(int min, int max) {
    return (rand() % (max + 1 - min)) + min;
}

// eye bobs
// eye has bloody bg
// TODO: bloody bg is rippled at edges somehow
// eye drains blood
// eye flits around (lerped)

long lastBlink = 0;
int blinkInterval = 0;
int lidCloseTime = 0;

void drawEye(point3 pos) {
    eyePosY += sineInc(0.0f, &eyeBobInc, 0.05, 0.005);

    glPushMatrix();
    glColor3ub(255, 255, 255);

    glTranslatef(0.0f, eyePosY, 0.0f);

    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);

    GLUquadric* sphere = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    gluQuadricDrawStyle(sphere, GLU_FILL);

    // blinking
    if (isDue(lastBlink, blinkInterval)) {
        if (isDue(lastBlink, blinkInterval+lidCloseTime)) {
            lastBlink = clock();
            blinkInterval = randomMq(500, 3000);
            lidCloseTime = randomMq(50, 100);
        }
        glBindTexture(GL_TEXTURE_2D, 3);
    }
    else {
        glBindTexture(GL_TEXTURE_2D, 2);
    }

    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);

    gluSphere(sphere, 0.5, 20, 20);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}