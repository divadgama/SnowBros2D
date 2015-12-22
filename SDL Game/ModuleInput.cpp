#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "SDL/include/SDL.h"


ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
	//SDL_PumpEvents();
	
	//keyboard = SDL_GetKeyboardState(NULL);

	//if (keyboard[SDL_SCANCODE_ESCAPE]) {
		//return UPDATE_STOP;
	//}

	while (SDL_PollEvent(&my_event)) { // loop list event
	switch (my_event.type) { // type event
		 
		case SDL_KEYDOWN: // keyboard

			 if (my_event.key.keysym.sym == SDLK_ESCAPE) // Escape
				 return UPDATE_STOP;

			 if (my_event.key.keysym.sym == SDLK_SPACE) // Space
			 {
				 LOG("SOUND SOUND SOUND");
				if(!App->scene->Jump())//return true if sound corret
					return UPDATE_ERROR;

				 return UPDATE_CONTINUE;
			 }

		 break;
		 case SDL_QUIT: //"x" window
					 return UPDATE_STOP;
		 break;
					
		}
	}

	// TODO 1: Make the application properly close when ESC is pressed (do not use exit())

	// Homework: Make the application close up when pressing “X” button of the window

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}