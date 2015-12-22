#pragma once

#include "Globals.h"
#include "Module.h"
#include "SDL/include/SDL.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/lib/x86/SDL2_mixer.lib")

class ModuleSound: public Module
{
public:
	ModuleSound();
	~ModuleSound();

	bool Init();
	bool Start();
	bool CleanUp();

public:

	Mix_Music* const LoadMusicLevel(const char* path);
	Mix_Chunk* const LoadSound(const char* path);
	bool const PlayMusicLevel(Mix_Music*);
	bool const PlaySoundEspecific(Mix_Chunk *);

};

