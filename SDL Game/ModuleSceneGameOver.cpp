#include "Application.h"
#include "ModuleSceneGameOver.h"
#include "ModuleSound.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

ModuleSceneGameOver::ModuleSceneGameOver(bool start_enabled) : Module(start_enabled)
{
}

//destructor
ModuleSceneGameOver::~ModuleSceneGameOver()
{
}


bool ModuleSceneGameOver::Start(){

	LOG("Scene Start GameOver.............");

	texture = App->textures->Load("../Game/scene/"SCENE_GAMEOVER);// load texture 
	if (texture == NULL){
		LOG("Texture don't load")
			return false;
	}
	App->sound->PlayMusic("../Game/Music/"SONG_GAMEOVER, 0.0f);
	timer.Start();
	return true;
}


update_status ModuleSceneGameOver::Update(){

	if (!(App->renderer->Blit(texture, 0, 0, NULL)))//render return true
		return UPDATE_ERROR;

	if (timer.Read() > 3000){
		App->sound->StopMusic();
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
		{
			App->fade->FadeToBlack(App->scene, this, 1.0f);
		}
	}

	return UPDATE_CONTINUE;
}


bool ModuleSceneGameOver::CleanUp(){

	LOG("Unloading scene");

	App->textures->Unload(texture);
	return true;
}