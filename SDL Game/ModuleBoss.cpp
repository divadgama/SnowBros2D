#include "Globals.h"
#include "Application.h"
#include "ModuleBoss.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemy.h"
#include "SDL/include/SDL.h"

ModuleBoss::ModuleBoss(bool start_enabled) : Module(start_enabled)
{
	
	idle.frames.push_back({ 6, 500, 81, 88 });//rugido y abre la boca
	idle.frames.push_back({ 95, 500, 81, 88 });
	idle.frames.push_back({ 185, 500, 83, 89 });
	idle.loop = true;
	idle.speed = 0.05f;


	idle2.frames.push_back({ 286, 481, 81, 105 });
	idle2.frames.push_back({ 6, 500, 81, 88 });//pequeños saltitos
	idle2.loop = true;
	idle2.speed = 0.07f;


	jump.frames.push_back({ 286, 481, 81, 105 });
	
	
	shot.frames.push_back({ 6, 500, 81, 88 });//crea los enemigos
	shot.frames.push_back({ 286, 481, 81, 105 });
	shot.frames.push_back({ 377, 463, 81, 121 });
	shot.loop = false;
	shot.speed = 0.03f;


	die.frames.push_back({ 286, 481, 81, 105 });
	die.frames.push_back({ 603, 496, 102, 86 });
	die.frames.push_back({ 476, 531, 118, 52 });
	die.loop = false;
	die.speed = 0.02f;

	finished = false;
	current_animation = &idle;

}


ModuleBoss::~ModuleBoss()
{
	if (collider != nullptr)
		collider->to_delete = true;
	if (colliderPoint != nullptr)
		colliderPoint->to_delete = true;
	if (colliderGround != nullptr)
		colliderGround->to_delete = true;
}

bool ModuleBoss::Start()
{
	LOG("Loading Boss");
	timer.Start();
	graphics = App->textures->Load("../Game/Animation/"SPRITE_FILE);

	enemyGrafic = App->textures->Load("../Game/Animation/"SPRITE_FILE);
	Enemys.graphics = enemyGrafic;

	position.x = 180;
	position.y = 0;

	//effect
	dano = App->sound->LoadFx("../Game/Effects/"SOUND_BOSSDANO);

	SDL_Rect r = idle.PeekCurrentFrame();
	collider = App->collision->AddCollider({ 1000, 1000, r.w-10, r.h-13 }, COLLIDER_BOSS, this);
	colliderPoint = App->collision->AddCollider({ 1000, 1000, 118, 50}, COLLIDER_POINT, this);
	colliderGround = App->collision->AddCollider({ 1000, 1000, 50, 2}, COLLIDER_BOSS, this);
	App->enemy->Enable();
	return true;
}

bool ModuleBoss::CleanUp()
{
	LOG("Unloading Boss");

	App->textures->Unload(graphics);
	App->textures->Unload(enemyGrafic);

	return true;
}



update_status ModuleBoss::PreUpdate(){
	
	++position.y;//gravedad
	
	if (life <= 1){

		finished = true;
		App->enemy->DeleteEnemy();
		App->sound->StopMusic();
		if ((timer.Read() - delayFinish) > 10000)
		{
			diebool = true;
		}
		return UPDATE_CONTINUE;
	}

	if (!finished){//dead boss
		if ((timer.Read() - delay)>2500){//cada segundo cambia de comportamiento
			delay = timer.Read();
			option = rand() % 3 + 1;
			if (option == preoption){
				option = 1;
			}
			preoption = option;
			switch (option)
			{
			case 1://rugidos
				shotboolean = false;
				still = false;
				break;
			case 2://se queda parado y pequeños saltitos
				still = true;
				shotboolean = false;		
				break;
			case 3://crea los enemigos shot y cambia de plataforma
				still = false;
				shotboolean = true;
				createEnemy = true;
				count = 0;
				if (plataformatop){
					plataformatop = false;
				}
				else{
					plataformatop = true;
				}
				break;
			default:
				break;
			}
		}
	}
	return UPDATE_CONTINUE;
}




