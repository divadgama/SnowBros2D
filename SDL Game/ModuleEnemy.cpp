#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleEnemy.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

ModuleEnemy::ModuleEnemy(bool start_enabled) : Module(start_enabled)
{
}


ModuleEnemy::~ModuleEnemy()
{
}

bool ModuleEnemy::Start()
{
	LOG("Loading player");

	//graphics = App->textures->Load("../Game/Animation/"SPRITE_FILE);

	//position.x = 15;
	//position.y = 12;

	//collider = App->collision->AddCollider({ 0, 0, 19, 24 }, COLLIDER_PLAYER, this);
	//current_animation = &idleright;
	return true;
}

bool ModuleEnemy::CleanUp()
{
	LOG("Unloading player");

	//App->textures->Unload(graphics);

	return true;
}