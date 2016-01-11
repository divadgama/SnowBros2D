#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleSound;
class ModuleFadeToBlack;
class ModuleParticles;
class ModuleCollision;

class ModuleScene;
class ModuleDebug;
class ModuleBoss;
class ModuleEnemy;
class ModulePlayer;

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
	ModuleParticles* particles;
	ModuleCollision* collision;

	//module logic game
	ModuleScene* scene;
	ModuleDebug* debug;
	ModuleBoss* boss;
	ModuleEnemy* enemy;
	ModulePlayer* player;

private:

	std::list<Module*> modules;
	Module* first_scene = nullptr;
};

extern Application* App;

#endif // __APPLICATION_CPP__