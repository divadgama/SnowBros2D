#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Globals.h"
#include "Module.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSound.h"
#include "Timer.h"


class ModuleScene : public Module
{
public:
	ModuleScene(bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update();
	bool CleanUp();

	Timer timer;

private:
	SDL_Texture* texturePlayer=NULL;
};

#endif // __MODULESCENE_H__