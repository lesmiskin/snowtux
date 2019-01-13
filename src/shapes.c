#include <stdlib.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include "common.h"
#include "graphics.h"
#include "controls.h"

void sideOfWall(float size) {
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(size, size, 0);
		glTexCoord2f(size, 0.0f); glVertex3f(-size, size, 0);
		glTexCoord2f(size, size); glVertex3f(-size, -size, 0);
		glTexCoord2f(0.0f, size); glVertex3f(size, -size, 0);
	glEnd();
}

float eyeBobInc = 0;
float eyePosY = 0;

long lastBlink = 0;
int blinkInterval = 0;
int lidCloseTime = 0;

long lastMove = 0;
int moveInterval = 0;
float moveSpeed = 0.0f;
point2 movePos = { 0,0 };
point2 moveDir = { 0,0 };

long lastPauseTime = 0;
int flitInc = 0;
bool shouldPause = false;
bool isPausing = false;

#define MAX_BLOOD 10

typedef struct {
    bool valid;
    point3 p;
    float alphaInc;
    float scale;
    float speed;
    float rot;
    float alphaSine;
} drip;
drip drips[MAX_BLOOD];

float RADIAN_CIRCLE = 3.141592 * 2;

float sineInc(float offset, float *sineInc, float speed, float magnitude) {
    *sineInc = *sineInc >= RADIAN_CIRCLE ? 0 : *sineInc + speed;

    float sineOffset = (sin(*sineInc) * magnitude);
    return offset - sineOffset;
}

void drawSprite(float size, float alpha, int textureIndex, point3 p, float rot) {
    glPushMatrix();

    glDisable(GL_DEPTH_TEST);
    glTranslatef(p.x, p.y, p.z);
    glRotatef(playerLookY, 0, 1, 0);        // always facing player
    glRotatef(rot, 0.0f, 0.0f, 1.0f);       // spin sprite
    glScalef(size, size, 1.0f);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 1.0f, alpha);     // gradually translucent.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, textureIndex);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 0);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
}

void spawnBlood() {
    for(int i=0; i < MAX_BLOOD; i++) {
        if(drips[i].valid) continue;
        point3 p = { randomMq(-15, 15) / 100.0f, eyePosY-0.35f, randomMq(-20, 20) / 100.0f };
        float scale = randomMq(30, 60) / 100.0f;
        float speed = randomMq(5, 10) / 1000.0f;
        float rot = randomMq(0, 360);
        drip d = { true, p, 1.0f, scale, speed, rot, 0.0f };
        drips[i] = d;
        break;
    }
}

void drawBlood() {
    for (int i = 0; i < MAX_BLOOD; i++) {
        if (!drips[i].valid) continue;
        drawSprite(drips[i].scale, drips[i].alphaInc, 4, drips[i].p, drips[i].rot);
        drips[i].p.y -= drips[i].speed;

        //drips[i].alphaInc -= 0.0125f;
        drips[i].alphaInc = sineInc(drips[i].alphaInc, &drips[i].alphaSine, 0.02f, 0.02f);
        if (drips[i].alphaInc < 0.0f) {
            drips[i].valid = false;
        }
    }
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

int randomMq(int min, int max) {
    return (rand() % (max + 1 - min)) + min;
}

void drawEye(point3 pos) {
    eyePosY += sineInc(0.0f, &eyeBobInc, 0.05, 0.005);

    glPushMatrix();
    glColor3ub(255, 255, 255);

	glTranslatef(0.0f, eyePosY, 0.0f);

    glRotatef(270.0f, 1.0f, 0.0f, 0.0f);

    GLUquadric* sphere = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    gluQuadricDrawStyle(sphere, GLU_FILL);

	// moving
    //if (isPausing) {
    //    if (isDue(lastPauseTime, 1000)) {
    //        isPausing = false;
    //        flitInc = 0;
    //    }
    //    glRotatef(movePos.x, 0.0f, 0.0f, 1.0f);
    //    glRotatef(movePos.y, 1.0f, 0.0f, 0.0f);
    //}else{
		//if(isDue(lastMove, moveInterval) && flitInc > 0) {
  //          isPausing = true;
  //          lastPauseTime = clock();
  //      } else if(isDue(lastMove, moveInterval)) {
		//	lastMove = SDL_GetTicks();
		//	moveInterval = 400;//randomMq(100, 200);
		//	moveSpeed = randomMq(0,1) == 1 ? 1.0f : -1.0f;//(float)randomMq(-5, 5) / 10.0f;
		//	moveDir.x = randomMq(-1, 1);
		//	moveDir.y = randomMq(-1, 1);
		//	flitInc++;
  //      }
  //      glRotatef(movePos.x += moveSpeed * 2, 0.0f, 0.0f, 1.0f);
  //      glRotatef(movePos.y += moveSpeed / 2, 1.0f, 0.0f, 0.0f);
  //  }
    // blinking
    if (isDue(lastBlink, blinkInterval)) {
        if (isDue(lastBlink, blinkInterval+lidCloseTime)) {
            lastBlink = SDL_GetTicks();
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

    gluSphere(sphere, 0.5, 16, 16);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}