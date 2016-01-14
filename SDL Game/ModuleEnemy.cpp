#include "Globals.h"
#include "Application.h"
#include "ModuleEnemy.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSound.h"

using namespace std;

ModuleEnemy::ModuleEnemy()
{
}


ModuleEnemy::~ModuleEnemy()
{
}


void ModuleEnemy::AddEnemy(const Enemy& enemy, int x, int y){
	
	Enemy* p = new Enemy(enemy);
	p->timer.Start();
	p->position.x = x;
	p->position.y = y;

	p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, COLLIDER_ENEMY, this);
	p->colliderGround = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, COLLIDER_ENEMY, this);
	p->colliderBall = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, COLLIDER_BALL, this);
	p->colliderBallMove = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, COLLIDER_BALL_MOVE, this);
	p->colliderBall->active = false;
	p->colliderBallMove->active = false;

		p->animInitial.frames.push_back({ 18, 406, 18, 20 });
		p->animInitial.frames.push_back({ 50, 404, 20, 23 });
		p->animInitial.loop = false;
		p->animInitial.speed = 0.1f;

		p->animIldeRight.frames.push_back({ 50, 404, 20, 23 });
		p->animIldeRight.frames.push_back({ 80, 402, 22, 26 });
		p->animIldeRight.frames.push_back({ 114, 402, 24, 26 });
		p->animIldeRight.frames.push_back({ 149, 402, 24, 26 });
		p->animIldeRight.loop = false;
		p->animIldeRight.speed = 0.1f;
		
		p->animIldeleft.frames.push_back({ 293, 404, 20, 23 });
		p->animIldeleft.frames.push_back({ 323, 402, 22, 26 });
		p->animIldeleft.frames.push_back({ 357, 402, 22, 26 });
		p->animIldeleft.frames.push_back({ 357, 402, 22, 26 });
		p->animIldeleft.loop = false;
		p->animIldeleft.speed = 0.1f;

		p->animWalkRight.frames.push_back({ 182, 400, 26, 29 });
		p->animWalkRight.frames.push_back({ 217, 403, 26, 27 });
		p->animWalkRight.loop = true;
		p->animWalkRight.speed = 0.2f;

		p->animWalkLeft.frames.push_back({ 427, 400, 26, 29 });
		p->animWalkLeft.frames.push_back({ 460, 403, 26, 27 });
		p->animWalkLeft.loop = true;
		p->animWalkLeft.speed = 0.2f;	

		p->animAtrapado1.frames.push_back({ 154, 363, 24, 23 });
		p->animAtrapado2.frames.push_back({ 189, 360, 27, 27 });
		p->animAtrapado3.frames.push_back({ 222, 359, 29, 28 });
		p->animAtrapado4.frames.push_back({ 257, 353, 34, 34 });
	
		p->animBall.frames.push_back({ 14, 353, 34, 34 });
		p->animBall.frames.push_back({ 47, 353, 34, 34 });
		p->animBall.frames.push_back({ 82, 353, 34, 34 });
		p->animBall.frames.push_back({ 117, 353, 34, 34 });
		p->animBall.loop = true;
		p->animBall.speed = 0.2f;

		 p->animEndBall.frames.push_back({ 300, 360, 30, 34 });
		 p->animEndBall.frames.push_back({ 340, 360, 30, 34 });
		 p->animEndBall.frames.push_back({ 300, 360, 30, 34 });
		 p->animEndBall.frames.push_back({ 340, 360, 30, 34 });
		 p->animEndBall.frames.push_back({ 300, 360, 30, 34 });
		 p->animEndBall.frames.push_back({ 340, 360, 30, 34 });
		 p->animEndBall.loop = false;
		 p->animEndBall.speed = 0.6f;
		
		 p->fxball = App->sound->LoadFx("../Game/Effects/"SOUND_CHOQUEBALL);;
		 p->fxballbroke = App->sound->LoadFx("../Game/Effects/"SOUND_BALLBROKEN);;

	EnemyActive.push_back(p);
}


