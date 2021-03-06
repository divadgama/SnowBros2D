#pragma once
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleScene.h"
#include "ModuleDebug.h"
#include "ModuleGame.h"
#include "ModuleSceneGameOver.h"
#include "ModuleSceneEnd.h"
#include "ModuleBoss.h"
#include "ModuleEnemy.h"
#include "ModulePlayer.h"


using namespace std;

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(sound = new ModuleSound());
	modules.push_back(fade = new ModuleFadeToBlack());
	modules.push_back(collision = new ModuleCollision());
	modules.push_back(particles = new ModuleParticles());

	// Game Module logic
	modules.push_back(scene = new ModuleScene(false));
	modules.push_back(debug = new ModuleDebug(false));
	modules.push_back(game = new ModuleGame(false));
	modules.push_back(gameOver = new ModuleSceneGameOver(false));
	modules.push_back(gameEnd = new ModuleSceneEnd(false));

	modules.push_back(enemy = new ModuleEnemy());
	modules.push_back(boss = new ModuleBoss(false));

	modules.push_back(player = new ModulePlayer(false));

	modules.push_back(renderer = new ModuleRender());

	// set first scene for the game
	first_scene = scene;
}

Application::~Application()
{

	for (list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it){
		RELEASE(*it);
	}
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}


bool Application::Start()
{
	bool ret = true;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}
	if (first_scene != nullptr)
		fade->FadeToBlack(first_scene, nullptr, 3.0f);

	return ret;
}




update_status Application::PreUpdate()
{
	update_status ret = UPDATE_CONTINUE;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PreUpdate();

	return ret;
}


update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Update();

	return ret;
}

update_status Application::PostUpdate()
{
	update_status ret = UPDATE_CONTINUE;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PostUpdate();

	return ret;
}


bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->CleanUp();

	return ret;
}
