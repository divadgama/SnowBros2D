#ifndef __MODULESCENEGAMEOVER_H__
#define __MODULESCENEGAMEOVER_H__

#include "Globals.h"
#include "Module.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSound.h"
#include "Timer.h"

class ModuleSceneGameOver : public Module
{
public:
	ModuleSceneGameOver(bool start_enabled = true);
	~ModuleSceneGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();


private:
	SDL_Texture* texture = NULL;
	Timer timer;
};
#endif // __MODULESCENEGAMEOVER_H__