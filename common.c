#include "common.h"
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

static const double RADIAN_CIRCLE = 6.28;
static const float PI = 3.141592;

double degToRad(double angle) {
    return angle * (PI/180);
}

long ticsToMilliseconds(long tics) {
    //we want the duration version of the platform-independent seconds, so we / 1000.
    long platformAgnosticMilliseconds = CLOCKS_PER_SEC / 1000;

    return tics / platformAgnosticMilliseconds;
}

bool isDue(long now, long lastTime, double hertz) {
    long timeSinceLast = ticsToMilliseconds(now - lastTime);
    return timeSinceLast >= hertz;
}

bool timer(long *lastTime, double hertz){
    long now = clock();
    if(isDue(now, *lastTime, hertz)) {
        *lastTime = now;
        return true;
    }else{
        return false;
    }
}

void fatalError(const char *title, const char *message) {
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR,
        title,
        message,
        window
    );
    SDL_Quit();
}

void quit(void) {
    running = false;
}

char *combineStrings(const char *a, const char *b) {
    //Allocate exact amount of space necessary to hold the two strings.
    char *result = malloc(strlen(a) + strlen(b) + 1);		//+1 for the zero-terminator
    strcpy(result, a);
    strcat(result, b);

    return result;
}

bool fileExists(const char *path) {
    return access(path, R_OK ) == 0;
}

double sineInc(double offset, double *sineInc, double speed, double magnitude) {
    *sineInc = *sineInc >= RADIAN_CIRCLE ? 0 : *sineInc + speed;

    double sineOffset = (sin(*sineInc) * magnitude);
    return offset - sineOffset;
}

double cosInc(double offset, double *sineInc, double speed, double magnitude) {
    *sineInc = *sineInc >= RADIAN_CIRCLE ? 0 : *sineInc + speed;

    double sineOffset = (cos(*sineInc) * magnitude);
    return offset - sineOffset;
}

int randomMq(int min, int max) {
    return (rand() % (max + 1 - min)) + min;
}

double getAngle(Coord a, Coord b) {
    return atan2(b.y - a.y, b.x - a.x);
}

bool chance(int probability) {
    //Shortcuts for deterministic scenarios (impossible and always)
    if(probability == 0) {
        return false;
    }else if (probability == 100) {
        return true;
    }

    int roll = randomMq(0, 100);			// dice roll up to 100 (to match with a percentage-based probability amount)
    return probability >= roll;			    // e.g. 99% is higher than a roll of 5, 50, and 75.
}

bool inBounds(Coord point, Rect area) {
    return
            point.x >= area.x && point.x <= area.width &&
            point.y >= area.y && point.y <= area.height;
}

Rect makeBounds(Coord origin, double width, double height) {
    Rect bounds = {
        origin.x - (width / 2),
        origin.y - (height / 2),
        origin.x + (width / 2),
        origin.y + (height / 2)
    };
    return bounds;
}

Rect makeSquareBounds(Coord origin, double size) {
    return makeBounds(origin, size, size);
}

Rect makeRect(double x, double y, double width, double height) {
    Rect rect = { x, y, width, height };
    return rect;
}