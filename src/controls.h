#ifndef CONTROLS_H
#define CONTROLS_H

#include <stdbool.h>
#include <SDL_opengl.h>

extern GLfloat playerFaceY;
extern GLfloat playerLookY;
extern float playerPosX;
extern float playerPosZ;

extern bool turningLeft;
extern bool turningRight;
extern bool movingBack;
extern bool movingForward;

extern void resetControls();
extern void applyControlsToPlayer();

#endif