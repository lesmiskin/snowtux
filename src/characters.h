#ifndef CHAR_H
#define CHAR_H

extern void charFrame();

#include <stdbool.h>
#include <SDL_opengl.h>

extern float playerX;
extern float playerY;

extern bool movingRight;
extern bool movingLeft;
extern bool jumpTry;

extern void resetControls(void);
extern void applyControlsToPlayer(void);

#endif