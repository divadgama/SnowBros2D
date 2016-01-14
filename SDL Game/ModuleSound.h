#ifndef __MODULESOUND_H__
#define __MODULESOUND_H__
#include <vector>
#include "Module.h"



#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;


class ModuleSound: public Module
{
public:
	ModuleSound(bool start_enabled = true);
	~ModuleSound();

	bool Init();
	bool CleanUp();

	void StopMusic();
	
	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

private:

	Mix_Music*	music = nullptr;
	std::vector<Mix_Chunk*>	fx;

};

#endif // __MODULESOUND_H__