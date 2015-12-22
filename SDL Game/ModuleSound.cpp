
#include "ModuleSound.h"
#include "SDL/include/SDL.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/lib/x86/SDL2_mixer.lib")

ModuleSound::ModuleSound()
{
}


ModuleSound::~ModuleSound()
{
}

bool ModuleSound::Init(){

	// init SDL AUDIO
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		LOG("No se pudo iniciar SDL: %s\n", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(22050, AUDIO_S16, 2, 4096)) {
		LOG("No inint SDL_mixer %s\n", Mix_GetError());
		return false;
	}

	return true;
}


bool ModuleSound::Start(){
	

	return true;
}

Mix_Music* const ModuleSound::LoadMusicLevel(const char* path)
{
	Mix_Music* musicLevel = NULL;

	musicLevel = Mix_LoadMUS(path);
	if (musicLevel == NULL) {
		LOG("Problem load music %s\n", Mix_GetError());
		return NULL;
	}

	return musicLevel;
}

bool const ModuleSound::PlayMusicLevel(Mix_Music* song){
	
	// Paly music
	// this funtion return the number channel 
	if (Mix_PlayMusic(song, -1) != 0)
		return false;
	return true;

}

Mix_Chunk* const ModuleSound::LoadSound(const char* path){

	Mix_Chunk *sound = NULL;

	sound = Mix_LoadWAV(path);
	if (sound == NULL) {
		LOG("Problem load sound jump %s\n", Mix_GetError());
		return NULL;
	}
	return sound;
}

bool const ModuleSound::PlaySoundEspecific(Mix_Chunk * sound){

	Mix_PlayChannel(-1, sound, 0);
	return true;
}


bool ModuleSound::CleanUp(){
	
	// Stop music
	Mix_HaltMusic();

	// clse library Mix
	atexit(Mix_CloseAudio);

	// free recurses
	//Mix_FreeMusic(musicGame);

	return true;
}