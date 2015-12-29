#include "ModuleDebug.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleSound.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

ModuleDebug::ModuleDebug(bool start_enabled) : Module(start_enabled)
{
	textureScene = NULL;
}


ModuleDebug::~ModuleDebug()
{
}

bool ModuleDebug::Start(){

	LOG("Scene Start.............");

	textureScene = App->textures->Load("../Game/scene/"SCENE_FILE1);// load texture player 
	if (textureScene == NULL){
		LOG("Texture player don't load")
			return false;
	}
	App->collision->Enable(); // enable before player
	App->player->Enable();

	//App->sound->PlayMusic("../Game/Music/"SONG_LEVEL, 1.0f);

	App->collision->AddCollider({ 0, 0,1, 240 }, COLLIDER_WALL);
	App->collision->AddCollider({ 267, 0, 1, 240 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0,223,270,17}, COLLIDER_WALL);
	App->collision->AddCollider({ 0, 89, 118, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 50, 123, 100, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, 156, 118, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 50, 189, 100, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 184, 139, 83, 34 }, COLLIDER_WALL);
	
	return true;
}


update_status ModuleDebug::Update(){

	if (!(App->renderer->Blit(textureScene, 0, 0, NULL)))//render return true
		return UPDATE_ERROR;

	return UPDATE_CONTINUE;
}


bool ModuleDebug::CleanUp(){

	LOG("Unloading space scene");

	App->textures->Unload(textureScene);
	return true;
}