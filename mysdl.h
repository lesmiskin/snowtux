#ifndef MYSDL_H
#define MYSDL_H

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_opengl.h>
#elif __APPLE__
    #include <SDL.h>
    #include <SDL_opengl.h>
#elif __linux__
	#include <SDL2/SDL.h>
    #include <SDL2/SDL_opengl.h>
#endif

#endif