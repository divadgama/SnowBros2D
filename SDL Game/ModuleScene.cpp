#include "ModuleScene.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleSound.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
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
	
	texturePlayer = App->textures->Load("../Game/"SCENE_FILE1);// load texture player 
	if (texturePlayer==NULL){
		LOG("Texture player don't load")
		return false;
	}
	//App->sound->PlayMusic("../Game/"SONG_LEVEL1, 1.0f);
	App->player->Enable();
    return true;
}


update_status ModuleScene::Update(){

	if (!(App->renderer->Blit(texturePlayer, 0, 0, NULL)))//render return true
		return UPDATE_ERROR;

	return UPDATE_CONTINUE;
}


bool ModuleScene::CleanUp(){

	LOG("Unloading space scene");

	App->textures->Unload(texturePlayer);
	return true;
}