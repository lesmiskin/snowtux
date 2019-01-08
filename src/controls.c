#include <math.h>
#include <stdbool.h>

bool turningLeft = false;
bool turningRight = false;
bool movingBack = false;
bool movingForward = false;

float piOver180 = 0.0174532925f;
float playerFaceY = 0;
float playerLookY = 0;
float playerPosX = 0;
float playerPosZ = 0;

void resetControls(void) {
	turningLeft = false;
	turningRight = false;
	movingForward = false;
	movingBack = false;
}

void applyControlsToPlayer(void) {
	if (turningLeft) {
		playerFaceY += 1.5f;
		playerLookY = playerFaceY;
	} else if (turningRight) {
		playerFaceY -= 1.5f;
		playerLookY = playerFaceY;
	}

	if (movingForward) {
		playerPosX -= (float)sin(playerLookY * piOver180) * 0.15f;
		playerPosZ -= (float)cos(playerLookY * piOver180) * 0.15f;
	} else if (movingBack) {
		playerPosX += (float)sin(playerLookY * piOver180) * 0.15f;
		playerPosZ += (float)cos(playerLookY * piOver180) * 0.15f;
	}
}