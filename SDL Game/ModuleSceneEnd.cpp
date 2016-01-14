#include "Application.h"
#include "ModuleSceneEnd.h"
#include "ModuleSound.h"
#include "ModuleInput.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScene.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

ModuleSceneEnd::ModuleSceneEnd(bool start_enabled) : Module(start_enabled)
{
}

//destructor
ModuleSceneEnd::~ModuleSceneEnd()
{
}


bool ModuleSceneEnd::Start(){

	LOG("Scene Start End.............");

	textureEnd = App->textures->Load("../Game/Scene/"SCENE_END);// load texture
	if (textureEnd == NULL){
		LOG("Texture don't load")
			return false;
	}
	App->sound->PlayMusic("../Game/Music/"SONG_END, 0.0f);
	return true;
}


update_status ModuleSceneEnd::Update(){

	if (!(App->renderer->Blit(textureEnd, 0, 0, NULL)))//render return true
		return UPDATE_ERROR;

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->sound->StopMusic();
		App->fade->FadeToBlack(App->scene, this, 1.0f);
	}

	return UPDATE_CONTINUE;
}


bool ModuleSceneEnd::CleanUp(){

	LOG("Unloading scene");

	App->textures->Unload(textureEnd);
	return true;
}