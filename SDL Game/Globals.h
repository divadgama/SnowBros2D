#pragma once
#include <windows.h>
#include <stdio.h>

#include "SDL/include/SDL_rect.h"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned __int32 uint32;

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Deletes a buffer
#define RELEASE( x ) \
    { \
       if( x != nullptr ) \
	          { \
         delete x; \
	     x = nullptr; \
	          } \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
		{  \
       if( x != nullptr ) \
	          { \
           delete[] x; \
	       x = nullptr; \
	   		 } \
		 }

// Configuration -----------
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FULLSCREEN false
#define RESIZABLE true
#define BORDERLESS false
#define FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "Snow Bros"
#define SPRITE_FILE "sprites.png"
#define SONG_LEVEL1 "Skrillex.mp3"
#define SOUND_JUMP "jump.wav"