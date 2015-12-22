#include "ModuleScene.h"
#include "Application.h"

ModuleScene::ModuleScene(bool start_enabled) : Module(start_enabled)
{
}

//destructor
ModuleScene::~ModuleScene()
{
}


bool ModuleScene::Init(){

	LOG("Scene Init.............");
	return true;
}


bool ModuleScene::Start(){

	LOG("Scene Start.............");
	
	texturePlayer = App->textures->Load("../Game/"SPRITE_FILE);// load texture player 
	if (texturePlayer==NULL){
		LOG("Texture player don't load")
		return false;
	}
	musicLevel1 = App->sound->LoadMusicLevel("../Game/"SONG_LEVEL1);//load music level 1

	if (musicLevel1 == NULL){
		LOG("Fail load music level 1 SCENE")
			return false;
	}
	if (!App->sound->PlayMusicLevel(musicLevel1)){ //play music level 1
		LOG("Fail play music level 1 SCENE")
			return false;
	}

    return true;
}

bool ModuleScene::Jump(){

	soundJump=App->sound->LoadSound("../Game/"SOUND_JUMP);
	if (soundJump == NULL){
		LOG("Fail load sound jump SCENE")
			return false;
	}
	if (!App->sound->PlaySoundEspecific(soundJump)){
		LOG("Fail play sound jump SCENE")
			return false;
	}

	return true;
}



update_status ModuleScene::Update(){

	if (!(App->renderer->Blit(texturePlayer, 0, 0, NULL)))//render return true
		return UPDATE_ERROR;

	return UPDATE_CONTINUE;
}


bool ModuleScene::CleanUp(){

	LOG("Scene CleanUp.............");
	return true;
}