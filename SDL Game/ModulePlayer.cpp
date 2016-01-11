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
	walkright.speed = 0.08f;

	// walk left
	walkleft.frames.push_back({ 199, 4, 21, 30 });
	walkleft.frames.push_back({ 233, 4, 21, 30 });
	walkleft.frames.push_back({ 273, 4, 21, 30 });
	walkleft.loop = true;
	walkleft.speed = 0.08f;

	// move jump right
	jumpright.frames.push_back({ 40, 37, 24, 36 });
	jumpright.frames.push_back({ 75, 37, 24, 36 });
	jumpright.frames.push_back({ 107, 37, 24, 36 });
	jumpright.frames.push_back({ 142, 37, 24, 36 });
	jumpright.frames.push_back({ 181, 37, 24, 36 });
	jumpright.frames.push_back({ 214, 37, 24, 36 });
	jumpright.frames.push_back({ 6, 37, 24, 36 });
	jumpright.loop = true;
	jumpright.speed = 0.1f;

	// move jump left
	jumpright.frames.push_back({ 100, 1, 32, 14 });
	jumpright.frames.push_back({ 132, 0, 32, 14 });
	jumpright.loop = false;
	jumpright.speed = 0.1f;

	// Move down right
	downright.frames.push_back({ 6, 38, 21, 30 });
	downright.loop = false;
	downright.speed = 0.1f;

	// Move down left
	downleft.frames.push_back({ 251, 38, 21, 30 });
	downleft.loop = false;
	downleft.speed = 0.1f;

	// shot particle
	shot.anim.frames.push_back({ 199, 4, 21, 30 });
	shot.anim.frames.push_back({ 199, 4, 21, 30 });
	shot.speed.x = 7;
	shot.life = 1000;
	shot.anim.speed = 0.05f;
	
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

	SDL_Texture* particles = App->textures->Load("../Game/Animation/"SHOT_FILE);
	shot.graphics = particles;

	//explosion.fx = App->audio->LoadFx("explosion.wav");
	//laser.fx = App->audio->LoadFx("slimeball.wav");

	collider = App->collision->AddCollider({ 500, 500, 19, 24 }, COLLIDER_PLAYER, this);
	colliderGround = App->collision->AddCollider({ 502, 503, 10, 2 }, COLLIDER_PLAYER, this);
	finished = false;
	current_animation = &idleright;
	return true;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

update_status ModulePlayer::PreUpdate(){
	int speed = 1;
	++position.y;//gravedad

	if (App->input->GetKey(SDL_SCANCODE_N) == KEY_UP)
	{
		if (direction){
			App->particles->AddParticle(shot, position.x, position.y +5, COLLIDER_PLAYER_SHOT,0,direction);
		}
		else
		{
			App->particles->AddParticle(shot, position.x, position.y +5, COLLIDER_PLAYER_SHOT,0,direction);
		}
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
		return UPDATE_CONTINUE;
	}

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
		return UPDATE_CONTINUE;
	}

	
	
	if (direction)
		{
			current_animation = &idleright;
		}
	else
		{
			current_animation = &idleleft;
		}
	
	return UPDATE_CONTINUE;
}

update_status ModulePlayer::Update()
{
	
	
	if (finished == true){//dead player
		//comprobar las vidas y dependiendo de las que te queden salie a pantalla principal


		App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
		return UPDATE_CONTINUE;
	}

	if (jump){
		
		if (direction){
			if (current_animation != &jumpright)
			{
				jumpright.Reset();
				current_animation = &jumpright;
			}
		}
		else
		{//cargar animacion salto
		/*	if (current_animation != &jumpleft)
			{
				jumpleft.Reset();
				current_animation = &jumpleft;
			}*/
		}
		App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));	
	
		if (frameAnimacion < 6){
			position.y -= 6;
			++frameAnimacion;
		}
		else{
			jump = false;
		}
		return UPDATE_CONTINUE;
	}

	


	/*if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN)
	{
		if (current_animation != &jumpright)
		{
			jumpright.Reset();
			current_animation = &jumpright;
		}
		App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
		return UPDATE_CONTINUE;
	}*/

	/*if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN)//jump left
	{
			position.y -= 10;
			position.x -= 5;
			current_animation = &jumpleft;
	
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN)//jump right
	{
			position.y -= 10;
			position.x += 5;
			current_animation = &jumpright;
	}*/

	if (!collidingGround){
		
		if (direction)
		{
			current_animation = &downright;
		}
		else
		{
			current_animation = &downleft;
		}	
	}
	
	
	collidingGround = false;

	collider->SetPos(position.x, position.y);
	colliderGround->SetPos(position.x+5, position.y+25);

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && c2->type == COLLIDER_WALL)
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

	if (c1 == collider && c2->type == COLLIDER_BOSS)
	{
		LOG("lost life");
		//App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_NONE);
		//App->fade->FadeToBlack((Module*)App->scene_intro, (Module*)App->scene_space, 1.0f);
		

	}

	if (c1 == colliderGround && c2->type == COLLIDER_GROUND){
		
		collidingGround = true;
		--position.y;

		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN)
		{
			frameAnimacion = 0;
			jump = true;
		}

		
	}
}