#include "ModuleScene.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleGame.h"
#include "ModuleSound.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

ModuleScene::ModuleScene(bool start_enabled) : Module(start_enabled)
{
}

//destructor
ModuleScene::~ModuleScene()
{
}


bool ModuleScene::Start(){

	LOG("Scene Start.............");
	
	texturePlayer = App->textures->Load("../Game/scene/"SCENE_FIRST);// load texture player 
	if (texturePlayer==NULL){
		LOG("Texture  don't load")
		return false;
	}
	App->sound->PlayMusic("../Game/Music/"SONG_FIRST, 0.0f);
	
	timer.Start();
    return true;
}


update_status ModuleScene::Update(){

	if (!(App->renderer->Blit(texturePlayer, 0, 0, NULL)))//render return true
		return UPDATE_ERROR;

	if (timer.Read() > 2300){
		App->sound->StopMusic();
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
		{
			App->fade->FadeToBlack(App->game, this, 1.0f);	
		}
	}
	return UPDATE_CONTINUE;
}


bool ModuleScene::CleanUp(){

	LOG("Unloading space scene");

	App->textures->Unload(texturePlayer);
	return true;
}