#include "ModuleGame.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleBoss.h"
#include "ModuleSound.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "ModuleSceneEnd.h"
#include "ModuleSceneGameOver.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

ModuleGame::ModuleGame(bool start_enabled) : Module(start_enabled)
{
	textureScene = NULL;
}


ModuleGame::~ModuleGame()
{
}

bool ModuleGame::Start(){

	LOG("Game Start.............");

	textureScene = App->textures->Load("../Game/scene/"SCENE_FILE1);// load texture map
	textureScene2 = App->textures->Load("../Game/scene/"SCENE_FILE2);// load texture map
	headScene = App->textures->Load("../Game/scene/"SCENE_HEAD);// load texture map
	life2 = App->textures->Load("../Game/scene/"SCENE_LIFE2);// load texture life
	life1 = App->textures->Load("../Game/scene/"SCENE_LIFE1);// load texture life
	life0 = App->textures->Load("../Game/scene/"SCENE_LIFE0);// load texture life
	if (textureScene == NULL || textureScene2 == NULL){
		LOG("Texture map don't load")
			return false;
	}
	App->collision->Enable(); // enable before collision
	App->player->Enable();


	App->sound->PlayMusic("../Game/Music/"SONG_LEVEL, 1.0f);

	App->collision->AddCollider({ 0, 0, 1, 240 }, COLLIDER_WALL);
	App->collision->AddCollider({ 267, 0, 1, 240 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, 223, 270, 10 }, COLLIDER_GROUND);
	App->collision->AddCollider({ 0, 89, 118, 2 }, COLLIDER_GROUND);
	App->collision->AddCollider({ 50, 123, 100, 2 }, COLLIDER_GROUND);
	App->collision->AddCollider({ 0, 156, 118, 2 }, COLLIDER_GROUND);
	App->collision->AddCollider({ 50, 189, 100, 2 }, COLLIDER_GROUND);
	App->collision->AddCollider({ 184, 139, 83, 2 }, COLLIDER_GROUND);
	App->collision->AddCollider({ 0, 0, 3, 190 }, COLLIDER_WALL_ENEMY);
	App->collision->AddCollider({ 265, 0, 3, 190 }, COLLIDER_WALL_ENEMY);

	reinit = true;
	
	return true;
}


update_status ModuleGame::Update(){

	if (App->boss->diebool){//final del boss
			App->boss->diebool = false;
			App->boss->finished = false;
			App->boss->plataformatop = false;
			App->boss->life=50;
			App->boss->diebool = false;
			App->player->life = 3;
			App->boss->Disable();
			App->player->Disable();
			App->collision->Disable();
			App->fade->FadeToBlack(App->gameEnd, this, 1.0f);
			App->game->Disable();
		return UPDATE_CONTINUE;
	}
	if (App->player->diebool){//final del player
		App->player->diebool = false;
		App->boss->finished = false;
		App->boss->plataformatop = false;
		App->boss->life = 50;
		App->player->life = 3;
		App->boss->Disable();
		App->player->Disable();
		App->collision->Disable();
		App->sound->StopMusic();
		App->fade->FadeToBlack(App->gameOver, this, 1.0f);
		App->game->Disable();
		return UPDATE_CONTINUE;
	}

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

	if (!(App->renderer->Blit(headScene, 0, 0, NULL)))//render return true
		return UPDATE_ERROR;

	if (App->player->life == 1){
		if (!(App->renderer->Blit(life0, 4, 25, NULL)))//render return true
			return UPDATE_ERROR;
	}
	else if (App->player->life == 2)
	{
		if (!(App->renderer->Blit(life1, 4, 25, NULL)))//render return true
			return UPDATE_ERROR;
	}
	else
	{
		if (!(App->renderer->Blit(life2, 4, 25, NULL)))//render return true
			return UPDATE_ERROR;
	}

	return UPDATE_CONTINUE;
}


bool ModuleGame::CleanUp(){

	LOG("Unloading scene game");

	App->textures->Unload(textureScene);
	App->textures->Unload(textureScene2);
	App->textures->Unload(BackgroundScene);
	App->textures->Unload(headScene);
	App->textures->Unload(life2);
	App->textures->Unload(life1);
	App->textures->Unload(life0);
	return true;
}