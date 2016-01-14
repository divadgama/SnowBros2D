#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "Point.h"
#include "Timer.h"

struct Collider;
struct SDL_Texture;
enum COLLIDER_TYPE;

struct Enemy
{
	SDL_Texture* graphics = nullptr;
	Animation animInitial;
	Animation animIldeRight;
	Animation animIldeleft;
	Animation animWalkLeft;
	Animation animWalkRight;
	Animation animAtrapado1;
	Animation animAtrapado2;
	Animation animAtrapado3;
	Animation animAtrapado4;
	Animation animBall;
	Animation animEndBall;

	Animation* current_animation = nullptr;

	iPoint position = { 0, 0 };
	iPoint speed = { 1, 1 };
	Timer timer;
	uint32 delay=10;
	uint32 delaywalk = 10;
	Collider* collider = nullptr;
	Collider* colliderGround = nullptr;
	Collider* colliderBall = nullptr;
	Collider* colliderBallMove= nullptr;

	bool direction = false;//false left true right
	bool atrapado = false;
	bool ground = false;
	bool walk = false;
	bool ball = false;
	bool ballmove=false;
	bool Finished = false;
	int countShot=0;

	//effect
	unsigned int fxball = 0;
	unsigned int fxballbroke = 0;

	~Enemy();
	bool Update();
};



class ModuleEnemy : public Module
{
public:

	ModuleEnemy(); 
	~ModuleEnemy();

	update_status PostUpdate();

	void OnCollision(Collider* c1, Collider* c2);
	void AddEnemy(const Enemy& enemy, int x, int y);
	void DeleteEnemy();

private:

	std::list<Enemy*> EnemyActive;

};
#endif //__MODULEENEMY_H__