update_status ModuleBoss::Update(){

	if (finished == true){//dead boss
		current_animation = &die;
		collider->active = false;
		colliderGround->active = false;
		colliderPoint->SetPos(position.x, position.y);
		colliderGround->SetPos(position.x +10, position.y + 50);
		
		if ((timer.Read() - delayDie) > 500){//cada 500 aumenta posicion x
			delayDie = timer.Read();
			if (count < 3){
				position.x -= 20;
				++count;
			}
		}
		if (position.y>170){
			colliderGround->active = true;
		}
		if (!plataformatop){
			if (count <2){
				position.y-=2;
			}
		}
		App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

		if ((timer.Read() - delayDie) > 10000){//a los 10000 fin del juego
		 
			//fade to back fin del juego volver a pantalla principal y poner pantalla en negro y escribir congratulations
		
		}
		return UPDATE_CONTINUE;
	}
	if (still){
		if (current_animation != &idle2)
		{
			idle2.Reset();
			current_animation = &idle2;
		}
		
		if ((timer.Read() - delayStill) > 450){//cada 450 aumenta posicion y -25
					delayStill = timer.Read();
					position.y -= 25;
					collider->SetPos(position.x+5, position.y+10);
					colliderGround->SetPos(position.x + 20, position.y+100);
					App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
					return UPDATE_CONTINUE;
			}
		else
		{
			colliderGround->SetPos(position.x + 20, position.y + 85);
			collider->SetPos(position.x + 5, position.y + 10);
		}
		App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
		return UPDATE_CONTINUE;
	}

	if (shotboolean){
		//crear los enemigos
		if (createEnemy){
			optionEnemy = rand() % 2 + 1;
			switch (optionEnemy)
			{
			case 1:
				App->enemy->AddEnemy(Enemys, position.x-20, position.y +10);
				App->enemy->AddEnemy(Enemys, position.x, position.y + 5);
				break;
			default:
				App->enemy->AddEnemy(Enemys, position.x-40, position.y-30);
				App->enemy->AddEnemy(Enemys, position.x-30, position.y+5);
				App->enemy->AddEnemy(Enemys, position.x, position.y + 5);
				break;
			}
			createEnemy = false;
		}
		
		if (current_animation != &shot)
		{
			shot.Reset();
			current_animation = &shot;
		}
		if (plataformatop){
			if ((timer.Read() - delayStill) > 200){//cada 500 aumenta posicion x
				delayStill = timer.Read();
				if (count == 0){
					position.y -= 50;
				}
				if (count == 1){
					position.y -= 70;
				}
				++count;
			}			
			if (position.y >= 51){
				
				idle.Reset();
				current_animation = &idle;
			}
			colliderGround->SetPos(200, 200);
			collider->SetPos(position.x + 5, position.y + 10);
			App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
			return UPDATE_CONTINUE;
		}
		else
		{
			if ((timer.Read() - delayStill) > 200){//cada 500 aumenta posicion x
				delayStill = timer.Read();
				if (count == 0){
					position.y -= 70;
				}
				if (count == 1){
					position.y -= 170;
				}
				++count;
			}		
			if (position.y >= 30){
				idle.Reset();
				current_animation = &idle;		
			}
			colliderGround->SetPos(200,130);
			collider->SetPos(position.x + 5, position.y + 10);
			App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
			return UPDATE_CONTINUE;

		}
		

		
	}
	if (!collidingGround){

			current_animation = &jump;
			colliderGround->SetPos(position.x + 20, position.y + 100);
			collider->SetPos(position.x + 5, position.y + 10);
			App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
			return UPDATE_CONTINUE;
	}

	if (colliderGround && !shotboolean && !still)
	{
		if (current_animation != &idle)
		{
			idle.Reset();
			current_animation = &idle;
		}
		//sonido de rugido
		if ((timer.Read() - delayStill) > 450){//cada 500 rugido
			delayStill = timer.Read();
			
		}
		collider->SetPos(position.x + 5, position.y + 10);
		colliderGround->SetPos(position.x + 20, position.y + 85);
		App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
		return UPDATE_CONTINUE;
	}
	return UPDATE_CONTINUE;
}



void ModuleBoss::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == colliderGround && c2->type == COLLIDER_GROUND)
	{
		collidingGround = true;
		--position.y;
	}

	if (c1 == collider)
	{
		if (c2->type == COLLIDER_PLAYER_SHOT){
			--life;
			LOG("LIFE BOSS: %d", life);
			++score;
			//sonido de recibir daño
			App->sound->PlayFx(dano);
		}
		if (c2->type == COLLIDER_BALL_MOVE){
			life-=5;
			score = +10;
			LOG("LIFE BOSS: %d", life);
			//sonido de recibir daño
			App->sound->PlayFx(dano);
		}
		if (life <= 1){
			delayFinish =timer.Read();
			count = 0;
		}
		
		
	}
	if (c1 == colliderPoint && c2->type == COLLIDER_PLAYER_SHOT){
		++score;
		LOG("%d", score);
		//sonido de recibir daño
		App->sound->PlayFx(dano);
	}
}