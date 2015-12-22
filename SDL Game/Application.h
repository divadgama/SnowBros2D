#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleScene;
class ModuleSound;
class ModuleFadeToBlack;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	
	ModuleSound* sound;
	ModuleFadeToBlack* fade;

	//module logic game
	ModuleScene* scene;
private:

	std::list<Module*> modules;
	Module* first_scene = nullptr;
};

extern Application* App;