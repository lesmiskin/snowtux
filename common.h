#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include "mysdl.h"

typedef struct {
    float x;
    float y;
    float z;
} Coord;

typedef struct {
	double x, y;
	int width, height;
} Rect;

#define WIDTH 800
#define HEIGHT 800
#define SCALE 5

#define WINDOW_WIDTH WIDTH * SCALE
#define WINDOW_HEIGHT HEIGHT * SCALE

extern double calcDistance(Coord a, Coord b);
extern Rect makeRect(double x, double y, double width, double height);
extern bool inBounds(Coord point, Rect area);
extern Rect makeBounds(Coord origin, double width, double height);
extern Rect makeSquareBounds(Coord origin, double size);
extern SDL_Window *window;
extern bool running;
extern bool timer(long *lastTime, double hertz);
extern bool isDue(long now, long lastTime, double hertz);
extern void fatalError(const char *title, const char *message);
extern void quit(void);
extern char *combineStrings(const char *a, const char *b);
extern bool fileExists(const char *path);
extern int randomMq(int min, int max);
extern double sineInc(double offset, double *sineInc, double speed, double magnitude);
extern double cosInc(double offset, double *sineInc, double speed, double magnitude);
extern double getAngle(Coord a, Coord b);
extern bool chance(int probability);
extern double degToRad(double angle);

#endif