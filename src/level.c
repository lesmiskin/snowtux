#include "assets.h"
#include "graphics.h"

const int TILE_SIZE = 8;

void drawLevel() {
	int offset = TILE_SIZE * 8;

	for (int i = 0; i < 20; i++) {
		drawSimpleTile("tile-01.png", makeCoord(offset + i*TILE_SIZE, 100));
	}
}