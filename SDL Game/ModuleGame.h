#ifndef __MODULEGAME_H__
#define __MODULEGAME_H__


#include "Globals.h"
#include "Module.h"
#include "ModuleTextures.h"
#include "Timer.h"


class ModuleGame : public Module
{
public:
	ModuleGame(bool start_enabled = true);
	~ModuleGame();
	bool Start();
	update_status Update();
	bool CleanUp();


private:
	SDL_Texture* textureScene = NULL;
	SDL_Texture* textureScene2 = NULL;
	SDL_Texture* BackgroundScene = NULL;
	SDL_Texture* headScene = NULL;
	SDL_Texture* life2 = NULL;
	SDL_Texture* life1 = NULL;
	SDL_Texture* life0 = NULL;
	bool changeScene = true;
	bool reinit = false;
	Timer timer;
	uint32 delay = 2;

};

#endif // __MODULEGAME_H__