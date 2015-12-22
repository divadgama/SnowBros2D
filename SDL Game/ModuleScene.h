#pragma once

#include "Globals.h"
#include "Module.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSound.h"


class ModuleScene : public Module
{
public:
	ModuleScene(bool start_enabled = true);
	~ModuleScene();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();


private:
	SDL_Texture* texturePlayer=NULL;
	Mix_Music *musicLevel1= NULL;
	Mix_Chunk *soundJump = NULL;

public:
	bool Jump();

};

