#ifndef CONTROLS_H
#define CONTROLS_H

#include <stdbool.h>
#include <SDL_opengl.h>

extern float playerFaceY;
extern float playerLookY;
extern float playerPosX;
extern float playerPosZ;

extern bool turningLeft;
extern bool turningRight;
extern bool movingBack;
extern bool movingForward;

extern void resetControls(void);
extern void applyControlsToPlayer(void);

#endif