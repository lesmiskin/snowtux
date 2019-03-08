#include "assets.h"
#include "graphics.h"
#include "level.h"
#include <stdbool.h>
#include <SDL.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

const int BOUND = 16;

// Controls
bool movingRight = false;
bool movingLeft = false;

// Position
float playerX = 50;
float playerY = 50;
bool onGround = false;

// Jumping
const float JUMP_SPEED = 2.0f;
const float JUMP_SLOW = 0.04f;
bool jumpTry = false;
bool isJumping = false;
long lastJump = 0;
float jumpInc = 0;

// Physics
float GRAVITY = 0.75f;
const int FLOOR = 100;

// Animation
long lastAnimTime = 0;
int animInc = 0;
SDL_RendererFlip flip = SDL_FLIP_NONE;

bool isWalking() {
	return movingLeft || movingRight;
}

bool facing() {
	return movingLeft;
}

bool onFlat() {
	return playerY >= FLOOR;
}

void resetControls(void) {
	movingRight = false;
	movingLeft = false;
	jumpTry = false;
}

void checkGround() {
	onGround = ((playerY + BOUND / 2) + GRAVITY >= FLOOR);
}

void applyControlsToPlayer(void) {
	if (movingRight) {
		playerX -= 1.0f;
	}
	else if (movingLeft) {
		playerX += 1.0f;
	}

	// Jumping

	// Start to jump
	if (jumpTry && onGround) {
		isJumping = true;
		lastJump = clock();
		jumpInc = JUMP_SPEED;
		onGround = false;
	}
	// Stop jumping
	if(isJumping && jumpInc == 0) {
		isJumping = false;
	}
	// Apply jumping
	if(isJumping) {
		playerY -= (jumpInc > 0 ? jumpInc -= JUMP_SLOW : 0);
	}
}

void charFrame() {
	checkGround();

	// Animation / flipping
	if (isWalking()) {
		if (isDue(lastAnimTime, 250)) {
			flip = facing() ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
			if (onGround) {
				if (animInc == 3) {
					animInc = 0;
				} else {
					animInc++;
				}
			}
			lastAnimTime = clock();
		}
	}
	else {
		animInc = 1;
		lastAnimTime = 0;
	}

	// Draw sprite
	if (onGround) {
		switch (animInc) {
			case 0:
				drawSprite(makeSprite(getTexture("tux1-01.png"), zeroCoord(), flip), makeCoord(playerX, playerY));
				break;
			case 1:
				drawSprite(makeSprite(getTexture("tux1-02.png"), zeroCoord(), flip), makeCoord(playerX, playerY));
				break;
			case 2:
				drawSprite(makeSprite(getTexture("tux1-03.png"), zeroCoord(), flip), makeCoord(playerX, playerY));
				break;
			case 3:
				drawSprite(makeSprite(getTexture("tux1-02.png"), zeroCoord(), flip), makeCoord(playerX, playerY));
				break;
		}
	} else {
		drawSprite(makeSprite(getTexture("tux1-jump.png"), zeroCoord(), flip), makeCoord(playerX, playerY));
	}

	// Falling
	if (!onGround) {
		playerY += GRAVITY;
	}
	//int bottomBound = playerY + BOUND/2;
	//if (bottomBound + GRAVITY >= FLOOR) {
	//	playerY = FLOOR - BOUND/2;
	//}
}
