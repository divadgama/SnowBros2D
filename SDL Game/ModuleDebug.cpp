#include "ModuleDebug.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleBoss.h"
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

	textureScene = App->textures->Load("../Game/scene/"SCENE_FILE1);// load texture map
	textureScene2 = App->textures->Load("../Game/scene/"SCENE_FILE2);// load texture map
	if (textureScene == NULL || textureScene2 == NULL){
		LOG("Texture map don't load")
			return false;
	}
	App->collision->Enable(); // enable before collision
	App->player->Enable();
	
	
	//App->sound->PlayMusic("../Game/Music/"SONG_LEVEL, 1.0f);

	App->collision->AddCollider({ 0, 0,1, 240 }, COLLIDER_WALL);
	App->collision->AddCollider({ 267, 0, 1, 240 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, 223, 270, 10 }, COLLIDER_GROUND);
	App->collision->AddCollider({ 0, 89, 118, 2 }, COLLIDER_GROUND);
	App->collision->AddCollider({ 50, 123, 100, 2 }, COLLIDER_GROUND);
	App->collision->AddCollider({ 0, 156, 118, 2 }, COLLIDER_GROUND);
	App->collision->AddCollider({ 50, 189, 100, 2 }, COLLIDER_GROUND);
	App->collision->AddCollider({ 184, 139, 83, 2 }, COLLIDER_GROUND);
	
	return true;
}


update_status ModuleDebug::Update(){
	if (timer.Read() > 2000){
		App->boss->Enable();
	}
	if (timer.Read() < 3000){
		if ((timer.Read() - delay) > 300){
			delay = timer.Read();

			if (changeScene){
				BackgroundScene = textureScene;
				changeScene = false;
			}
			else
			{
				changeScene = true;
				BackgroundScene = textureScene2;
			}
		}
		if (!(App->renderer->Blit(BackgroundScene, 0, 0, NULL)))//render return true
			return UPDATE_ERROR;
	}
	else
	{
		if (!(App->renderer->Blit(textureScene2, 0, 0, NULL)))//render return true
			return UPDATE_ERROR;
	}
	
	

	return UPDATE_CONTINUE;
}


bool ModuleDebug::CleanUp(){

	LOG("Unloading space scene");

	App->textures->Unload(textureScene);
	App->textures->Unload(textureScene2);
	App->textures->Unload(BackgroundScene);
	return true;
}