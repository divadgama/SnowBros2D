#ifndef __MODULEBOSS_H__
#define __MODULEBOSS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "Timer.h"

class ModuleBoss : public Module
{
public:
	ModuleBoss(bool start_enabled = true);
	~ModuleBoss();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	Collider* collider = nullptr;
	Collider* colliderPoint = nullptr;
	Collider* colliderGround = nullptr;
	Animation* current_animation = nullptr;
	
	Animation idle;
	Animation idle2;
	Animation die;
	Animation jump;
	Animation shot;

	bool finished = false;
	bool collidingGround = false;
	bool shotboolean = false;
	bool still = false;
	bool plataformatop = false;
	int option=0;
	int preoption = 0;
	int life = 5;
	iPoint position;

	Timer timer;
	uint32 delay = 2;
	uint32 delayDie = 2;
	uint32 delayStill = 2;
	uint32 delayFinish = 2;
	int count=0;

};

#endif // __MODULEBOSS_H__