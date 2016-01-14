#ifndef __MODULESCENEEND_H__
#define __MODULESCENEEND_H__
#include "Globals.h"
#include "Module.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSound.h"

class ModuleSceneEnd : public Module
{
public:
	ModuleSceneEnd(bool start_enabled = true);
	~ModuleSceneEnd();

	bool Start();
	update_status Update();
	bool CleanUp();


private:
	SDL_Texture* textureEnd = NULL;
};
#endif // __MODULESCENEEND_H__