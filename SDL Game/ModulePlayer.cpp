#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleEnemy.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"


ModulePlayer::ModulePlayer(bool start_enable) : Module(start_enable)
{
	//idlevacio animation
	idleVacio.frames.push_back({ 3, 3, 1, 1 });

	// idleright animation 
	idleright.frames.push_back({ 4,4, 21, 30});

	// idleleft animation 
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
	jumpright.frames.push_back({ 7, 37, 20, 36 });
	jumpright.loop = true;
	jumpright.speed = 0.2f;

	// move jump left
	jumpleft.frames.push_back({ 285, 37, 24, 36 });
	jumpleft.frames.push_back({ 321, 37, 24, 36 });
	jumpleft.frames.push_back({ 352, 37, 24, 36 });
	jumpleft.frames.push_back({ 387, 37, 24, 36 });
	jumpleft.frames.push_back({ 426, 37, 24, 36 });
	jumpleft.frames.push_back({ 459, 37, 24, 36 });
	jumpleft.frames.push_back({ 251, 37, 20, 36 });
	jumpleft.loop = true;
	jumpleft.speed = 0.2f;

	// Move down right
	downright.frames.push_back({ 6, 38, 21, 30 });
	downright.loop = false;
	downright.speed = 0.1f;

	// Move down left
	downleft.frames.push_back({ 251, 38, 21, 30 });
	downleft.loop = false;
	downleft.speed = 0.1f;

	//die

	die.frames.push_back({ 8, 117, 32, 36 });
	die.frames.push_back({ 43, 117, 32, 36 });
	die.frames.push_back({ 78, 117, 32, 36 });
	die.frames.push_back({ 110, 117, 32, 36 });
	die.frames.push_back({ 144, 117, 32, 36 });
	die.frames.push_back({ 180, 117, 32, 36 });
	die.frames.push_back({ 215, 117, 32, 36 });
	die.frames.push_back({ 248, 117, 32, 36 });
	die.loop = true;
	die.speed = 0.1f;


	//ball animation

	animballRight.frames.push_back({ 11, 161, 23, 28 });
	animballRight.frames.push_back({ 47, 161, 23, 28 });
	animballRight.frames.push_back({ 82, 161, 23, 28 });
	animballRight.loop = true;
	animballRight.speed = 0.1f;

	animballLeft.frames.push_back({ 116, 161, 23, 28 });
	animballLeft.frames.push_back({ 152, 161, 23, 28 });
	animballLeft.frames.push_back({ 187, 161, 23, 28 });
	animballLeft.loop = true;
	animballLeft.speed = 0.1f;
	
	//ball movimiento atrapado

	animballAtrapado.frames.push_back({ 11, 161, 23, 28 });
	animballAtrapado.frames.push_back({ 47, 161, 23, 28 });
	animballAtrapado.frames.push_back({ 82, 161, 23, 28 });
	animballAtrapado.loop = true;
	animballAtrapado.speed = 0.1f;


	//shot animation

	animshotRight.frames.push_back({ 113, 237, 26, 28 });
	animshotRight.frames.push_back({ 80, 237, 26, 28 });
	animshotRight.frames.push_back({ 47, 237, 26, 28 });
	animshotRight.frames.push_back({ 6, 237, 30, 28 });
	animshotRight.loop = true;
	animshotRight.speed = 0.3f;

	animshotLeft.frames.push_back({ 258, 237, 26, 28 });
	animshotLeft.frames.push_back({ 222, 237, 26, 28 });
	animshotLeft.frames.push_back({ 190, 237, 26, 28 });
	animshotLeft.frames.push_back({ 149, 237, 30, 28 });
	animshotLeft.loop = true;
	animshotLeft.speed = 0.3f;

	// shot particle

	shotRight.anim.frames.push_back({ 0, 11, 6, 8 });
	shotRight.anim.frames.push_back({ 11, 11, 6, 8 });
	shotRight.speed.x = 7;
	shotRight.life = 1000;
	shotRight.anim.speed = 0.9f;
	
	shotLeft.anim.frames.push_back({ 0, 1, 6, 8 });
	shotLeft.anim.frames.push_back({ 11, 1, 6, 8 });
	shotLeft.speed.x = 7;
	shotLeft.life = 1000;
	shotLeft.anim.speed = 0.9f;
	
}


ModulePlayer::~ModulePlayer()
{
	if (collider != nullptr)
		collider->to_delete = true;
	if (colliderGround != nullptr)
		colliderGround->to_delete = true;
}

bool ModulePlayer::Start()
{
	LOG("Loading player");
	graphics = App->textures->Load("../Game/Animation/"SPRITE_FILE);
	timer.Start();
	position.x = 100;
	position.y = 200;

    particles = App->textures->Load("../Game/Animation/"SHOT_FILE);
	shotLeft.graphics = shotRight.graphics = particles;

	//effect
	shotLeft.fx = shotLeft.fx = App->sound->LoadFx("../Game/Effects/"SOUND_SHOT);
	fxjump = App->sound->LoadFx("../Game/Effects/"SOUND_JUMP);
	fxdie = App->sound->LoadFx("../Game/Effects/"SOUND_DIE);

	collider = App->collision->AddCollider({ 500, 500, 19, 20 }, COLLIDER_PLAYER, this);
	colliderGround = App->collision->AddCollider({ 502, 503, 10, 2 }, COLLIDER_PLAYER, this);
	finished = false;
	current_animation = &idleright;
	return true;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->textures->Unload(particles);
	return true;
}

