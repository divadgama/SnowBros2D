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
#define SCREEN_WIDTH 270
#define SCREEN_HEIGHT 240
#define FULLSCREEN false
#define RESIZABLE false
#define BORDERLESS false
#define FULLSCREEN_DESKTOP false
#define SCREEN_SIZE 3
#define VSYNC true
#define TITLE "Snow Bros"
#define SCENE_FILE1 "Escenario1.png"
#define SCENE_FILE2 "Escenario2.png"
#define SPRITE_FILE "SpriteAnimaciones.png"
#define SHOT_FILE "ShotSprites.png"
#define SONG_LEVEL "Boss_Yade.mp3"
#define SOUND_JUMP "jump.wav"