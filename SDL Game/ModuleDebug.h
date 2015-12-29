#ifndef __MODULEDEBUDG_H__
#define __MODULEDEBUDG_H__


#include "Globals.h"
#include "Module.h"
#include "ModuleTextures.h"


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
};

#endif // __MODULEDEBUDG_H__