#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "Point.h"

class ModuleEnemy : public Module
{
public:
	ModuleEnemy(bool start_enabled = true); 
	~ModuleEnemy();

	bool Start();

	//update_status Update();
	bool CleanUp();
	//void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	Collider* collider = nullptr;

	Animation* current_animation = nullptr;
	Animation idleright;
	Animation idleleft;

	Animation walkleft;
	Animation walkright;

	bool direction = true;//direction true = right false = left
	bool finished = false;
	iPoint position;

};
#endif //__MODULEENEMY_H__

