#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "Point.h"
#include "Timer.h"



struct SDL_Texture;
struct Collider;
struct Particle;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* particles = nullptr;
	Collider* collider = nullptr;
	Collider* colliderGround = nullptr;
	Animation* current_animation = nullptr;
	Animation idleVacio;
	Animation idleright;
	Animation idleleft;
	Animation jumpright;
	Animation jumpleft;
	Animation downright;
	Animation downleft;
	Animation walkleft;
	Animation walkright;
	Animation die;
	Animation animballLeft;
	Animation animballRight;
	Animation animballAtrapado;
	Animation animshotLeft;
	Animation animshotRight;
	Particle shotRight;
	Particle shotLeft;



	bool direction = true;//direction true = right false = left
	bool jump = false;
	bool collidingGround = false;
	int frameAnimacion = 0;
	bool finished = false;
	bool inicio = true;
	bool shot = false;
	bool ball=false;
	bool diebool = false;
	iPoint position;

	int life = 3;

	Timer timer;
	uint32 delay = 10;

	//effects
	unsigned int fxjump = 0;
	unsigned int fxdie = 0;
	

};

#endif // __MODULEPLAYER_H__