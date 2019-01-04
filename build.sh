#!/bin/bash
# -lm = Link math library. Otherwise compiler compiles to constants and skips it where it can.

# Linux build
# -lGL permits compilation of functions from <SDL2/SDL_opengl.h>
# -lGLU permits compilation of functions from <GL/glu.h>
gcc *.c -std=c11 -lm `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_mixer -lGL -lGLU -o output.bin

# Windows build (after copying resources in /win32)
#gcc *.c -std=c99 \
#-Lc:\\SDL2\\sdl2\\lib -Ic:\\SDL2\\sdl2\\include\\SDL2 \
#-Lc:\\SDL2\\sdl2_mixer\\lib -Ic:\\SDL2\\sdl2_mixer\\include\\SDL2 \
#-Lc:\\SDL2\\sdl2_image\\lib -Ic:\\SDL2\\sdl2_image\\include\\SDL2 \
#-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer \
#-o output.bin
