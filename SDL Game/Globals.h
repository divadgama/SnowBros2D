#ifndef __GLOBAL_H__
#define __GLOBAL_H__
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
#define SCENE_END "Congratulations.png"
#define SCENE_GAMEOVER "GameOver.png"
#define SCENE_FIRST "PantallaInicio.png"
#define SCENE_HEAD "Cabecera.png"
#define SCENE_LIFE2 "life2.png"
#define SCENE_LIFE1 "life1.png"
#define SCENE_LIFE0 "life0.png"

//music and effect
#define SONG_LEVEL "Boss_Yade.mp3"
#define SONG_FIRST "Inicio.mp3"
#define SONG_END "Ending.mp3"
#define SONG_GAMEOVER "GameOver.mp3"
#define SOUND_JUMP "Jump.wav"
#define SOUND_BOSSDANO "BossDano.wav"
#define SOUND_CHOQUEBALL "ChoqueBola.wav"
#define SOUND_DIE "Muerte.wav"
#define SOUND_BALLBROKEN "RompeBola.wav"
#define SOUND_SHOT "Shot.wav"
#endif //__GLOBAL_H__