update_status ModuleEnemy::PostUpdate(){
	for (list<Enemy*>::iterator it = EnemyActive.begin(); it != EnemyActive.end();)
	{
		Enemy* p = *it;

		if (p->Finished == true)
		{
			p->colliderBallMove->active = false;
			App->renderer->Blit(p->graphics, p->position.x, p->position.y, &(p->animEndBall.GetCurrentFrame()));
			if (p->animEndBall.NumFrames() == 5){
				RELEASE(p);
				it = EnemyActive.erase(it);
				break;			
			}
			return UPDATE_CONTINUE;
		}
		
		
		if (p->Update() == false)
		{
			RELEASE(p);
			it = EnemyActive.erase(it);
			break;
		}
		else if (p->timer.Read() > p->delay)
		{
			App->renderer->Blit(p->graphics, p->position.x, p->position.y, &(p->current_animation->GetCurrentFrame()));
			if (p->current_animation->Finished()){
				if (p->ground){
					p->walk = true;
				}
			}
			
		}
		++it;
	}
	return UPDATE_CONTINUE;
}

void ModuleEnemy::DeleteEnemy(){
	for (list<Enemy*>::iterator it = EnemyActive.begin(); it != EnemyActive.end();)
	{
		Enemy* p = *it;
		RELEASE(p);
		it = EnemyActive.erase(it);
		break;
	}
}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{

	for (list<Enemy*>::iterator it = EnemyActive.begin(); it != EnemyActive.end(); ++it)
	{
		
		if ((*it)->collider == c1 && c2->type == COLLIDER_PLAYER_SHOT)
		{
			(*it)->atrapado = true;
			++(*it)->countShot;
		}
		

		if ((*it)->collider == c1 && c2->type == COLLIDER_BALL_MOVE)
		{
			RELEASE(*it);
			it = EnemyActive.erase(it);
			break; 
		}

		if ((*it)->colliderGround == c1 && c2->type == COLLIDER_GROUND)
		{
			--(*it)->position.y;
			(*it)->ground = true;
		}

		if ((*it)->colliderBall == c1)//comportamiento con el estado bola
		{
			if (c2->type == COLLIDER_PLAYER){
				(*it)->ball = true;
				if (App->player->direction)
				{
					++(*it)->position.x;
				}
				else{
					--(*it)->position.x;
				}
			}

			if (c2->type == COLLIDER_BALL_MOVE){
				
				//play effect ball
				App->sound->PlayFx((*it)->fxball);

				if (App->player->direction)
				{
					++(*it)->position.x;
				}
				else{
					--(*it)->position.x;
				}
					(*it)->ballmove = true;
					(*it)->direction = App->player->direction;
					(*it)->colliderBall->active = false;
					(*it)->colliderBallMove->active = true;
			}

			if (c2->type == COLLIDER_WALL_ENEMY || c2->type == COLLIDER_BALL){
				
				if ((*it)->direction){
						(*it)->position.x-=2;
					}
					else{
						(*it)->position.x+=2;
					}
				}

			if (c2->type == COLLIDER_GROUND){
				--(*it)->position.y;
			}

			if (c2->type == COLLIDER_PLAYER_SHOT)
			{
				if ((*it)->ball){
					(*it)->ballmove = true;
					(*it)->direction = App->player->direction;
					(*it)->colliderBall->active = false;
					(*it)->colliderBallMove->active = true;
				}
			}

		}

		if ((*it)->colliderBallMove == c1)//comportamiento con el estado bola en movimiento
		{
			if (c2->type == COLLIDER_GROUND){
				--(*it)->position.y;
			}

			if (c2->type == COLLIDER_WALL_ENEMY){// change direction
				//play effect ball
				App->sound->PlayFx((*it)->fxball);

				if ((*it)->timer.Read() - (*it)->delay > 100){
					(*it)->delay = (*it)->timer.Read();
					if ((*it)->direction){
						(*it)->position.x -= 2;
						(*it)->direction = false;
					}
					else{
						(*it)->position.x += 2;
						(*it)->direction = true;
					}
				}
			}

			if (c2->type == COLLIDER_WALL || c2->type == COLLIDER_BOSS){// Delete ball
				
				//play effect ball broke
				App->sound->PlayFx((*it)->fxballbroke);
				(*it)->Finished = true;
			}

		}

		if ((*it)->colliderGround == c1 && c2->type == COLLIDER_WALL_ENEMY || (*it)->colliderGround == c1 && c2->type == COLLIDER_ENEMY)//comportamiento con la tierra
		{
			//si no estan en bola solo cuando caminan
			if ((*it)->ground){	
				if ((*it)->direction)
				{
					if ((*it)->timer.Read() - (*it)->delay > 500){
						(*it)->delay = (*it)->timer.Read();
						(*it)->direction = false;
					}
				}
				else
				{
					if ((*it)->timer.Read() - (*it)->delay > 500){
						(*it)->delay = (*it)->timer.Read();
						(*it)->direction = true;
					}
				}
			}
		}
	}
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;

	if (colliderGround != nullptr)
		colliderGround->to_delete = true;

	if (colliderBall != nullptr)
		colliderBall->to_delete = true;

	if (colliderBallMove != nullptr)
		colliderBallMove->to_delete = true;
}

