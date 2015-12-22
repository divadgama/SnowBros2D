#pragma once
#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_events.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();

private:
	const Uint8 *keyboard = NULL;
    SDL_Event my_event; // list event
};