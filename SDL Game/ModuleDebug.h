#ifndef __MODULEDEBUDG_H__
#define __MODULEDEBUDG_H__


#include "Globals.h"
#include "Module.h"
#include "ModuleTextures.h"
#include "Timer.h"


class ModuleDebug : public Module
{
public:
	ModuleDebug(bool start_enabled = true);
	~ModuleDebug();
	bool Start();
	update_status Update();
	bool CleanUp();


private:
	SDL_Texture* textureScene = NULL;
	SDL_Texture* textureScene2 = NULL;
	SDL_Texture* BackgroundScene = NULL;
	bool changeScene=true;
	Timer timer;
	uint32 delay = 2;

};

#endif // __MODULEDEBUDG_H__