bool Enemy::Update()
{
	bool ret = true;

	if (collider != NULL)
	{
		SDL_Rect r = animInitial.PeekCurrentFrame();
		collider->rect = {position.x+4, position.y+5, r.w-4, r.h-9 };
	}

	if (colliderGround != NULL)
	{
		SDL_Rect r = animInitial.PeekCurrentFrame();
		colliderGround->rect = { position.x+2, position.y+22, 19, 3};
	}

	if (colliderBall != NULL)
	{
		SDL_Rect r = animBall.PeekCurrentFrame();
		colliderBall->rect = { position.x+4, position.y+10, r.w-15, r.h-13 };
	}

	if (colliderBallMove!= NULL)
	{
		SDL_Rect r = animBall.PeekCurrentFrame();
		colliderBallMove->rect = { position.x + 4, position.y + 10, r.w - 15, r.h - 13 };
	}

	if (position.x < -40 || position.x>270){ //out scren
		return false;
	}
	
	if (ballmove){
			++position.y;
			current_animation = &animBall;

			if (direction){
				position.x += 2;
			}
			else{
				position.x -= 2;
			}
			return ret;
		}
	

	if (atrapado)
	{
		++position.y;

		if (countShot==1){
		
			current_animation = &animAtrapado1;
		}
		else if (countShot == 2){
			current_animation = &animAtrapado2;
		}
		else if (countShot == 3){
			current_animation = &animAtrapado3;
		}
		else{
			collider->active = false;
			colliderGround->active = false;
			current_animation = &animAtrapado4;
			colliderBall->active = true;
			if (ball){
				current_animation = &animBall;
			}
		}
		ball = false;
		return ret;
	}

	if (walk)
	{
		if (direction){
			position.x += speed.x;
			position.y += speed.y;
			current_animation = &animWalkRight;
		}
		else{
			position.x -= speed.x;
			position.y += speed.y;
			current_animation = &animWalkLeft;
		}
		
		return ret;
	}

	if (ground){
		if (direction){
			current_animation = &animIldeRight;
		}
		else{
			current_animation = &animIldeleft;
		}
			return ret;
	}

	if (direction){

		position.x += speed.x;
		position.y += speed.y;

	}
	else
	{
		position.x -= speed.x;
		position.y += speed.y;
	}

	
	current_animation = &animInitial;
	return ret;
}