update_status ModulePlayer::PreUpdate(){
	int speed = 1;
	
	if (inicio){
		return UPDATE_CONTINUE;
	}

	if (!finished){

		++position.y;//gravedad

		/*if (App->input->GetKey(SDL_SCANCODE_I) == KEY_UP)// God mode
		{
			collider->active = false;
		}*/

		if (App->input->GetKey(SDL_SCANCODE_N) == KEY_UP)
		{
			shot = true;
			if (direction){
				App->particles->AddParticle(shotRight, position.x + 24, position.y, COLLIDER_PLAYER_SHOT, 0, direction);
			}
			else
			{
				App->particles->AddParticle(shotLeft, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, direction);
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
	}
		return UPDATE_CONTINUE;
	
}

update_status ModulePlayer::Update()
{
	if (inicio){
		collider->active = false;
		colliderGround->active = true;
		if (timer.Read() < 1000){
			if ((timer.Read() - delay) > 300){
				delay = timer.Read();
				App->renderer->Blit(graphics, position.x, position.y, &(idleright.GetCurrentFrame()));
			}
			else{
				App->renderer->Blit(graphics, position.x, position.y, &(idleVacio.GetCurrentFrame()));
			}
		}
		else{
			timer.Stop();
			collider->active = true;
			inicio = false;
		}	
		collider->SetPos(position.x, position.y+4);
		colliderGround->SetPos(position.x + 5, position.y + 25);
		return UPDATE_CONTINUE;
	}
	
	
	if (finished == true){//dead player
		App->enemy->DeleteEnemy();
		return UPDATE_CONTINUE;
	}


	if (jump){
		
		if (direction){
			App->renderer->Blit(graphics, position.x, position.y, &(jumpright.GetCurrentFrame()));
	
			if (frameAnimacion < 6){
				position.y -= 8;
				++frameAnimacion;
			}
			if (jumpright.NumFrames()==6){//end animacion
				jumpright.Reset();
				jump = false;
			}	
		}
		else
		{
		   App->renderer->Blit(graphics, position.x, position.y, &(jumpleft.GetCurrentFrame()));

			if (frameAnimacion < 6){
				position.y -= 8;
				++frameAnimacion;
			}
			if (jumpleft.NumFrames() == 6){//end animacion
				jumpleft.Reset();
				jump = false;
			}
		}
		
	
		
		collider->SetPos(position.x, position.y+4);
		colliderGround->SetPos(position.x + 5, position.y + 25);
		return UPDATE_CONTINUE;
	}

	if (shot){

		if (direction){
			App->renderer->Blit(graphics, position.x, position.y, &(animshotRight.GetCurrentFrame()));
			if (animshotRight.NumFrames() == 3){//end animacion
				animshotRight.Reset();
				shot = false;
			}
		}
		else
		{
			App->renderer->Blit(graphics, position.x, position.y, &(animshotLeft.GetCurrentFrame()));
			
			if (animshotLeft.NumFrames() == 3){//end animacion
				animshotLeft.Reset();
				shot = false;
			}
		}
		
		collider->SetPos(position.x, position.y+4);
		colliderGround->SetPos(position.x + 5, position.y + 25);
		return UPDATE_CONTINUE;
	}

	if (ball){

		if (direction){
			App->renderer->Blit(graphics, position.x, position.y, &(animballRight.GetCurrentFrame()));
			if (animballRight.NumFrames() == 2){//end animacion
				animballRight.Reset();
				ball = false;
			}
		}
		else
		{
			App->renderer->Blit(graphics, position.x, position.y, &(animballLeft.GetCurrentFrame()));

			if (animballLeft.NumFrames() == 2){//end animacion
				animballLeft.Reset();
				ball = false;
			}
		}

		collider->SetPos(position.x, position.y+4);
		colliderGround->SetPos(position.x + 5, position.y + 25);
		return UPDATE_CONTINUE;
	}


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

	collider->SetPos(position.x, position.y+4);
	colliderGround->SetPos(position.x+5, position.y+25);

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	return UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (finished == true){//dead player
		//comprobar las vidas y dependiendo de las que te queden salir a pantalla principal
		App->renderer->Blit(graphics, position.x, position.y, &(die.GetCurrentFrame()));
		colliderGround->active = false;
		if (die.NumFrames() == 7){
			if (life > 0){
				position.x = 100;
				position.y = 200;
				inicio = true;
				finished = false;
				return UPDATE_CONTINUE;
			}
			else{
				 diebool = true;
				 position.x = 100;
				 position.y = 200;
				 inicio = true;
				 finished = false;
				 return UPDATE_CONTINUE;
			}
		}
	}
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && c2->type == COLLIDER_WALL)
	{
		
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
		--life;
		App->sound->PlayFx(fxdie);
		collider->active = false;
		finished = true;
		die.Reset();
	}

	if (c1 == collider && c2->type == COLLIDER_ENEMY)
	{
		LOG("lost life");
		--life;
		App->sound->PlayFx(fxdie);
		collider->active = false;
		finished = true;
		die.Reset();
	}

	if (c1 == colliderGround && c2->type == COLLIDER_GROUND){
		
		collidingGround = true;
		--position.y;

		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN)
		{
			//play effect jump
			App->sound->PlayFx(fxjump);

			frameAnimacion = 0;
			jump = true;
		}
	}

	if (c1 == collider && c2->type == COLLIDER_BALL)
	{
		ball = true;
	}
}