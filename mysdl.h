#ifndef MYSDL_H
#define MYSDL_H

#ifdef _WIN32
    #include <SDL_image.h>
    #include <SDL_mixer.h>
#elif __APPLE__
		#include <SDL.h>
    #include <SDL2_Image/SDL_image.h>
    #include <SDL2_Mixer/SDL_mixer.h>
#elif __linux__
		#include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_mixer.h>
#endif

#endif
