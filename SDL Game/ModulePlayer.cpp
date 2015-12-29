#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"


ModulePlayer::ModulePlayer(bool start_enable) : Module(start_enable)
{
	// idleright animation (just the ship)
	idleright.frames.push_back({ 4,4, 21, 30});

	// idleleft animation (just the ship)
	idleleft.frames.push_back({ 156, 4, 21,30 });

	// walk right
	walkright.frames.push_back({ 44, 4, 21, 30 });
	walkright.frames.push_back({ 79, 4, 21, 30 });
	walkright.frames.push_back({ 118, 4, 21, 30 });
	walkright.loop = true;
	walkright.speed = 0.1f;

	// walk left
	walkleft.frames.push_back({ 199, 4, 21, 30 });
	walkleft.frames.push_back({ 233, 4, 21, 30 });
	walkleft.frames.push_back({ 273, 4, 21, 30 });
	walkleft.loop = true;
	walkleft.speed = 0.1f;

	// move jump right
	jumpright.frames.push_back({ 100, 1, 32, 14 });
	jumpright.frames.push_back({ 132, 0, 32, 14 });
	jumpright.loop = false;
	jumpright.speed = 0.1f;

	// move jump left
	jumpright.frames.push_back({ 100, 1, 32, 14 });
	jumpright.frames.push_back({ 132, 0, 32, 14 });
	jumpright.loop = false;
	jumpright.speed = 0.1f;

	// Move down right
	downright.frames.push_back({ 33, 1, 32, 14 });
	downright.frames.push_back({ 0, 1, 32, 14 });
	downright.loop = false;
	downright.speed = 0.1f;

	// Move down left
	downright.frames.push_back({ 33, 1, 32, 14 });
	downright.frames.push_back({ 0, 1, 32, 14 });
	downright.loop = false;
	downright.speed = 0.1f;




}


ModulePlayer::~ModulePlayer()
{
}

bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("../Game/Animation/"SPRITE_FILE);

	position.x = 15;
	position.y = 12;

	//SDL_Texture* particles = App->textures->Load("particles.png");
	//explosion.graphics = laser.graphics = particles;

	//explosion.fx = App->audio->LoadFx("explosion.wav");
	//laser.fx = App->audio->LoadFx("slimeball.wav");

	collider = App->collision->AddCollider({ 0, 0, 21, 30 }, COLLIDER_PLAYER, this);

	finished = false;
	return true;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}


update_status ModulePlayer::Update()
{
	int speed = 1;
	
	if (finished == true)
		return UPDATE_CONTINUE;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (direction)
			direction = false;
		if (current_animation != &walkleft)
		{
			downright.Reset();
			current_animation = &walkleft;
		}
		position.x -= speed;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (!direction)
			direction = true;
		if (current_animation != &walkright)
		{
			walkright.Reset();
			current_animation = &walkright;
		}
		position.x += speed;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
	{
		position.y -= speed;
		if (current_animation != &jumpright)
		{
			jumpright.Reset();
			current_animation = &jumpright;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		//App->particles->AddParticle(laser, position.x + 28, position.y, COLLIDER_PLAYER_SHOT);
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
	{
		if (direction)
		{
			current_animation = &idleright;
		}
		else
		{
			current_animation = &idleleft;
		}
	}

	collider->SetPos(position.x, position.y);

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider)
	{
		//App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_NONE);
		//App->fade->FadeToBlack((Module*)App->scene_intro, (Module*)App->scene_space, 1.0f);
		if (direction){
			--position.x;
		}
		else{
			++position.x;
		}
		
	}
}